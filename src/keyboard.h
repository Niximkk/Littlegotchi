#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <Arduino.h>
#include <BleKeyboard.h>

extern bool attacking;

extern BleKeyboard bleKeyboard;

void initKeyboard();
void loopKeyboard();
void attackSniff();
void updateBattery();

#endif