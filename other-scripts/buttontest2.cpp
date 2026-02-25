#include <Arduino.h>

/*
  This does not work yet
  I plan for the button to toggle the LED
*/

const int buttonpin = GPIO_NUM_23;
const int ledPin3 = GPIO_NUM_18;

int buttonState;
int ledState = HIGH;

void changestateBinary(int target) {
    if (target == LOW) {
      target = HIGH;
    }
    else {
      target = LOW;
    }
}

void setup() {
  Serial.begin(115200);
  pinMode(buttonpin, INPUT_PULLUP);
  pinMode(ledPin3, OUTPUT);
}

void loop() {
  int buttonState = digitalRead(buttonpin);
  if (buttonState == LOW) {
    changestateBinary(ledState);  }
    while (digitalRead(buttonpin) == LOW) {
      delay(10);
    }
}
