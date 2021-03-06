#include <Arduino.h>
#include "buttons.h"
#include "functions.h"

void setup() {
    Serial.begin(9600);
//    while(!Serial);

    if (!buttons::trellis.begin()) {
        Serial.println("Failed to start trellis");
        while (true);
    }

    buttons::flashAll(4, 0, 35, 0);

    functions::init(0,0xffffff);

    functions::addCombo(0x600000, 0x60222222, 7, nullptr, nullptr);
    functions::addCombo(0x006000, 0x226022, 6, nullptr, nullptr);
    functions::addCombo(0x000060, 0x222260, 5, nullptr, nullptr);
}

void loop() {
    buttons::trellis.read();
    delay(20);
}

//
//for (int y = 0; y < ROWS; y++) {
//for (int x = 0; x < COLS; x++) {
//multiTrellis.activateKey(x, y, SEESAW_KEYPAD_EDGE_RISING, true);
//multiTrellis.activateKey(x, y, SEESAW_KEYPAD_EDGE_FALLING, true);
//multiTrellis.registerCallback(x, y, onKey);
//multiTrellis.setPixelColor(id(x, y), PIXEL_OFF);
//}
//}
//multiTrellis.show();