#include <Arduino.h>

const int throttlePin = A0;
const int ledPin = 3;

void setup() {
  Serial.begin(115200); // Allows communication between computer at 115200 bits/second
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int input = analogRead(throttlePin);

  Serial.print(input);

  int brightness = map(input, 168, 726, 0, 255); // Scale input to 0-255 range (proportionally)
  brightness = constrain(brightness, 0, 255); // Prevent values escaping the range

  analogWrite(ledPin, brightness);
  delay(50);
}