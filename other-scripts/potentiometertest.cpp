#include <Arduino.h>

/*
  not sure if this works yet
*/

const int motor1A = GPIO_NUM_13;
const int motor2A = GPIO_NUM_14;
const int enableA = GPIO_NUM_27;
const int potPin = GPIO_NUM_36;

// PWM settings
const int freq = 20000; // PWM frequency: 20 kHz (Adjust 2-20 kHz as needed)
const int resolution = 12; // PWM resolution: 12 bits (dutyCycle: 0-4095)

void stop(int rtime) {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor2A, LOW);
  ledcWrite(enableA, 0);
  delay(rtime);
}

void forward(int spd, int rtime = 500) {
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor2A, LOW);
  ledcWrite(enableA, spd);
  delay(rtime);
}

void reverse(int spd, int rtime = 500) {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor2A, HIGH);
  ledcWrite(enableA, spd);
  delay(rtime);
}

void setup() {
  Serial.begin(115200);
  pinMode(motor1A, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(enableA, OUTPUT);
  pinMode(potPin, INPUT);

  // Set up PWM
  ledcAttach(enableA, freq, resolution);
  ledcWrite(enableA, 0);
  analogReadResolution(resolution);
}

void loop() {
  int rawPotValue = analogRead(potPin);
  Serial.print("RawPot: ");
  Serial.print(rawPotValue);
  if (rawPotValue < 2047.5) {
    Serial.print(" Reverse: ");
    Serial.println(rawPotValue + 2047.5);
    reverse(rawPotValue + 2047.5);
  } else {
    Serial.print(" Forward: ");
    Serial.println(rawPotValue);
    forward(rawPotValue);
  }
  // stop(1000);
}