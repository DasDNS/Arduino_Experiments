# ESP32 Web-Controlled Servo Motor

This project demonstrates how to control a servo motor using an ESP32 microcontroller over Wi-Fi through a simple web interface. The ESP32 acts as a web server, and users can control the servo's position using a slider on the web page.

## Features

- Hosts a web server on the ESP32
- Displays a slider to adjust servo motor position (0° to 180°)
- Sends real-time commands to the servo via HTTP GET requests
- Mobile-friendly interface using basic HTML/CSS/JavaScript

## Hardware Required

- ESP32 development board
- Servo motor (e.g., SG90 or MG90)
- Jumper wires
- Power supply (e.g., USB or battery)

## Connections

| ESP32 Pin | Component |
|-----------|-----------|
| GPIO 13   | Servo signal pin |
| 5V        | Servo VCC        |
| GND       | Servo GND        |

## Installation

1. Connect your ESP32 to your PC.
2. Open the code in the Arduino IDE.
3. Install the required libraries:
   - `WiFi.h` (included with ESP32 boards)
   - `ESP32Servo.h` (Install from Library Manager)
4. Replace the following lines with your Wi-Fi credentials:
   ```cpp
   const char* ssid     = "YOUR_SSID";
   const char* password = "YOUR_PASSWORD";

