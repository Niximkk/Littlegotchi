#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <Arduino.h>
#include <BleKeyboard.h>

extern BleKeyboard bleKeyboard;

void initKeyboard();
void lookForFool();

#endif