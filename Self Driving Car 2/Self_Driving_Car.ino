#include <Servo.h>

//Pin definitions
int leftIRPin = 24;
int rightIRPin = 25;
int ultrasonicTrigPin = 20;
int ultrasonicEchoPin = 21;

int servoPin = 28;
int motorLeftForwardPin = 12; 
int motorLeftBackwardPin = 11; 
int motorRightForwardPin = 10; 
int motorRightBackwardPin = 9; 
int motorEN1 = 13;
int motorEn2 = 8;

int encoderPin = 7;
int encoderCount = 0; //counter for encoder pulses
float wheelCircumference = 20.0; //in centimeters
float speedConstant = 1000.0 / wheelCircumference; //Conversion factor (ms to seconds)


Servo steeringServo;

void setup() {

  pinMode(leftIRPin, INPUT);
  pinMode(rightIRPin, INPUT);

  pinMode(ultrasonicEchoPin, INPUT);
  pinMode(ultrasonicTrigPin, OUTPUT);

  pinMode(encoderPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderPin), updateEncoder, RISING);
  Serial.begin(9600);
  
  pinMode(motorLeftForwardPin, OUTPUT);
  pinMode(motorLeftBackwardPin, OUTPUT);
  pinMode(motorRightForwardPin, OUTPUT);
  pinMode(motorRightBackwardPin, OUTPUT);
  pinMode(motorEN1, OUTPUT);
  pinMode(motorEn2, OUTPUT);

  steeringServo.attach(servoPin);

}

void loop() {
  
  //Read IR sensor values
  int leftIRValue = digitalRead(leftIRPin);
  int rightIRValue = digitalRead(rightIRPin);

  //Adjusting motor control based on IR sensor values (lane detection)
  int threshold = 500;

  if (leftIRValue > threshold && rightIRValue > threshold) {
    //Both sensors detect white line (stop)
    stopMotors();
  } else if (leftIRValue > threshold) {
    //Left sensor detects white line (turn right)
    turnLeft();
  } else if (rightIRValue > threshold){
    //Right sensor detects white line (turn left)
    turnLeft();
  } else {
    //No white line detected (go forward)
    goForward();
  }


  //Read ultrasonic distance
  long duration, distance;
  digitalWrite(ultrsonicTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(ultrasonicTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultrsonicTrigPin, LOW);
  duration = pulseIn(ultrasonicEchoPin, HIGH);
  distance = duration * 0.034 / 2;


  //Read encoder pulses
  //Calculate speed (in cm/s)
  float speed = encoderCount * speedConstant;
  Serial.print(" Speed: ");
  Serial.print(speed);
  Serial.println(" cm/s ");
  delay(1000);

}

void goForward() {

  digitalWrite(motorLeftForwardPin, HIGH);
  digitalWrite(motorLeftBackwardPin, LOW);
  digitalWrite(motorRightForwardPin, HIGH);
  digitalWrite(motorRightBackwardPin, LOW);

}

void turnLeft() {

  digitalWrite(motorLeftForwardPin, LOW);
  digitalWrite(motorLeftBackwardPin, HIGH);
  digitalWrite(motorRightForwardPin, HIGH);
  digitalWrite(motorRightBackwardPin, LOW);

}

void turnRight() {

  digitalWrite(motorLeftForwardPin, HIGH);
  digitalWrite(motorLeftBackwardPin, LOW);
  digitalWrite(motorRightForwardPin, LOW);
  digitalWrite(motorRightBackwardPin, HIGH);

}

void stopMotors() {

  digitalWrite(motorLeftForwardPin, LOW);
  digitalWrite(motorLeftBackwardPin, LOW);
  digitalWrite(motorRightForwardPin, LOW);
  digitalWrite(motorRightBackwardPin, LOW);

}

void updateEncoder () {
  if (digitalRead(encoderPin) == HIGH) {
    encoderCount++;
  } else {
    encoderCount--;
  }
}
