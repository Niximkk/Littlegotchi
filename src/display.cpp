#include "display.h"
#include "serial.h"
#include "moods.h"

void initDisplay(){
    M5.Lcd.setRotation(1);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setTextColor(WHITE, BLACK);
    M5.Lcd.setTextFont(0);
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(10, 60);
    M5.Lcd.setTextSize(5);
    M5.Lcd.print(moodFace[2]);
    log("Display initialized");
}
