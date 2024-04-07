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
    } else{
        log("SD card mounted.");
    }    
    if (!SD.open(Path)){
        alert("Directory not found... Creating the directory.");
        if (SD.mkdir(Path)) {
            log("Directory created successfully!");
        } else {
            panic("Failed to create the directory.");
            return;
        }
    } else{
        log("Directory found.");
        if (!SD.open(FileName)){
            panic("Payload not found! Create a file called payload.txt @ /Littlegotchi");
            return;
        }
    }
}

void convert(){
    File payload = SD.open(FileName);

    while (payload.available()) {
        String line = payload.readStringUntil('\n');

        /* Keystroke Injection */
        if (line.startsWith("REM")){
            continue;
        } else if (line.startsWith("STRING")){
            bleKeyboard.print(line.substring(7));
        } else if (line.startsWith("STRINGLN")){
            bleKeyboard.println(line.substring(9));
        }

        /* System Keys*/
        if (line.startsWith("ENTER")){
            bleKeyboard.press(KEY_NUM_ENTER);
        } else if (line.startsWith("ESCAPE")){
            bleKeyboard.press(KEY_ESC);
        } else if (line.startsWith("PRINTSCREEN")){
            bleKeyboard.press(KEY_PRTSC);
        } else if (line.startsWith("PAGEUP")){
            bleKeyboard.press(KEY_PAGE_UP);
        } else if (line.startsWith("PAGEDOWN")){
            bleKeyboard.press(KEY_PAGE_DOWN);
        } else if (line.startsWith("HOME")){
            bleKeyboard.press(KEY_HOME);
        } else if (line.startsWith("END")){
            bleKeyboard.press(KEY_END);
        } else if (line.startsWith("INSERT")){
            bleKeyboard.press(KEY_INSERT);
        } else if (line.startsWith("DELETE") || line.startsWith("DEL")){
            bleKeyboard.press(KEY_DELETE);
        } else if (line.startsWith("BACKSPACE")){
            bleKeyboard.press(KEY_BACKSPACE);
        } else if (line.startsWith("TAB")){
            bleKeyboard.press(KEY_TAB);
        }

        /* Cursor Keys */
        if (line.startsWith("UP") || line.startsWith("UPARROW")){
            bleKeyboard.press(KEY_UP_ARROW);
        } else if (line.startsWith("DOWN") || line.startsWith("DOWNARROW")){
            bleKeyboard.press(KEY_DOWN_ARROW);
        } else if (line.startsWith("LEFT") || line.startsWith("LEFTARROW")){
            bleKeyboard.press(KEY_LEFT_ARROW);
        } else if (line.startsWith("RIGHT") || line.startsWith("RIGHTARROW")){
            bleKeyboard.press(KEY_RIGHT_ARROW);
        }

        /* All the F's*/
        if (line.startsWith("F1")){
            bleKeyboard.press(KEY_F1);
        } else if (line.startsWith("F2")){
            bleKeyboard.press(KEY_F2);
        } else if (line.startsWith("F3")){
            bleKeyboard.press(KEY_F3);
        } else if (line.startsWith("F4")){
            bleKeyboard.press(KEY_F4);
        } else if (line.startsWith("F5")){
            bleKeyboard.press(KEY_F5);
        } else if (line.startsWith("F6")){
            bleKeyboard.press(KEY_F6);
        } else if (line.startsWith("F7")){
            bleKeyboard.press(KEY_F7);
        } else if (line.startsWith("F8")){
            bleKeyboard.press(KEY_F8);
        } else if (line.startsWith("F9")){
            bleKeyboard.press(KEY_F9);
        } else if (line.startsWith("F10")){
            bleKeyboard.press(KEY_F10);
        } else if (line.startsWith("F11")){
            bleKeyboard.press(KEY_F11);
        } else if (line.startsWith("F12")){
            bleKeyboard.press(KEY_F12);
        }

        /* Modifier Keys */
        if (line.startsWith("SHIFT")){
            bleKeyboard.press(KEY_LEFT_SHIFT);
        } else if (line.startsWith("ALT")){
            bleKeyboard.press(KEY_LEFT_ALT);
        } else if (line.startsWith("CONTROL") || line.startsWith("CTRL")){
            bleKeyboard.press(KEY_LEFT_CTRL);
        } else if (line.startsWith("COMMAND") || line.startsWith("WINDOWS") || line.startsWith("GUI")){
            bleKeyboard.press(KEY_LEFT_GUI);
        }

        /* Lock Keys */
        if (line.startsWith("CAPSLOCK")){
            bleKeyboard.write(KEY_CAPS_LOCK);
        }

        /* Non supported */
        if (line.startsWith("MENU APP")){
            alert("The key: MENU APP is not suported!");
        } else if (line.startsWith("PAUSE BREAK")){
            alert("The key: PAUSE BREAK is not suported!");
        } else if (line.startsWith("SPACE")){
            alert("The key: SPACE is not suported!");
        } else if (line.startsWith("NUMLOCK")){
            alert("The key: NUMLOCK is not suported!");
        } else if (line.startsWith("SCROLLOCK")){
            alert("The key: SCROLLOCK is not suported!");
        }

        /* Delay */
        if (line.startsWith("DELAY")){
            delay(line.substring(6).toInt());
        }

        // All of the Littlegotchi things
        if (line.startsWith("DISCONNECT")){
            bleKeyboard.end();
        } else if (line.startsWith("RELEASE")){
            bleKeyboard.releaseAll();
        } else if (line.startsWith("NEXTTRACK")){
            bleKeyboard.write(KEY_MEDIA_NEXT_TRACK);
        } else if (line.startsWith("PREVTRACK")){
            bleKeyboard.write(KEY_MEDIA_PREVIOUS_TRACK);
        } else if (line.startsWith("STOPTRACK")){
            bleKeyboard.write(KEY_MEDIA_STOP);
        } else if (line.startsWith("PAUSETRACK")){
            bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
        } else if (line.startsWith("MUTE")){
            bleKeyboard.write(KEY_MEDIA_MUTE);
        } else if (line.startsWith("VOLUMEUP")){
            bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
        } else if (line.startsWith("CALC")){
            bleKeyboard.write(KEY_MEDIA_CALCULATOR);
        }
    }

}