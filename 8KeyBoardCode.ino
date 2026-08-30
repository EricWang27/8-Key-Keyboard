#include <Arduino.h>

const byte ROWS = 2;
const byte COLS = 4;

byte rowPins[ROWS] = {5, 6};
byte colPins[COLS] = {1, 2, 3, 4};

char keymap[ROWS][COLS] = {
  {'1','2','3','4'},
  {'5','6','7','8'}
};

bool keyState[ROWS][COLS] = {false};

void setup() {
  Serial.begin(115200);
  delay(2000);

  Serial.println("Keyboard ready");

  for (byte r = 0; r < ROWS; r++) {
    pinMode(rowPins[r], OUTPUT);
    digitalWrite(rowPins[r], HIGH);
  }

  for (byte c = 0; c < COLS; c++) {
    pinMode(colPins[c], INPUT_PULLUP);
  }
}

void loop() {
  for (byte r = 0; r < ROWS; r++) {

    digitalWrite(rowPins[r], LOW);

    delayMicroseconds(50);

    for (byte c = 0; c < COLS; c++) {

      bool pressed = (digitalRead(colPins[c]) == LOW);

      if (pressed && !keyState[r][c]) {
        Serial.print("Pressed: ");
        Serial.println(keymap[r][c]);
      }

      keyState[r][c] = pressed;
    }

    digitalWrite(rowPins[r], HIGH);
  }

  delay(10);
}