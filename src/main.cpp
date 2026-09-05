#include <Arduino.h>

// 74HC595 control pins
const int SER  = 7;  // Serial data input
const int SHCP = 3;  // Shift register clock
const int STCP = 4;  // Latch clock

// Digit wiring
const int digitA3 = 5;
const int digitA4 = 6;

// Hall sensor
const int hallPin = 2;

// Wheel circumference / 15 pulses per revolution
const float distancePerPulse = 0.78 / 15.0;

// Hall sensor timing
volatile unsigned long lastPulse = 0;
volatile unsigned long pulseTime = 0;

// Segment mapping
const byte segA = 191;
const byte segB = 223;
const byte segC = 239;
const byte segD = 247;
const byte segE = 251;
const byte segF = 253;
const byte segG = 254;

// Convert a number into a 7-segment pattern
byte number(int n) {
  switch (n) {
    case 0: return segA & segB & segC & segD & segE & segF;
    case 1: return segB & segC;
    case 2: return segA & segB & segD & segE & segG;
    case 3: return segA & segB & segC & segD & segG;
    case 4: return segB & segC & segF & segG;
    case 5: return segA & segC & segD & segF & segG;
    case 6: return segA & segC & segD & segE & segF & segG;
    case 7: return segA & segB & segC;
    case 8: return segA & segB & segC & segD & segE & segF & segG;
    case 9: return segA & segB & segC & segD & segF & segG;
  }

  return 255; // All segments off
}

void send(byte value) {
  digitalWrite(STCP, LOW);
  shiftOut(SER, SHCP, LSBFIRST, value);
  digitalWrite(STCP, HIGH);
}

// Show a number on A3 and A4
void showNumber(int value) {
  // Keep the speed between 0 and 99
  if (value > 99) value = 99;
  if (value < 0) value = 0;

  // If the number is only one digit, use A4 only
  if (value < 10) {
    digitalWrite(digitA3, HIGH); // A3 off
    send(number(value));
    digitalWrite(digitA4, LOW);  // A4 on
    delay(5);
  }
  
  else {
    // Separate the number into tens and ones
    int tens = value / 10;
    int ones = value % 10;

    // Digit A3
    digitalWrite(digitA4, HIGH);
    send(number(tens));
    digitalWrite(digitA3, LOW);
    delay(5);

    // Digit A4
    digitalWrite(digitA3, HIGH);
    send(number(ones));
    digitalWrite(digitA4, LOW);
    delay(5);
  }
}

void pulse() {
  unsigned long now = micros(); // Get current time in microseconds

  if (now - lastPulse < 2000) {
    return; // Ignore pulses that are too close together
  }

  pulseTime = now - lastPulse; // Calculate time since previous pulse
  lastPulse = now; // Save time of this pulse
}

void setup() {
  // 74HC595 pins
  pinMode(SER, OUTPUT);
  pinMode(SHCP, OUTPUT);
  pinMode(STCP, OUTPUT);

  // Display digit pins
  pinMode(digitA3, OUTPUT);
  pinMode(digitA4, OUTPUT);

  // Turn both digits off initially
  digitalWrite(digitA3, HIGH);
  digitalWrite(digitA4, HIGH);

  // Hall sensor
  pinMode(hallPin, INPUT_PULLUP);

  // Run pulse() whenever the Hall sensor changes from HIGH to LOW
  attachInterrupt(digitalPinToInterrupt(hallPin), pulse, FALLING);
}

void loop() {
  unsigned long timeSincePulse;
  unsigned long interval;

  noInterrupts(); // Temporarily stop interrupts while copying these values
  timeSincePulse = micros() - lastPulse;
  interval = pulseTime;
  interrupts();

  float speed = 0;

  // If a pulse has been received recently
  if (interval > 0 && timeSincePulse < 1000000) {
    // Calculate m/s and then converts to mph
    speed = (distancePerPulse / (interval / 1000000.0)) * 2.23694;
  }

  int speedDisplay = (int)(speed + 0.5); // Round speed to the nearest whole number

  Serial.println(speedDisplay); // Print speed to Serial monitor

  // Keep refreshing the display
  unsigned long start = millis();

  // Keep refreshing the two digits for 100ms
  while (millis() - start < 100) {
    showNumber(speedDisplay);
  }
}