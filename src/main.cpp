#include <Arduino.h>

const int ledPin = 3;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  for (int i = 0; i <= 255; i++)
  {
    analogWrite(ledPin, i);
    delay(5);
  }

  for (int i = 255; i >= 0; i--)
  {
    analogWrite(ledPin, i);
    delay(5);
  }
}