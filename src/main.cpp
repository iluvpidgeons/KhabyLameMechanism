#include <Arduino.h>
#include "pitches.h"

const int motor1A = GPIO_NUM_13;
const int motor2A = GPIO_NUM_14;
const int enableA = GPIO_NUM_27;
const int ledPin1 = GPIO_NUM_16;
const int ledPin2 = GPIO_NUM_17;
const int ledPin3 = GPIO_NUM_18;
const int buzzerPin = GPIO_NUM_19;
// const int potPin = GPIO_NUM_36;
const int micPin = GPIO_NUM_39;

// PWM settings
const int freq = 20000; // PWM frequency: 20 kHz (Adjust 2-20 kHz as needed)
const int resolution = 12; // PWM resolution: 12 bits (dutyCycle: 0-4095)

const int sampleWindow = 50;
unsigned int sample;

const int threshold = 1000; // Placeholder threshold for sound level, I am not able to test it right now

void stop(int rtime = 0) {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor2A, LOW);
  ledcWrite(enableA, 0);
  delay(rtime);
}

void forward(int spd, int rtime) {
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor2A, LOW);
  ledcWrite(enableA, spd);
  for (int i = 0; i < 20; i++) {
    leds(random(2), random(2), random(2));
    delay(rtime / 20);
  }
}

// void reverse(int spd, int rtime) {
//   digitalWrite(motor1A, LOW);
//   digitalWrite(motor2A, HIGH);
//   ledcWrite(enableA, spd);
//   delay(rtime);
// }

void leds(bool ledState1 = LOW, bool ledState2 = LOW, bool ledState3 = LOW) {
  digitalWrite(ledPin1, ledState1);
  digitalWrite(ledPin2, ledState2);
  digitalWrite(ledPin3, ledState3);
}

void setup() {
  Serial.begin(115200);
  pinMode(motor1A, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(enableA, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  // pinMode(potPin, INPUT);
  pinMode(micPin, INPUT);

  // Set up motor PWM
  ledcAttach(enableA, freq, resolution);
  ledcWrite(enableA, 0);  // Start with motor stopped
  analogReadResolution(resolution);

  leds();
}

void loop() {
  unsigned long startMillisMic = millis();  // Start of sample window
  unsigned int peakToPeak = 0;   // peak-to-peak level

  unsigned int signalMax = 0;
  unsigned int signalMin = 4095;

  //  collect data for 50 mS
  while (millis() - startMillisMic < sampleWindow) {
    sample = analogRead(micPin);
    if (sample < 4095) { // toss out spurious readings
      if (sample > signalMax) {
        signalMax = sample;  // save just the max levels
      } else if (sample < signalMin) {
        signalMin = sample;  // save just the min levels
      }
    }
  }
  peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
  Serial.println(peakToPeak);
  
  // I will change so you need to scream to make the LEDs light up one by one and then activate, but that will be difficult due to delays messing up the microphone scripts
  
  if (peakToPeak > threshold) {
    tone(buzzerPin, NOTE_A1);
    forward(4095, 5000);
  }
  stop();
  leds();
  noTone(buzzerPin);
}