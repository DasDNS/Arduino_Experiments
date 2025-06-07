# ESP32 Web-Based Servo Controller

This project is an ESP32-based web-controlled servo motor interface using WebSockets and LittleFS. It allows real-time control of a servo motor through a web interface by adjusting a slider. The servo is managed via an Adafruit PWM Servo Driver (PCA9685).

## Features

- Real-time servo motor control via WebSocket
- Files served from LittleFS (e.g., `index.html`)
- Uses Adafruit PCA9685 for PWM control
- Lightweight and fast UI communication using JSON
- Runs as a WiFi Station

## Hardware Requirements

- [ESP32 Dev Module](https://www.espressif.com/en/products/socs/esp32)
- [Adafruit PCA9685 16-Channel PWM Servo Driver](https://www.adafruit.com/product/815)
- Servo motor
- WiFi network
- Optional: external power supply for servos

## Software Dependencies

Install the following libraries in the Arduino IDE:
- `ESPAsyncWebServer`  
- `AsyncTCP`  
- `Arduino_JSON`  
- `LittleFS`  
- `Adafruit PWM Servo Driver Library`
- `Wire.h` (typically built-in)

## File Structure

/project-root
│
├── index.html # Web UI served via LittleFS
├── main.ino # The Arduino sketch (code provided below)
└── data/ # Contains the LittleFS files (upload using the LittleFS uploader)


## How It Works

1. ESP32 connects to a WiFi network.
2. A WebSocket server runs on port 80.
3. The client (index.html) connects and sends slider values.
4. ESP32 maps the received angle to a PWM pulse width.
5. The PCA9685 servo driver outputs corresponding signals to control the servo.

## WiFi Configuration

Update the following lines with your WiFi credentials:

```cpp
const char* ssid = "***";
const char* password = "*******";


Uploading Files to LittleFS
Place your index.html (or other assets) into a /data directory.

Use the LittleFS Uploader to upload the files.

Serial Monitor Output
Monitor the ESP32 at 115200 baud for:

WiFi status

WebSocket events

Slider data and mapped pulse values




