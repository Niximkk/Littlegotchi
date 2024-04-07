#ifndef PANIC_H
#define PANIC_H

#include <Arduino.h>

extern bool INPANIC;

void panic(String reason);

#endif