#include <Arduino.h>

// Segments of the digits
int ASeg = 9;
int BSeg = 13;
int CSeg = 4;
int DSeg = 6;
int ESeg = 7;
int FSeg = 8;
int GSeg = 3;

// Decimal points
int DPSeg = 5;

// Digits
int a1 = 10;
int a2 = 11;
int a3 = 12;
int a4 = 2;

int segments[] = {
  ASeg, BSeg, CSeg, DSeg,
  ESeg, FSeg, GSeg, DPSeg
};

int digits[] = {
  a1, a2, a3, a4
};

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(segments[i], OUTPUT);
    digitalWrite(segments[i], HIGH); // Segments OFF
  }

  for (int i = 0; i < 4; i++) {
    pinMode(digits[i], OUTPUT);
    digitalWrite(digits[i], LOW); // Digits OFF
  }
}

// Go through each segment in each digit, one by one
void loop() {
  for (int d = 0; d < 4; d++) {

    digitalWrite(digits[d], HIGH); // Turn this digit ON

    digitalWrite(ASeg, LOW);
    delay(100);
    digitalWrite(ASeg, HIGH);

    digitalWrite(BSeg, LOW);
    delay(100);
    digitalWrite(BSeg, HIGH);

    digitalWrite(CSeg, LOW);
    delay(100);
    digitalWrite(CSeg, HIGH);

    digitalWrite(DSeg, LOW);
    delay(100);
    digitalWrite(DSeg, HIGH);

    digitalWrite(ESeg, LOW);
    delay(100);
    digitalWrite(ESeg, HIGH);

    digitalWrite(FSeg, LOW);
    delay(100);
    digitalWrite(FSeg, HIGH);

    digitalWrite(GSeg, LOW);
    delay(100);
    digitalWrite(GSeg, HIGH);

    digitalWrite(DPSeg, LOW);
    delay(100);
    digitalWrite(DPSeg, HIGH);

    digitalWrite(digits[d], LOW); // Turn digit OFF
  }
}