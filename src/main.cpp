#include <Arduino.h>

const int SER  = 7;
const int SHCP = 3;
const int STCP = 4;

const int digit3 = 6;
const int digit4 = 5;

void show(byte value) {
  digitalWrite(STCP, LOW);
  shiftOut(SER, SHCP, LSBFIRST, value);
  digitalWrite(STCP, HIGH);
}

void setup() {
  pinMode(SER, OUTPUT);
  pinMode(SHCP, OUTPUT);
  pinMode(STCP, OUTPUT);

  pinMode(digit3, OUTPUT);
  pinMode(digit4, OUTPUT);

  digitalWrite(digit3, HIGH);
  digitalWrite(digit4, HIGH);
}

void loop() {
  show(191);  // A
  delay(1000);

  show(223);  // B
  delay(1000);

  show(239);  // C
  delay(1000);

  show(247);  // D
  delay(1000);

  show(251);  // E
  delay(1000);

  show(253);  // F
  delay(1000);

  show(254);  // G
  delay(1000);

  show(127);  // DP
  delay(1000);
}