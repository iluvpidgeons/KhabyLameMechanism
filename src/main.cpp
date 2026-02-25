#include <Arduino.h>

/*
    This should be a clone of main.cpp, may be outdated if I forget to update it
*/

const int motor1A = GPIO_NUM_13;
const int motor2A = GPIO_NUM_14;
const int enableA = GPIO_NUM_27;
const int potpin = GPIO_NUM_33;
const int ledPin1 = GPIO_NUM_16;
const int ledPin2 = GPIO_NUM_17;
const int ledPin3 = GPIO_NUM_18;
// ill add the giant fire alarm light later

// PWM settings
const int freq = 20000; // PWM frequency: 20 kHz (Adjust 2-20 kHz as needed)
const int resolution = 8; // PWM resolution: 8 bits (dutyCycle: 0-255)

void stop(int rtime) {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor2A, LOW);
  ledcWrite(enableA, 0);
  delay(rtime);
}

void forward(int spd, int rtime) {
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor2A, LOW);
  ledcWrite(enableA, spd);
  delay(rtime);
}

void reverse(int spd, int rtime) {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor2A, HIGH);
  ledcWrite(enableA, spd);
  delay(rtime);
}

void setup() {
  Serial.begin(115200);
  pinMode(motor1A, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(potpin, INPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);

  // Set up PWM
  ledcAttach(enableA, freq, resolution);
  ledcWrite(enableA, 0);  // Start with motor stopped
  analogReadResolution(resolution);

  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);
}

void loop() {
  int sensorValue;
  sensorValue = analogRead(potpin) / 2 + 127.5;
  if (sensorValue == 127) {
    sensorValue = 0;
  }
  Serial.println(sensorValue);
  digitalWrite(ledPin3, LOW);
  digitalWrite(ledPin1, HIGH);
  delay(100);
  
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, HIGH);
  forward(sensorValue, 1000);

  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, HIGH);
  stop(1000);
}

// activate didy virus :skull: :grape: :mango: