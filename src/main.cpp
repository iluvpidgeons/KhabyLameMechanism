#include <Arduino.h>
#include "ESP_Music.h"
#include "Melody.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

bool DEBUG = true; // Activates serial prints
// Sample window width in ms (50ms = 20Hz) for measuring sound amplitude. Adjust this based on how responsive you want the LEDs to be.
// Shorter windows will be more responsive but may be more affected by noise, while longer windows will be smoother but less responsive.
const int sampleWindow = 50;
const int threshold = 2500; // Amplitude threshold to consider as "loud". Adjust this based on your microphone's sensitivity and environment noise level.
const unsigned long interval = 100; // How long you need to scream to light up the next led (in ms)
const int cylonInterval = 100; // Interval for the Cylon LED pattern in ms

// pins
const int ledPins[] = {
GPIO_NUM_32, 
GPIO_NUM_33, 
GPIO_NUM_25, 
GPIO_NUM_26,
GPIO_NUM_27,
GPIO_NUM_14};
const int numLeds = sizeof(ledPins) / sizeof(ledPins[0]);
const int micPin = GPIO_NUM_35;
const int buzzerPin = GPIO_NUM_12;
const int motor1A = GPIO_NUM_18;
const int motor2A = GPIO_NUM_17;
const int enableA = GPIO_NUM_16;

// ADC resolution
const int resolution = 12;
const int freq = 20000;

// timer variables
unsigned long stepMillis = 0;
int litCount = 0; // number of LEDs currently ON (0..numLeds)
bool wasLoud = false;
bool khabyTriggered = false;
volatile bool playMusic = false;

MusicPlayer player(buzzerPin, bpm);

void forward(int spd = 4095) {
    digitalWrite(motor1A, HIGH);
    digitalWrite(motor2A, LOW);
    ledcWrite(enableA, spd);
}

void stop() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor2A, LOW);
  ledcWrite(enableA, 0);
}

void musicTask(void *pvParameters) {
    for(;;) { // Tasks must loop forever
        if (playMusic) {
            player.play(melody, melodyLength);
            playMusic = false; // Stop after playing once, or create a counter to repeat as needed
        }
        // Small delay to prevent the watchdog timer from barking
        vTaskDelay(pdMS_TO_TICKS(100)); 
    }
}

void runCylonScanner() {
  // Static variables remember their state between loop iterations
  static unsigned long lastUpdate = 0;
  static int currentLed = 0;
  static int direction = 1;

  // Non-blocking timer check
  if (millis() - lastUpdate >= cylonInterval) {
    lastUpdate = millis();

    // 1. Turn off all LEDs
    for (int i = 0; i < numLeds; i++) {
      digitalWrite(ledPins[i], LOW);
    }

    // 2. Turn on the active LED
    digitalWrite(ledPins[currentLed], HIGH);

    // 3. Logic to bounce back and forth
    currentLed += direction;
    if (currentLed >= numLeds - 1 || currentLed <= 0) {
      direction *= -1; // Reverse direction
    }
  }
}


void initiateKhaby() {
    playMusic = true;

    while (playMusic) {
        // TODO: add your mechanism trigger here
        forward();
        runCylonScanner();
        // Yield to let other tasks (like musicTask) run.
        vTaskDelay(pdMS_TO_TICKS(1));
    }

    // Reset LEDs/state after the sequence so the main state machine isn't out-of-sync
    // with whatever the scanner left on.
    for (int i = 0; i < numLeds; i++) {
        digitalWrite(ledPins[i], LOW);
    }
    litCount = 0;
    stop();
}


unsigned int readMicAmplitude() {
    const unsigned long startMillis = millis();

    unsigned int signalMax = 0;
    unsigned int signalMin = 4095;

    while (millis() - startMillis < sampleWindow) {
        const unsigned int sample = analogRead(micPin);

        if (sample < 4095) {
            if (sample > signalMax) {
                signalMax = sample;
            } else if (sample < signalMin) {
                signalMin = sample;
            }
        }
    }

    // max - min = peak-peak amplitude (guard against unsigned underflow)
    if (signalMax >= signalMin) {
        return signalMax - signalMin;
    }
    return 0;
}

void updateLedState(const bool loud, const unsigned long now) {
    if (loud != wasLoud) {
        stepMillis = now;
        wasLoud = loud;
    }

    if (loud) {
        if (litCount < numLeds) {
            khabyTriggered = false;
            if (now - stepMillis >= interval) {
                digitalWrite(ledPins[litCount], HIGH);
                litCount++;
                stepMillis = now;
            }
        } else {
            if (!khabyTriggered && (now - stepMillis >= interval)) {
                initiateKhaby();
                khabyTriggered = true;
                stepMillis = now;
            }
        }
    } else {
        khabyTriggered = false;
        if (litCount > 0 && (now - stepMillis >= interval)) {
            litCount--;
            digitalWrite(ledPins[litCount], LOW);
            stepMillis = now;
        }
    }
}

void setup() {
    Serial.begin(115200);
    analogReadResolution(resolution);
    pinMode(micPin, INPUT); 
    for (int i = 0; i < numLeds; i++) {
        pinMode(ledPins[i], OUTPUT);
        digitalWrite(ledPins[i], LOW);
    }
    pinMode(motor1A, OUTPUT);
    pinMode(motor2A, OUTPUT);
    ledcAttach(enableA, freq, resolution);
    ledcWrite(enableA, 0);  // Start with motor stopped

    // Start the music task so initiateKhaby() can actually complete.
    xTaskCreatePinnedToCore(
        musicTask,
        "musicTask",
        4096,
        nullptr,
        1,
        nullptr,
        0
    );
}

void loop() {
    const unsigned long now = millis();
    const unsigned int micAmplitude = readMicAmplitude();

    if (DEBUG) {
        Serial.println(micAmplitude);
    }

    updateLedState(micAmplitude > threshold, now);

}