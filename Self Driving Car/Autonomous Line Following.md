# Autonomous Line-Following and Obstacle-Avoiding Robot with Speed Measurement

This project is an Arduino-based robot that uses infrared (IR) sensors for line detection, an ultrasonic sensor for obstacle avoidance, and an encoder for measuring the speed of the robot. The robot is controlled using an Adafruit Motor Shield and a servo for steering.

## 🛠️ Components Used

- Arduino Mega or Uno
- Adafruit Motor Shield
- 2x DC motors (connected to motor shield channels 1 and 2)
- Servo motor (for steering, connected to pin 28)
- Ultrasonic sensor (Trig: pin 20, Echo: pin 21)
- 2x IR sensors (left: pin 24, right: pin 25)
- Rotary encoder (signal pin: 7)
- Wheels and chassis
- Power supply (battery pack)

## 🔧 Pin Configuration

| Component          | Arduino Pin |
|--------------------|-------------|
| Left IR Sensor     | 24          |
| Right IR Sensor    | 25          |
| Ultrasonic Trig    | 20          |
| Ultrasonic Echo    | 21          |
| Encoder Signal     | 7           |
| Servo Signal       | 28          |
| Left DC Motor      | Motor Shield M1 |
| Right DC Motor     | Motor Shield M2 |

## 🚀 Features

- **Obstacle Avoidance:** Uses an ultrasonic sensor to detect objects and avoid collisions.
- **Line Following:** Uses two IR sensors to detect white lines and steer accordingly.
- **Speed Measurement:** Encoder counts wheel rotations and calculates speed (cm/s).
- **Basic Movement Controls:** Forward, backward, turning, and stopping logic.

## 🧠 How It Works

1. **Obstacle Detection:** If the ultrasonic sensor detects an object <2 cm, the robot moves backward. If the distance is <5 cm, it turns right.
2. **Line Following:** Based on IR sensor readings:
   - Both sensors detect white: reverse and turn.
   - Left detects white: turn right.
   - Right detects white: turn left.
   - None detect white: go forward.
3. **Speed Calculation:** Each pulse from the encoder is counted and converted to speed using the wheel circumference.

## 📦 Libraries Required

Install these libraries in the Arduino IDE:
- `AFMotor` – For motor control with Adafruit Motor Shield
- `Servo` – For controlling the steering servo

## 💡 To Do

- Calibrate IR sensors and threshold values.
- Tune motor speeds and delays for better performance.
- Add PID control for smoother line following.
- Improve obstacle avoidance strategy.

## 📝 Notes

- Make sure your encoder is correctly wired and debounce filtering is applied if necessary.
- Confirm that your motor shield is compatible with the board and library version.
- Ensure the robot has enough power when driving both motors and the servo.

## 🔄 Example Output

Speed: 12.00 cm/s
