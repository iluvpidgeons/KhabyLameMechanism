#include <Arduino.h>

/*
  Not finished
*/

const int micPin = GPIO_NUM_39;
const int ledPin1 = GPIO_NUM_16;
const int ledPin2 = GPIO_NUM_17;
const int ledPin3 = GPIO_NUM_18;

const int resolution = 12;
int micValue;

void setup() {
  Serial.begin(115200);
  analogReadResolution(resolution);
}

void loop() {
  micValue = analogRead(micPin);
  Serial.println(micValue);
  delay(100);
}