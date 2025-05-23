# 🔌 ESP32 IoT LED Controller with Adafruit IO

This project connects an ESP32 (or ESP8266) board to [Adafruit IO](https://io.adafruit.com) via Wi-Fi to receive remote commands from a shared feed and control an LED accordingly.

---

## 📦 Features

- Connects to Wi-Fi and Adafruit IO
- Subscribes to a shared feed named `var`
- Listens for integer values from the feed
- Reads the value and prints it to the serial monitor
- (Extendable) Use the value to control an onboard or external LED

---

## 🧰 Requirements

- ESP32 or ESP8266 board
- Adafruit IO account
- Arduino IDE with the following libraries installed:
  - `Adafruit IO Arduino`
  - `WiFi` (board-specific)

---

## 🔐 Credentials

Update the following macros in your code with your own Adafruit IO and Wi-Fi credentials:

```cpp
#define IO_USERNAME "your_adafruit_io_username"
#define IO_KEY "your_adafruit_io_key"
#define WIFI_SSID "your_wifi_name"
#define WIFI_PASS "your_wifi_password"

✅ Credentials are hidden in this repository version for security reasons.

🛠️ Pin Configuration
Component	Pin
LED	13

🔁 Code Behavior
Connects to the specified Wi-Fi network

Connects to Adafruit IO using provided credentials

Subscribes to a shared feed (var) owned by dns_das

When data is received on the feed, handleMessage() is triggered

Value is printed via serial:

text
Copy
Edit
received <- 1
💡 You can extend handleMessage() to toggle LED_PIN1 based on the received value:

cpp
Copy
Edit
digitalWrite(LED_PIN1, val == 1 ? HIGH : LOW);

