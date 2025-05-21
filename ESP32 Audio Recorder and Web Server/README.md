# ESP32 Audio Recorder & Web Server

This project implements a real-time audio recording system on the ESP32 using the I2S protocol and serves the recorded `.wav` file over Wi-Fi using an HTTP web server. It stores audio to the ESP32's internal flash via the `LittleFS` file system and serves it for remote access.

## 🚀 Features

- Records 16-bit mono audio at 16kHz using an I2S microphone
- Saves audio as a `.wav` file in flash using LittleFS
- Runs a Wi-Fi server (AP or Station) for file download
- Handles audio scaling and WAV header generation
- Multi-tasked using FreeRTOS to offload I2S data collection

## 🛠️ Hardware Required

- ESP32 Dev Board
- I2S MEMS Microphone (e.g., ICS43434, INMP441)
- USB Cable
- Optional: Power bank or battery

## 🔧 Wiring

| Microphone Pin | ESP32 Pin |
|----------------|-----------|
| WS (LRCL)      | GPIO25    |
| SD (DOUT)      | GPIO22    |
| SCK (BCLK)     | GPIO26    |
| GND            | GND       |
| VCC            | 3.3V      |

## 📦 Libraries Used

- `WiFi.h`
- `AsyncTCP.h`
- `ESPAsyncWebServer.h`
- `LittleFS.h`
- `driver/i2s.h` (ESP32 native)

## 📁 File Structure

- `recording.wav` – The output audio file accessible from browser
- Stored in internal flash using LittleFS

## 🌐 Web Access

After boot:
1. Connect ESP32 to Wi-Fi
2. Note the IP address printed in the serial monitor
3. Open your browser and go to:

http://<ESP32_IP_ADDRESS>/recording.wav


## ⏺️ Recording Parameters

- Sample Rate: 16,000 Hz
- Bits per Sample: 16
- Channels: Mono (Right only)
- Duration: 20 seconds
- File Size: ~640 KB

## 🧠 Notes

- Make sure the microphone is wired correctly to avoid silent recordings.
- The system uses FreeRTOS to handle real-time audio recording in the background.
- Recorded files are served immediately after recording ends.


