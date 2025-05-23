# 🚀 ESP32 WebSocket-Based LED Controller (Up & Left)

This project enables real-time control of two LEDs connected to an ESP32 using WebSockets and a web interface hosted via `LittleFS`. The interface responds to `toggleUp` and `toggleLeft` WebSocket commands to control the respective LEDs.

---

## 🧠 Key Features

- 🌐 Wi-Fi-connected ESP32 web server (port 80)
- ⚡ Real-time control of two LEDs using WebSocket messages:
  - `toggleUp` → LED 1 (GPIO 22)
  - `toggleLeft` → LED 2 (GPIO 23)
- 🗂️ Serves static files from onboard `LittleFS` filesystem
- 🔁 WebSocket client auto-updates on LED state changes (if implemented)

---

## 🧰 Requirements

- ESP32 development board
- Arduino IDE or PlatformIO
- Required Libraries:
  - [`ESPAsyncWebServer`](https://github.com/me-no-dev/ESPAsyncWebServer)
  - [`AsyncTCP`](https://github.com/me-no-dev/AsyncTCP)
  - `LittleFS` (included with ESP32 core)

---

## 📁 Project Structure

ESP32-WebSocket-LED-UpLeft/
│
├── data/
│ └── index.html # Web interface with WebSocket controls
├── src/
│ └── main.ino # ESP32 source code
└── README.md


---

## 🔧 Setup Instructions

1. **Configure Wi-Fi**  
   Update these lines in `main.ino` with your Wi-Fi credentials:

   ```cpp
   const char* ssid = "your_SSID";
   const char* password = "your_PASSWORD";

Upload Web Files to LittleFS
Put your index.html in the data/ folder and upload it:

In Arduino IDE: Use the ESP32 Sketch Data Upload tool

In PlatformIO: Run pio run --target uploadfs

Flash and Run
Upload the sketch to the ESP32 and open the Serial Monitor to get the local IP address.

Access the Web App
Open your browser and go to:

cpp
Copy
Edit
http://<ESP32_IP>/
🔌 GPIO Mapping
LED Function	GPIO Pin	WebSocket Message
Up Control	22	toggleUp
Left Control	23	toggleLeft

LEDs toggle when the corresponding WebSocket message is received from the web page.

📡 WebSocket Handling
cpp
Copy
Edit
if (strcmp((char*)data, "toggleUp") == 0) {
  ledState = !ledState;
}
if (strcmp((char*)data, "toggleLeft") == 0) {
  ledState2 = !ledState2;
}
