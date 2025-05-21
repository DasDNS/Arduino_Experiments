# ESP32 Web-Based WAV Audio Recorder

This project demonstrates how to record stereo audio using the ESP32's I2S interface and save it as a WAV file using LittleFS. The recorded audio is then hosted via a web server on the ESP32 for download.

---

## 🎯 Features

- Records **stereo audio** (2 channels) at **16 kHz** sampling rate using I2S
- Stores audio as a **WAV file** on the ESP32's internal flash using **LittleFS**
- Serves the recorded audio file over Wi-Fi using an **Async Web Server**
- Displays progress via serial monitor during recording
- Automatically stops recording after a defined time (default: 20 seconds)

---

## 🧠 Technical Details

| Feature                | Configuration              |
|------------------------|----------------------------|
| I2S Port               | `I2S_NUM_0`                |
| Sample Rate            | `16,000 Hz`                |
| Bits Per Sample        | `16 bits`                  |
| Channels               | `Stereo (2 channels)`      |
| Recording Duration     | `20 seconds`               |
| File Format            | `.wav`                     |
| File System            | `LittleFS`                 |
| File Size              | ~1.28 MB                   |
| HTTP Endpoint          | `/recording.wav`           |
| Web Server Port        | `80`                       |

---

## 📦 Hardware Used

- **ESP32** Development Board (with sufficient flash memory)
- **I2S Microphone Module** (e.g., INMP441, ICS43434)
- Wi-Fi Connection

### 🛠 I2S Pinout

| Signal       | GPIO Pin |
|--------------|----------|
| BCK (SCK)    | 26       |
| WS (LRCK)    | 25       |
| SD (DOUT)    | 22       |

Adjust pins in the code as needed for your hardware.

---

## 🚀 Getting Started

### 1. Prerequisites

- **Arduino IDE** with **ESP32 board support**
- Libraries:
  - `ESPAsyncWebServer`
  - `AsyncTCP`
  - `LittleFS`
  - `driver/i2s.h`

### 2. Setup Wi-Fi

Edit these lines in the sketch to set your Wi-Fi credentials:

```cpp
const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";

