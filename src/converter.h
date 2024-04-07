#ifndef CONVERTER_H
#define CONVERTER_H

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

extern SPIClass SPI2_SD;

void initSdCard();
void convert();

#endif
