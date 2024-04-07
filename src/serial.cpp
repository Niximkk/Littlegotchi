#include "serial.h"

void initSerial(){
    String logo = "\
                                                 \n\
     __    _ _   _   _             _       _   _ \n\
    |  |  |_| |_| |_| |___ ___ ___| |_ ___| |_|_|\n\
    |  |__| |  _|  _| | -_| . | . |  _|  _|   | |\n\
    |_____|_|_| |_| |_|___|_  |___|_| |___|_|_|_|\n\
                          |___|                  \n";

    Serial.begin(115200);
    Serial.print(logo);
}

void log(String message){
    Serial.println("(•‿‿•) - "+message);
}

void alert(String message){
    Serial.println("(#__#) - "+message);
}

void rem(String message){
    Serial.println("( ◕‿◕) - "+message);
}

void broken(String message){
    Serial.println("(☓‿‿☓) - I BROKE!!!! because "+message);
}

// Some ducks for decoration!
//   __(.)< __(.)> __(.)=   
//   \___)  \___)  \___)    
// Is this a Rubber Ducky reference? (♥‿‿♥)