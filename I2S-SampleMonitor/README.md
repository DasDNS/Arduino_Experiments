# I2S-SampleMonitor

**I2S-SampleMonitor** is a lightweight Arduino-based tool for the ESP32 that continuously reads audio samples from a digital MEMS microphone (like the INMP441) via the I2S interface and logs the number of effective samples captured per minute at a target sample rate. This is useful for verifying microphone functionality, sample integrity, and system timing.

---

## 📌 Features

- 📶 Reads 16-bit mono audio samples using I2S
- 🎯 Downsamples from the microphone’s native sample rate to a target rate
- 🧪 Reports sample count every minute for monitoring and analysis
- 🔧 Customizable pin and sampling rate configuration

---

## 📷 Hardware Requirements

- **ESP32 Development Board**
- **INMP441** or compatible I2S digital microphone
- Jumper wires for connection

---

## 🧰 Pin Configuration

Update the following pins as needed for your board layout:

| Signal       | ESP32 GPIO |
|--------------|------------|
| BCLK (SCK)   | 32         |
| LRCLK (WS)   | 25         |
| DOUT (SD)    | 33         |

---

## ⚙️ Configuration

You can modify the following constants in the code to match your needs:

```cpp
#define SAMPLE_RATE 16000    // Native mic sampling rate
#define TARGET_RATE 16000    // Downsample target (can be equal)
#define I2S_BUFFER_SIZE 512  // I2S buffer size in samples

🚀 Getting Started
Clone this repository or copy the *.ino code to your Arduino IDE.

Connect your INMP441 microphone to the ESP32 as per the pin configuration.

Upload the sketch.

Open the Serial Monitor at 115200 baud.

Observe the number of samples captured every minute.

📡 Output Example

I2S Initialized
Captured samples in last minute: 960000
Captured samples in last minute: 960000
...
📚 Dependencies
Arduino core for ESP32

Uses native driver/i2s.h for efficient audio sampling

🧠 Use Cases
Verifying I2S mic connectivity and performance

Benchmarking sample throughput

Audio capture timing and buffer test
