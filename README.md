# ⚙️ ESP32 Cache Simulator

## 📘 Project Overview
The **ESP32 Cache Simulator** is an embedded systems project designed to simulate cache memory behavior and its interaction with main memory.  
It demonstrates both **Direct-Mapped** and **Set-Associative** cache architectures, while supporting multiple **replacement policies** like **FIFO** and **LRU**.  

Through real-time LED feedback and a **web-based dashboard**, users can visualize cache hits, misses, and memory access patterns.  
The simulator also integrates **CACTI-based analysis** for performance modeling, including access time, power consumption, and area estimation.

---

## 🚀 Features
- **Cache Architectures:** Supports both Direct-Mapped and Set-Associative caches with configurable associativity and block sizes.  
- **Replacement Policies:** Implements FIFO and LRU algorithms for cache line replacement.  
- **Real-Time Visualization:**  
  - Green LED → Cache Hit  
  - Red LED → Cache Miss  
- **Web Dashboard:** Displays cache contents, hit/miss ratios, AMAT (Average Memory Access Time), and performance graphs with live updates over Wi-Fi.  
- **CACTI Integration:** Enables hardware-level performance evaluation (access time, power, area).  
- **Configurable System:** Easily modify cache, memory, and hardware parameters through JSON files.  
- **Logging:** Generates detailed logs for memory accesses, metrics, and errors.

---

## 🧠 System Architecture
The simulator is composed of **three core modules**:
1. **ESP32 Firmware:**  
   Handles cache logic, memory access requests, replacement policies, and LED signaling.  
2. **Web Dashboard:**  
   Hosted on the ESP32, visualizing cache state, hit/miss data, and real-time metrics.  
3. **CACTI Integration:**  
   Simulates hardware characteristics (latency, power, area) based on cache configurations.

The data flow between **CPU requests → Cache → Main Memory → LEDs → Dashboard** provides a comprehensive real-time view of caching behavior.

---

## 🧩 Cache and Memory Configuration
You can configure all system parameters using JSON files:
- `config/cache_config.json` → Cache size, block size, associativity, replacement policy  
- `config/memory_config.json` → Memory size and block configuration  
- `config/led_config.json` → LED pin assignments and blink timings  

This modular setup supports classroom experiments, performance benchmarking, or research comparisons.

---

## 📊 Logging and Metrics
The simulator maintains comprehensive logs for analysis:
- **access_log.txt:** Memory addresses, hit/miss status, and timestamps  
- **metrics_log.csv:** Real-time hit ratio, miss ratio, and AMAT  
- **error_log.txt:** Captures unexpected events or failed accesses  

Logs are accessible via the dashboard or for offline evaluation.

---

## 🔬 CACTI Integration
CACTI integration enables hardware-level analysis:
- Define cache parameters in `cacti/cache.cfg`  
- Generate detailed reports (access time, dynamic/leakage power, area)  
- Results are stored in `cacti/results/`  
- Compare CACTI outputs with real-time ESP32 metrics for validation and study

---

## 🧭 Usage Instructions
1. Connect LEDs to ESP32 following the provided wiring diagram.  
2. Configure cache, memory, and LED settings using the JSON files.  
3. Upload the firmware from `/src` to your ESP32 via the **Arduino IDE**.  
4. Connect to the ESP32-hosted **web dashboard** to monitor live performance.  
5. (Optional) Run **CACTI simulations** for hardware-level cache evaluation.

---

## 🎓 Educational and Research Applications
This project provides a **hands-on platform** for understanding:
- Cache memory behavior  
- Replacement policies (FIFO, LRU)  
- Memory hierarchy performance  

It’s ideal for **computer architecture courses**, **embedded systems labs**, or **research** on cache performance modeling.

---

## 🪪 License
This project is licensed under the **MIT License**.  
See the [LICENSE](LICENSE) file for details.

---

### 🧰 Developed Using
- **ESP32 Development Board**
- **Arduino IDE**
- **CACTI Toolset**
- **HTML/CSS/JavaScript** (for dashboard)
- **JSON Configuration Files**

---

### 💡 Author
**Manjunath Rachakonda**  
📍 JIIT Noida | Embedded Systems & Computer Architecture Enthusiast  
📧 [GitHub Profile](https://github.com/Manjunathmcu718)

---
