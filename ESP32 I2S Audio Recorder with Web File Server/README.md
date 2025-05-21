
📻 ESP32 I2S Audio Recorder with Web File Server

This project uses an ESP32 to record audio using the I2S protocol and an I2S microphone, saves the audio as a WAV file in LITTLEFS, and provides an HTTP endpoint to download the recording.

🚀 Features
Records mono 16-bit PCM audio at 16 kHz using I2S

Saves audio as a WAV file on LITTLEFS

Hosts a web server to download the WAV file from a browser

Automatically starts recording on boot (30 seconds)

Shows progress and stack usage in Serial Monitor

🔧 Hardware Requirements
ESP32 Dev Board

I2S Microphone (e.g., ICS43434, INMP441)

USB cable for power and serial monitoring

I2S Microphone Pin Mapping
ESP32 Pin	I2S Signal	Microphone Pin
32	BCLK	BCLK
25	WS/LRCLK	L/R
33	SD	DOUT
GND	GND	GND
3.3V	VCC	VDD

📦 Software Used
Arduino Core for ESP32

ESPAsyncWebServer

AsyncTCP

LITTLEFS

FreeRTOS task for non-blocking recording

📁 File Structure
File	Description
/recording.wav	30-second recorded audio file (WAV)

📡 Web Interface
After boot, connect to the same network as your ESP32.
Access the recording at:

arduino
Copy
Edit
http://<ESP32-IP>/recording
This will start downloading the recording.wav file.

🛠️ How It Works
Connects to Wi-Fi.

Initializes LITTLEFS and I2S peripherals.

Creates a WAV file with proper header and starts recording using a FreeRTOS task.

Scales the I2S ADC data and writes to file.

On completion, the file is flushed, closed, and listed.

Starts a web server at port 80 for downloading the file.

📈 Configuration
Constants

#define I2S_SAMPLE_RATE 16000      // Sample rate in Hz
#define I2S_SAMPLE_BITS 16         // Bits per sample
#define RECORD_TIME     30         // Recording duration in seconds
To change recording time or sample rate, update the constants and re-upload.

🧪 Serial Output Example
mathematica

Connecting to Wi-Fi....
Connected to Wi-Fi
IP Address: 192.168.1.100
LITTLEFS initialized successfully.
 *** Recording Start ***
Sound recording 10%
Sound recording 50%
Sound recording 100%
Never Used Stack Size: 1224
⚠️ Notes
This code scales I2S ADC data using i2s_adc_data_scale() — tune it based on your microphone’s output.

Only one recording is stored; older files are overwritten at boot.

Make sure ESPAsyncWebServer, AsyncTCP, and LITTLEFS are properly installed in your Arduino IDE.

📚 Dependencies
Install these libraries via Library Manager or manually:

ESPAsyncWebServer

AsyncTCP

LITTLEFS (ESP32)

✅ Tested On
ESP32-WROOM-32

ICS43434 Microphone

Arduino IDE 2.x with ESP32 Board v2.x
