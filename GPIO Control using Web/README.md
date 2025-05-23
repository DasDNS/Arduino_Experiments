# 🔌 ESP32 Web Server for GPIO Control

This project creates a simple web server using an ESP32 microcontroller to control two GPIO pins (GPIO 13 and GPIO 14) over Wi-Fi using a web browser.

## 📡 Features

- Connects to a local Wi-Fi network
- Hosts a web server on port 80
- Provides a simple HTML interface to:
  - Turn GPIO 13 (labeled as GPIO 12 in the interface) ON/OFF
  - Turn GPIO 14 ON/OFF
- Real-time GPIO state display

## 🛠️ Requirements

- ESP32 Development Board
- Arduino IDE or PlatformIO
- USB cable for programming
- Wi-Fi network credentials

## 🔧 Setup Instructions

1. **Install ESP32 board in Arduino IDE**
   - Follow the official [ESP32 setup guide](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html)

2. **Connect your ESP32 to your PC**

3. **Upload the Code**
   - Replace the Wi-Fi credentials:
     ```cpp
     const char* ssid = "YOUR_SSID";
     const char* password = "YOUR_PASSWORD";
     ```
   - Select your ESP32 board and correct COM port
   - Click `Upload`

4. **Open Serial Monitor**
   - Set baud rate to `115200`
   - After connecting to Wi-Fi, your ESP32 will print its IP address

5. **Control GPIOs**
   - Open the IP address in a browser (e.g., `http://192.168.1.x`)
   - Use the buttons to toggle GPIO 13 and 14

## 🌐 Web Interface

The web page includes:
- ON/OFF buttons for each GPIO
- Status display for current state of each pin
- Simple CSS styling for easy interaction

## 📁 Project Structure

📂 ESP32-WebServer-GPIO
├── main.ino (your Arduino code)
└── README.md
