#include "keyboard.h"
#include "serial.h"

void initKeyboard(){
    bleKeyboard.setName("Littlegotchi!");
    bleKeyboard.begin();
    log("Keyboard initialized.");
}

void lookForFool(){
    if(bleKeyboard.isConnected()) {
        log("Fool found.");
    }

}