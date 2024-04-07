#ifndef SERIAL_H
#define SERIAL_H

#include <Arduino.h>

void initSerial();
void log(String message);
void alert(String message);
void broken(String message);

#endif