#include <WiFi.h>
#include <WebServer.h>

// ======== Wi-Fi Setup (EDIT THESE) =========
const char* ssid = "Hotspot";          // 🔹 Your hotspot name
const char* password = "mahirat718";  // 🔹 Your hotspot password
// ===========================================

// LED pin (use GPIO 2)
#define LED_PIN 2

// Cache setup
#define CACHE_LINES 8
struct CacheLine {
  int tag;
  bool valid;
  unsigned long lastUsed;
};
CacheLine cache[CACHE_LINES];

int totalAccesses = 0, hits = 0, misses = 0;
WebServer server(80);

// --------------------------------------------------
// LED Blink Functions
// --------------------------------------------------
void blinkOnce() { // Cache HIT
  digitalWrite(LED_PIN, HIGH);
  delay(150);
  digitalWrite(LED_PIN, LOW);
}

void blinkTwice() { // Cache MISS
  for (int i = 0; i < 2; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(120);
    digitalWrite(LED_PIN, LOW);
    delay(120);
  }
}

// --------------------------------------------------
// Cache Access Simulation
// --------------------------------------------------
int accessMemory(int address) {
  totalAccesses++;
  int index = address % CACHE_LINES;
  int tag = address / CACHE_LINES;

  if (cache[index].valid && cache[index].tag == tag) {
    hits++;
    cache[index].lastUsed = millis();
    blinkOnce();  // HIT → 1 blink
    return 1;
  } else {
    misses++;
    cache[index].valid = true;
    cache[index].tag = tag;
    cache[index].lastUsed = millis();
    blinkTwice(); // MISS → 2 blinks
    return 0;
  }
}

// --------------------------------------------------
// Web Dashboard
// --------------------------------------------------
void handleRoot() {
  String html = "<html><head><title>ESP32 Cache Simulator</title>"
                "<meta http-equiv='refresh' content='3'>"
                "<style>"
                "body{font-family:Arial;background:#111;color:#0f0;text-align:center;}"
                "table{border:1px solid #0f0;margin:auto;border-collapse:collapse;}"
                "td,th{border:1px solid #0f0;padding:5px;}"
                "input{padding:5px;margin:5px;border-radius:5px;}"
                "</style></head><body>";
  html += "<h1>ESP32 Cache Simulator</h1>";
  html += "<h3>Hits: " + String(hits) + " | Misses: " + String(misses) +
          " | Total: " + String(totalAccesses) + "</h3>";

  float hitRatio = totalAccesses > 0 ? (float)hits / totalAccesses * 100 : 0;
  html += "<h3>Hit Ratio: " + String(hitRatio, 2) + "%</h3>";

  html += "<table><tr><th>Line</th><th>Tag</th><th>Valid</th></tr>";
  for (int i = 0; i < CACHE_LINES; i++) {
    html += "<tr><td>" + String(i) + "</td><td>" +
            String(cache[i].tag) + "</td><td>" +
            (cache[i].valid ? "1" : "0") + "</td></tr>";
  }
  html += "</table><br>"
          "<form action='/access'>"
          "<input type='number' name='addr' placeholder='Enter Address'>"
          "<input type='submit' value='Access'>"
          "</form></body></html>";

  server.send(200, "text/html", html);
}

void handleAccess() {
  int addr = server.arg("addr").toInt();
  int result = accessMemory(addr);
  String msg = (result == 1) ? "Cache HIT ✅" : "Cache MISS ❌";
  server.send(200, "text/html", "<h2>" + msg + "</h2><a href='/'>Back</a>");
}

// --------------------------------------------------
// SETUP
// --------------------------------------------------
void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 15000) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✅ Connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\n❌ Failed to connect to WiFi!");
    Serial.println("➡ Check SSID/password or ensure 2.4GHz hotspot is ON.");
    // Retry every 10 seconds
    while (WiFi.status() != WL_CONNECTED) {
      delay(10000);
      Serial.println("Retrying WiFi...");
      WiFi.begin(ssid, password);
    }
  }

  for (int i = 0; i < CACHE_LINES; i++) {
    cache[i].valid = false;
    cache[i].tag = -1;
  }

  server.on("/", handleRoot);
  server.on("/access", handleAccess);
  server.begin();
  Serial.println("Web server started");
}

// --------------------------------------------------
// LOOP
// --------------------------------------------------
void loop() {
  server.handleClient();
}
