# Autonomous Robot with Line Detection, Obstacle Avoidance, and Speed Monitoring

This project is an Arduino-based autonomous vehicle that uses infrared (IR) sensors for line detection, an ultrasonic sensor for obstacle avoidance, and an encoder to measure the speed of the robot. The motors are controlled through individual GPIO pins, and a servo is used for steering.

## 🛠️ Hardware Components

- Arduino Mega or Uno
- 2x DC motors (with motor driver, connected to GPIOs)
- 2x IR sensors (for line detection)
- Ultrasonic distance sensor (HC-SR04 or similar)
- Rotary encoder (for speed measurement)
- Servo motor (for steering)
- Power supply (battery pack)
- Wheels, chassis, and connectors

## ⚙️ Pin Configuration

| Component              | Arduino Pin     |
|------------------------|-----------------|
| IR Sensor (Left)       | 24              |
| IR Sensor (Right)      | 25              |
| Ultrasonic Trig        | 20              |
| Ultrasonic Echo        | 21              |
| Encoder Signal         | 7               |
| Servo Signal           | 28              |
| Motor Left Forward     | 12              |
| Motor Left Backward    | 11              |
| Motor Right Forward    | 10              |
| Motor Right Backward   | 9               |
| Motor Enable Left (EN1)| 13              |
| Motor Enable Right (EN2)| 8              |

## 🚀 Features

- **IR Line Detection**: Follows a path based on IR sensor input.
- **Obstacle Avoidance**: Detects obstacles using an ultrasonic sensor and can stop or turn.
- **Speed Calculation**: Uses an encoder to measure wheel revolutions and calculate speed in cm/s.
- **Manual Motor Control**: DC motors are controlled directly using digital output pins.
- **Serial Monitoring**: Speed data is printed to the serial monitor.

## 📐 Speed Calculation

The speed is calculated using:
speed = encoderCount * (1000.0 / wheelCircumference)

Where `wheelCircumference` is set to 20.0 cm and the speed is output in cm/s.

## 🔄 Logic Overview

- If both IR sensors detect white lines → Stop motors.
- If left IR sensor detects white → Turn left.
- If right IR sensor detects white → Turn left (may be an error in logic).
- If no line detected → Move forward.
- Distance is constantly measured using the ultrasonic sensor.
- Speed is calculated based on encoder pulse count.

## 📦 Required Libraries

- `Servo` (built-in with Arduino IDE)

## ⚠️ Known Issues / Improvements

- **Typo**: `digitalWrite(ultrsonicTrigPin, LOW);` is misspelled (missing `a` in `ultrasonic`).
- **IR Logic Error**: Both cases for left and right IR sensors result in a left turn (`turnLeft()`); this should be fixed to include `turnRight()` for the right sensor.
- **Motor Enable Pins** (`EN1`, `EN2`) are declared but not used for PWM speed control—add `analogWrite()` if required.

## 📈 Sample Output
Speed: 15.00 cm/s

