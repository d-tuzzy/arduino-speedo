#include <Arduino.h>

const int SER  = 7; // Serial data input
const int SHCP = 3; // Shift register clock
const int STCP = 4; // Latch clock

// Digit wiring
const int digitA3 = 5;
const int digitA4 = 6;

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

void showBoth(int n) {
  byte pattern = number(n);

  // Digit A3
  digitalWrite(digitA4, HIGH); // Digit off
  send(pattern);
  digitalWrite(digitA3, LOW); // Digit on
  delay(5);

  // Digit A4
  digitalWrite(digitA3, HIGH); // Digit off
  send(pattern);
  digitalWrite(digitA4, LOW); // Digit on
  delay(5);
}

void setup() {
  pinMode(SER, OUTPUT);
  pinMode(SHCP, OUTPUT);
  pinMode(STCP, OUTPUT);

  pinMode(digitA3, OUTPUT);
  pinMode(digitA4, OUTPUT);

  // Turn both digits off initially
  digitalWrite(digitA3, HIGH);
  digitalWrite(digitA4, HIGH);
}

void loop() {
  for (int i = 0; i <= 9; i++) {

    unsigned long start = millis(); // Remember the start time

    // Keep refreshing the two digits for 1 second
    while (millis() - start < 1000) {
      showBoth(i);
    }
  }
}