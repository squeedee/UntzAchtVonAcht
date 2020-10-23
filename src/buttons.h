//
// Created by Rasheed Abdul-Aziz on 10/22/20.
//

#ifndef UNTZACHTVONACHT_BUTTONS_H
#define UNTZACHTVONACHT_BUTTONS_H

#include <Adafruit_NeoTrellis.h>

// Number of buttons
#define ROWS 8
#define COLS 8

// Addressing of Neo Trellis Boards
#define TOP_LEFT_ADDR 0x2f
#define TOP_RIGHT_ADDR 0x2e
#define BOTTOM_LEFT_ADDR 0x30
#define BOTTOM_RIGHT_ADDR 0x31

// Colors

#define PIXEL_OFF 0x000000

namespace buttons {
    void flashAll(int amount, int low, int high, int delayTime);
    extern Adafruit_MultiTrellis trellis;
}

#endif //UNTZACHTVONACHT_BUTTONS_H
