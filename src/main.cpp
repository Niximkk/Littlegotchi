#include <Arduino.h>
#include <M5StickCPlus.h>
#include "serial.h"
#include "display.h"
#include "keyboard.h"
#include "converter.h"

void setup() {
  M5.begin();
  initSerial();
  initDisplay();
  initSdCard();
  initKeyboard();
}
void loop() {
  M5.update();
}