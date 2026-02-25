#include <Arduino.h>

const int buttonpin = GPIO_NUM_23;
const int ledPin3 = GPIO_NUM_18;

void setup() {
  Serial.begin(115200);
  pinMode(buttonpin, INPUT_PULLUP);
  pinMode(ledPin3, OUTPUT);
}

void loop() {
  int buttonState = digitalRead(buttonpin);
  if (buttonState == LOW) {
    digitalWrite(ledPin3, HIGH);
    Serial.println("Button Pressed");
  } else {
    digitalWrite(ledPin3, LOW);
    Serial.println("Button Released");
  }
}
