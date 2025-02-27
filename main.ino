#include <math.h>

const int enA = 9;  // Enable A (PWM speed control)
const int in1 = 2;  // Input 1 (direction)
const int in2 = 3;  // Input 2 (direction)

const int greenLEDPin = 5;
const int redLEDPin = 6;
const int blueLEDPin = 7;

int sensorVal = 0;
int tempVal = 17;

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  sensorVal = analogRead(A0);
  tempVal = analogRead(A1) * 0.48828125;

  // Serial.println(sensorVal);
  Serial.println(tempVal);

  delay(10);

  if (abs(sensorVal) > abs(220) || tempVal > 80) {
    motorForward(150);
    setRGBColor(2);
    delay(25);
  } else if (abs(sensorVal) < abs(150) || tempVal < 68) {
    motorReverse(150);
    setRGBColor(3);
    delay(25);
  } else {
    motorStop();
    setRGBColor(4);
    delay(25);
  }
}

void motorForward(int speed) {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, abs(speed));  // Speed (adjust 200 as needed)
}

void motorReverse(int speed) {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, abs(speed));  // Speed (adjust 150 as needed)
}

void motorStop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(enA, 0);  // Speed 0 (motor off)
}

void setRGBColor(int input) {
  if (input == 1) {
    analogWrite(redLEDPin, 255);
    analogWrite(blueLEDPin, 0);
    analogWrite(greenLEDPin, 0);
  } else if (input == 2) {
    analogWrite(redLEDPin, 0);
    analogWrite(blueLEDPin, 0);
    analogWrite(greenLEDPin, 255);
  } else if (input == 3) {
    analogWrite(redLEDPin, 0);
    analogWrite(blueLEDPin, 255);
    analogWrite(greenLEDPin, 0);
  } else if (input == 4) {
    analogWrite(redLEDPin, 255);
    analogWrite(blueLEDPin, 255);
    analogWrite(greenLEDPin, 255);
  } else {
    analogWrite(redLEDPin, 0);
    analogWrite(blueLEDPin, 0);
    analogWrite(greenLEDPin, 0);
  }
}
