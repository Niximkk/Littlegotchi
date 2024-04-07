#include "panic.h"
#include "serial.h"
#include "keyboard.h"

bool INPANIC = false;

void panic(String reason){
    INPANIC = true;
    bleKeyboard.end(); // Se você estiver usando bleKeyboard, inclua o arquivo de cabeçalho KeyboardHandler.h
    broken(reason);
}
