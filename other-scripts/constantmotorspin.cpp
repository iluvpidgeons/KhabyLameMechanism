#include <Arduino.h>

/*
    Components:
    Motor with Motor Driver (L298N)
    Potentiometer (for speed control)
*/

int motor1A = GPIO_NUM_13;
int motor2A = GPIO_NUM_14;
int enableA = GPIO_NUM_27;
int potpin = GPIO_NUM_33;

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

  // Set up PWM
  ledcAttach(enableA, freq, resolution);
  ledcWrite(enableA, 0);  // Start with motor stopped
  analogReadResolution(resolution);
}

void loop() {
  int sensorValue;
  sensorValue = analogRead(potpin) / 2 + 127.5;
  if (sensorValue == 127) {
    sensorValue = 0;
  }
  Serial.println(sensorValue);
  forward(sensorValue, 500);
  // stop(1000);
}

// activate didy virus :skull: :grape: :mango: