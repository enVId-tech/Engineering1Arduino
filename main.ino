#include <math.h>

const int enA = 9;  // Enable A (PWM speed control)
const int in1 = 2;  // Input 1 (direction)
const int in2 = 3;  // Input 2 (direction)

const int in3 = 10;
const int in4 = 11;

const int greenLEDPin = 5;
const int redLEDPin = 6;
const int blueLEDPin = 7;

int sensorVal = 0;

const int numReadings = 10;   // Number of readings to tempAvg
float readings[numReadings];  // Array to store readings
int readIndex = 0;            // Index of current reading
float total = 0;              // Sum of readings
float tempAvg = 0;            // tempAvg of readings

int motionInput = 0;

float isRainDetect = 0;

int isClosed = 0;

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  pinMode(in3, INPUT);
  pinMode(in4, INPUT);

  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);

  Serial.begin(9600);

  for (int i = 0; i < numReadings; i++) {
    readings[i] = 0;  // Initialize readings array
  }
}

void loop() {
  sensorVal = analogRead(A0);

  motionInput = digitalRead(in3);

  isRainDetect = digitalRead(in4);

  float temperature = analogRead(A1) * 0.48828125;  // Replace with your temperature reading function

  total = total - readings[readIndex];        // Subtract the oldest reading
  readings[readIndex] = temperature;          // Add the new reading
  total = total + readings[readIndex];        // Add the new reading
  readIndex = (readIndex + 1) % numReadings;  // Increment index

  tempAvg = temperature * 1.8 + 32;  //total / numReadings;  // Calculate tempAvg



  // Serial.println(tempAvg);     // TempAvg on its own line
  // Serial.println(sensorVal);     // SensorVal on its own line
  // Serial.println(motionInput); // MotionInput on its own line
  // Serial.print(" isRainDetected Val: ");
  // Serial.print(isRainDetect);

  delay(30);

  if ((abs(sensorVal) < abs(1) || tempAvg < 70) && abs(isRainDetect) < 0.5) {
    motorReverse(250);
    isClosed = 0;
  } else if (abs(sensorVal) > abs(90) || tempAvg > 90 || abs(isRainDetect) > 0.5) {
    isClosed = 1;
  } else {
    isClosed = 2;
  }

  if (isClosed == 0) {
    runClosed();
  } else if (isClosed == 1) {
    runOpened();
  } else if (isClosed == 2) {
    motorStop();
  }
}

void runClosed() {
  motorReverse(250);
  setRGBColor(1);
  delay(1000);
  motorStop();
  setRGBColor(4);
}

void runOpened() {
  motorForward(250);
  setRGBColor(2);
  delay(1000);
  motorStop();
  setRGBColor(4);
}

void motorForward(int speed) {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 250);  // Speed (adjust 200 as needed)
}

void motorReverse(int speed) {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 250);  // Speed (adjust 150 as needed)
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
