#include "display.h"
#include "keyboard.h"
#include "serial.h"
#include "converter.h"

bool attacking = false;

BleKeyboard bleKeyboard("Littlegotchi!", "ImNix");

void initKeyboard(){
    bleKeyboard.begin();
    log("Keyboard initialized.");
}

void loopKeyboard(){
    attackSniff();
    updateBattery();
}

void attackSniff(){
    if(bleKeyboard.isConnected()){ log("Sending payload."); convert(); log("Payload sent, repeating..."); }
}

void updateBattery(){
	float b = M5.Axp.GetVbatData() * 1.1 / 1000;
	bleKeyboard.setBatteryLevel(((b - 3.0) / 1.2) * 100);
}