#include <Arduino.h>
#include "buttons.h"


void setup() {
    Serial.begin(9600);
//    while(!Serial);

    if (!buttons::init()) {
        Serial.println("Failed to start trellis");
        while (true);
    }

    buttons::addFunction(0x00600000, 7, nullptr, nullptr);
    buttons::addFunction(0x00006000, 6, nullptr, nullptr);
    buttons::addFunction(0x00000060, 5, nullptr, nullptr);
}

void loop() {
    buttons::read();
    delay(20);
}