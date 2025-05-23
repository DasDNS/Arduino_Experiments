# 🌐 ESP32 WebSocket LED Controller with LittleFS

This project sets up an ESP32 as a WebSocket-enabled web server that allows real-time control of two LEDs from a web interface. It uses `ESPAsyncWebServer` and `LittleFS` to serve an HTML page that communicates with the ESP32 via WebSockets.

---

## 🚀 Features

- 📡 Wi-Fi-enabled ESP32 web server on port 80
- 🔌 Real-time LED control via WebSocket messages
- 🧠 Dual LED state tracking and response
- 🗂️ HTML page served from onboard `LittleFS` storage
- 📲 Easily accessible via ESP32 local IP address

---

## 🧰 Requirements

- ESP32 board
- Arduino IDE or PlatformIO
- Libraries:
  - `WiFi.h`
  - `ESPAsyncWebServer.h`
  - `AsyncTCP.h`
  - `LittleFS.h`

You can install the required libraries via the Arduino Library Manager or from GitHub.

---

## 📂 File Structure

ESP32-WebSocket-LED/
│
├── data/
│ └── index.html # Web page with WebSocket logic
├── src/
│ └── main.ino # This Arduino sketch
└── README.md


> Make sure to upload files in the `data/` folder to `LittleFS` using the **ESP32 Sketch Data Upload Tool** (in Arduino) or `pio run --target uploadfs` (in PlatformIO).

---

## 📶 Wi-Fi Credentials

Update the following lines in `main.ino` with your network details:

```cpp
const char* ssid = "your-SSID";
const char* password = "your-PASSWORD";

🔌 GPIO Pin Mapping
Component	GPIO
LED 1	22
LED 2	23

The LEDs are toggled by WebSocket commands: "toggle" for LED 1 and "toggle2" for LED 2.

🔁 Behavior Summary
ESP32 connects to Wi-Fi and starts a web server.

It mounts LittleFS and serves index.html when accessed from a browser.

When a button is clicked on the page:

A WebSocket message is sent ("toggle" or "toggle2").

The corresponding LED state is toggled.

LED status is sent back to all connected WebSocket clients.

🖥️ Example WebSocket Message Handling
cpp
Copy
Edit
if (strcmp((char*)data, "toggle") == 0) {
  ledState = !ledState;
  notifyClients();
}
🌐 Accessing the Web App
Upload index.html to LittleFS.

Flash the sketch to the ESP32.

Open the Serial Monitor to find the device’s IP.

In your browser, go to: http://<ESP32-IP>/

Example:

sh
Copy
Edit
http://192.168.1.100/

