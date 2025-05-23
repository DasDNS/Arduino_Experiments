# ESP32 I2S Audio Recorder with Web Server (WAV Format)

This project uses an **ESP32** to record audio from an **I2S microphone** (such as the ICS43434), save it as a **WAV file** using **LittleFS**, and host it over Wi-Fi via an **Async Web Server**.

## Features

- Records 20 seconds of mono audio at 44.1kHz, 16-bit PCM
- Saves recording in `.wav` format using `LittleFS`
- Hosts a web page to download the WAV file via `/download`
- Uses FreeRTOS task for non-blocking audio recording
- Compact and reliable file system and network handling

---

## Hardware Required

- ESP32 development board
- I2S microphone (e.g., ICS43434)
- Micro-USB cable
- Access to Wi-Fi

---

## Wiring

| Microphone Pin | ESP32 Pin |
|----------------|-----------|
| WS (LRCLK)     | GPIO15    |
| SD (DOUT)      | GPIO13    |
| SCK (BCLK)     | GPIO2     |
| GND            | GND       |
| VCC            | 3.3V      |

---

## Software Requirements

- [Arduino IDE](https://www.arduino.cc/en/software) with ESP32 board support
- Install the following libraries via Library Manager:
  - `ESPAsyncWebServer`
  - `AsyncTCP`
  - `LittleFS for ESP32`

---

## How It Works

1. **Wi-Fi Connection**: Connects to a predefined SSID (`Senz ML`) and password (`SMml@2015`).
2. **File System Init**: Formats and initializes `LittleFS`, removes old recordings.
3. **WAV Header**: Writes a valid 44-byte WAV header to the file.
4. **I2S Init**: Configures the I2S peripheral for 44.1kHz mono 16-bit data.
5. **Recording Task**: Captures 20 seconds of audio and writes it to LittleFS with proper scaling.
6. **Web Server**: Hosts endpoints:
   - `/` – Displays instructions
   - `/download` – Serves the recorded WAV file

---

## Web Interface

- **Main Page**:  
  Access the ESP32 IP address from your browser. You will see a plain text message with instructions.

- **Download Page**:  
  Navigate to `http://<ESP32-IP>/download` to download the `.wav` recording.

---

## Customization

- Change `RECORD_DURATION` to modify the recording time.
- Adjust `I2S_SAMPLE_RATE` or `I2S_SAMPLE_BITS` for different quality or size.
- Modify SSID/password for your own Wi-Fi network.

---

## Example Output

Connecting to WiFi...
Connected to WiFi
*** Recording Start ***
Sound recording 5%
Sound recording 10%
...
Sound recording 100%
*** Recording Complete ***


