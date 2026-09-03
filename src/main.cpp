#include <Arduino.h>

const int hallPin = 2;

// The wheel's circumference is 0.78m and there are 15 pulses per revolution
const float distancePerPulse = 0.78 / 15.0;

volatile unsigned long lastPulse = 0; // Time of the previous sensor pulse
volatile unsigned long pulseTime = 0; // Time between the last two pulses

void pulse() {
  unsigned long now = micros(); // Get current time in microseconds

  if (now - lastPulse < 2000) {
    return; // Ignore pulses that are too close together
  }

  pulseTime = now - lastPulse; // Calculate time since previous pulse
  lastPulse = now; // Save time of this pulse
}

void setup() {
  Serial.begin(115200);

  pinMode(hallPin, INPUT_PULLUP); // Set Hall sensor pin as an input

  // Run pulse() whenever the Hall sensor changes from HIGH to LOW
  attachInterrupt(digitalPinToInterrupt(hallPin), pulse, FALLING);
}

void loop() {
  unsigned long timeSincePulse;
  unsigned long interval;

  // Temporarily stop interrupts while copying these values
  noInterrupts();

  timeSincePulse = micros() - lastPulse;
  interval = pulseTime;

  interrupts();

  float speed = 0;

  // If a pulse has been received recently, calculate speed in mph
  if (interval > 0 && timeSincePulse < 1000000) {
    // Calculates m/s and then converts to mph
    speed = (distancePerPulse / (interval / 1000000.0)) * 2.23694;
  }

  Serial.println(speed, 1); // Print speed to 1 d.p.

  delay(100); // Update speed every 100 ms
}