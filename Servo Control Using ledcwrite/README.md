#Control five servo motors using ledcWrite function
#Convert 0-180 degrees to 0-65535

# ESP32 Multi-Servo WebSocket Controller

This project enables real-time control of up to **6 servo motors** via a **web-based UI** using an **ESP32 microcontroller**. It leverages WebSocket communication for efficient and fast updates, and serves its frontend files from the ESP32's internal **LittleFS** filesystem.

---

## 🛠️ Features

- Control up to **6 servo motors** using sliders in a web interface.
- WebSocket communication for **real-time updates**.
- **LittleFS** is used to serve HTML/CSS/JS files.
- Angle-to-PWM conversion for standard hobby servos.
- Built-in WiFi client mode.

---

## 📦 Hardware Requirements

- ESP32 development board
- 5x servo motors (can be extended to 6)
- External power supply (recommended for multiple servos)
- Jumper wires and breadboard

---

## 💾 Library Dependencies

Ensure the following libraries are installed in the Arduino IDE:

- `ESPAsyncWebServer`
- `AsyncTCP`
- `Arduino_JSON`
- `LittleFS` (via ESP32 filesystem support)

---

## 📁 Project Structure

/project-root
│
├── data/
│ └── index.html # Web interface with sliders (to be served via LittleFS)
├── main.ino # Arduino sketch (code provided)
└── README.md


> Upload `/data` files to LittleFS using the [ESP32 LittleFS uploader plugin](https://github.com/lorol/arduino-esp32fs-plugin).

---

## 📡 Network Setup

Update your WiFi credentials in the sketch:

```cpp
const char* ssid = "***";
const char* password = "*******";

🧪 Testing
Connect the ESP32 to your WiFi.

Upload files to LittleFS (index.html with sliders).

Open the Serial Monitor at 115200 baud.

Access the ESP32 IP address from a browser.

Use sliders to control each servo in real-time.

