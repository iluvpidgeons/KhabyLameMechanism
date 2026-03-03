#include <Arduino.h>

/*
  I dont understand a lot of this code bro
  Not fixed yet but the plan is for the button to swap the direction

  Components:
  Motor with Motor Driver (L298N)
  Potentiometer (for speed control)
  Button (for direction control)
*/

// pins
const int motor1A = GPIO_NUM_13;
const int motor2A = GPIO_NUM_14;
const int enableA = GPIO_NUM_27;
const int potpin = GPIO_NUM_36;
const int buttonpin = GPIO_NUM_23;

// PWM settings
const int freq = 20000; // PWM frequency: 20 kHz (Adjust 2-20 kHz as needed)
const int resolution = 8; // PWM resolution: 8 bits (dutyCycle: 0-255)

// button state variables
int lastButtonState = HIGH;
int buttonState = LOW;


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

// void momentaryLight() {
//   int buttonState = digitalRead(buttonpin);

//   if (buttonState == LOW) {
  
//   }
//   else {
  
//   }
// }

void changestate() {
    if (buttonState == LOW) {
      buttonState = HIGH;
    }
    else {
      buttonState = LOW;
    }
}

// void lightSwitch() {  
//   int buttonState = digitalRead(buttonpin);

//     if (buttonState != lastButtonState) {
//         lastButtonState = buttonState;
//         if (buttonState == HIGH) {
//         changestate();
//         }
//     }
// }

// void lightSwitchDebounced() {
//   button.update();
//   if (button.released()) { // button pressed
//     changestate();
//   }
// }

void setup() {
  Serial.begin(115200);
  pinMode(motor1A, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(potpin, INPUT);
//   button.attach(buttonpin, INPUT_PULLUP);
//   button.interval(25);
  pinMode(buttonpin, INPUT_PULLUP);

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
  buttonState = digitalRead(buttonpin);
  if (buttonState != lastButtonState) {
    lastButtonState = buttonState;
  }
//   lightSwitchDebounced();
  if (buttonState == LOW) {
    forward(sensorValue, 500);
  }
  else {
    reverse(sensorValue, 500);
  } 
  // stop(1000);
}

// activate didy virus :skull: :grape: :mango: