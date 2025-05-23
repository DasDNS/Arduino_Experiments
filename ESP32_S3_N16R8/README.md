# 🧠 ESP32-S3 Memory Diagnostic Tool

This Arduino sketch reports detailed memory statistics of your **ESP32-S3** board, including flash size, PSRAM, heap usage, and internal RAM status. It’s useful for performance optimization, debugging, and understanding available memory resources before deploying memory-intensive applications.

---

## 📋 Features

- 📦 Reports **flash memory size** and **free sketch space**
- 🗃️ Displays **heap** and **PSRAM** usage
- 📊 Prints **minimum free heap ever** recorded
- 🧠 Shows **internal RAM** statistics (excluding PSRAM)

---

## 🔧 Requirements

- ESP32-S3 board
- Arduino IDE with **ESP32 board support**
- Baud rate: `115200`

---

## 🧪 Output Example

```text
ESP32-S3 Memory Information:
Flash chip size: 4194304 bytes
Free sketch space: 1441792 bytes
Total heap size: 327680 bytes
Free heap size: 214312 bytes
Minimum free heap ever: 198456 bytes
PSRAM size: 8388608 bytes
Free PSRAM: 8326144 bytes
Internal RAM Information:
Total internal RAM size: -8060928 bytes
Free internal RAM: -8111832 bytes

⚠️ Note: If you see negative values, it may indicate a miscalculation or a lack of PSRAM support on your board/configuration. This usually occurs when using functions not supported by a particular chip variant.

📂 File Structure
bash
Copy
Edit
ESP32S3-Memory-Diagnostics/
└── memory_info.ino      # Main Arduino sketch
└── README.md            # This file

🚀 How to Use
Open the sketch in Arduino IDE.

Select your ESP32-S3 board under Tools > Board.

Upload the code.

Open the Serial Monitor at 115200 baud.

View detailed memory diagnostics.

📘 Reference Functions Used
Function	Description
ESP.getFlashChipSize()	Flash size in bytes
ESP.getFreeSketchSpace()	Available space for sketch
ESP.getHeapSize()	Total dynamic heap size
ESP.getFreeHeap()	Current free heap
ESP.getMinFreeHeap()	Lowest ever free heap recorded
ESP.getPsramSize()	Total PSRAM size
ESP.getFreePsram()	Free PSRAM memory

📌 Notes
This sketch is read-only: it does not modify flash or RAM.

Ensure your board supports PSRAM if you want accurate PSRAM metrics.

Compatible with ESP32-S3 boards using Arduino framework.


