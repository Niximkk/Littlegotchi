#define SD_CLK_PIN 0
#define SD_MISO_PIN 36
#define SD_MOSI_PIN 26
#define SD_CS_PIN 14
#define Path "/Littlegotchi"
#define FileName "/Littlegotchi/payload.txt"

#include "converter.h"
#include "keyboard.h"
#include "serial.h"
#include "panic.h"

SPIClass SPI2_SD;

void initSdCard(){
    SPI2_SD.begin(SD_CLK_PIN, SD_MISO_PIN, SD_MOSI_PIN, SD_CS_PIN);
    if (!SD.begin(SD_CS_PIN, SPI2_SD)){
        alert("Failed to mount SD card! Retrying in 5 seconds");
        unsigned timer = millis();
        while (millis() - timer < 5000) {
            initSdCard();
            alert("Retrying to mount the SD card.");
        }
    } else log("SD card mounted.");
    if (!SD.open(Path)){
        alert("Directory not found... Creating the directory.");
        if (SD.mkdir(Path)) log("Directory created successfully!");
        else panic("Failed to create the directory."); return;
    } else{
        if (!SD.open(FileName)){
            panic("Payload not found! Create a file called payload.txt @ /Littlegotchi");
            return;
        } else log("Payload found!");
    }
}

void convert(){
    File payload = SD.open(FileName);
    while (payload.available()) {
        String line = payload.readStringUntil('\n');
        String command;
        String argument;
        int separator = line.indexOf(' ');

        if (separator == -1) { line.remove(line.length() - 1); command = line; argument = "1337"; }
        else { command = line.substring(0, separator).c_str(); argument = line.substring(separator + 1).c_str(); }

        /* Keystroke Injection */
        if (command=="REM") rem(argument);
        else if (command=="STRING") bleKeyboard.print(argument);
        else if (command=="STRINGLN") bleKeyboard.println(argument);

        /* System Keys*/
        if (command=="ENTER") bleKeyboard.press(KEY_NUM_ENTER);
        else if (command=="ESCAPE") bleKeyboard.press(KEY_ESC);
        else if (command=="PAUSE") bleKeyboard.press(0xD0);
        else if (command=="PRINTSCREEN") bleKeyboard.press(KEY_PRTSC);
        else if (command=="MENU") bleKeyboard.press(0xED);

        /* Cursor Keys */
        if (command=="UP" || command=="UPARROW") bleKeyboard.press(KEY_UP_ARROW);
        else if (command=="DOWN" || command=="DOWNARROW") bleKeyboard.press(KEY_DOWN_ARROW);
        else if (command=="LEFT" || command=="LEFTARROW") bleKeyboard.press(KEY_LEFT_ARROW);
        else if (command=="RIGHT" || command=="RIGHTARROW") bleKeyboard.press(KEY_RIGHT_ARROW);
        else if (command=="BACKSPACE") bleKeyboard.press(KEY_BACKSPACE);
        else if (command=="PAGEUP") bleKeyboard.press(KEY_PAGE_UP);
        else if (command=="PAGEDOWN") bleKeyboard.press(KEY_PAGE_DOWN);
        else if (command=="DELETE" || command=="DEL") bleKeyboard.press(KEY_DELETE);
        else if (command=="TAB") bleKeyboard.press(KEY_TAB);
        else if (command=="INSERT") bleKeyboard.press(KEY_INSERT);
        else if (command=="HOME") bleKeyboard.press(KEY_HOME);
        else if (command=="END") bleKeyboard.press(KEY_END);
        else if (command=="SPACE") bleKeyboard.print(" ");

        /* All the F's*/
        if (command=="F1") bleKeyboard.press(KEY_F1);
        else if (command=="F2") bleKeyboard.press(KEY_F2);
        else if (command=="F3") bleKeyboard.press(KEY_F3);
        else if (command=="F4") bleKeyboard.press(KEY_F4);
        else if (command=="F5") bleKeyboard.press(KEY_F5);
        else if (command=="F6") bleKeyboard.press(KEY_F6);
        else if (command=="F7") bleKeyboard.press(KEY_F7);
        else if (command=="F8") bleKeyboard.press(KEY_F8);
        else if (command=="F9") bleKeyboard.press(KEY_F9);
        else if (command=="F10") bleKeyboard.press(KEY_F10);
        else if (command=="F11") bleKeyboard.press(KEY_F11);
        else if (command=="F12") bleKeyboard.press(KEY_F12);
        
        /* Modifier Keys */
        if (command=="SHIFT") bleKeyboard.press(KEY_LEFT_SHIFT);
        else if (command=="ALT") bleKeyboard.press(KEY_LEFT_ALT);
        else if (command=="CONTROL" || command=="CTRL") bleKeyboard.press(KEY_LEFT_CTRL);
        else if (command=="COMMAND" || command=="WINDOWS" || command=="GUI") bleKeyboard.press(KEY_LEFT_GUI);
        
        /* Lock Keys */
        if (command=="CAPSLOCK") bleKeyboard.write(KEY_CAPS_LOCK);
        else if (command=="NUMLOCK") bleKeyboard.write(0xDB);
        else if (command=="SCROLLOCK") bleKeyboard.write(0xCF);

        /* Delays */
        if (command=="DELAY") delay(argument.toInt());

        /* All of the Littlegotchi things */
        if (command=="DISCONNECT") bleKeyboard.end(); // Doesn't work.
        else if (command=="RELEASE") bleKeyboard.releaseAll();
        else if (command=="NEXTTRACK") bleKeyboard.write(KEY_MEDIA_NEXT_TRACK);
        else if (command=="PREVTRACK") bleKeyboard.write(KEY_MEDIA_PREVIOUS_TRACK);
        else if (command=="STOPTRACK") bleKeyboard.write(KEY_MEDIA_STOP);
        else if (command=="PAUSETRACK") bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
        else if (command=="MUTE") bleKeyboard.write(KEY_MEDIA_MUTE);
        else if (command=="VOLUMEUP") bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
        else if (command=="CALC") bleKeyboard.write(KEY_MEDIA_CALCULATOR);
    }
    payload.close();
}