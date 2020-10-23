//
// Created by Rasheed Abdul-Aziz on 10/22/20.
//
#include "buttons.h"


namespace buttons {

    Adafruit_NeoTrellis trellisi[ROWS / 4][COLS / 4] = {
        {Adafruit_NeoTrellis(TOP_LEFT_ADDR),    Adafruit_NeoTrellis(TOP_RIGHT_ADDR)},
        {Adafruit_NeoTrellis(BOTTOM_LEFT_ADDR), Adafruit_NeoTrellis(BOTTOM_RIGHT_ADDR)}
    };

    Adafruit_MultiTrellis trellis = Adafruit_MultiTrellis((Adafruit_NeoTrellis *) trellisi, ROWS / 4, COLS / 4);

    uint32_t wheel(byte WheelPos) {
        if (WheelPos < 85) {
            return seesaw_NeoPixel::Color(WheelPos * 3, 255 - WheelPos * 3, 0);
        } else if (WheelPos < 170) {
            WheelPos -= 85;
            return seesaw_NeoPixel::Color(255 - WheelPos * 3, 0, WheelPos * 3);
        } else {
            WheelPos -= 170;
            return seesaw_NeoPixel::Color(0, WheelPos * 3, 255 - WheelPos * 3);
        }
    }

    int id(int x, int y) {
        return x + (y * COLS);
    }

    void flashAll(int amount, int low, int high, int delayTime) {
        int color;
        int dbl = amount * 2;
        for (int i = 0; i < dbl; i++) {
            if (i <= amount) {
                color = map(i, 0, amount, low, high);
            } else {
                color = map(dbl - i - 1, 0, amount, low, high);
            }

            for (int y = 0; y < ROWS; y++) {
                for (int x = 0; x < COLS; x++) {
                    trellis.setPixelColor(x, y, seesaw_NeoPixel::Color(color, color, color));
                }
            }
            trellis.show();
            if (delayTime > 0) {
                delay(delayTime);
            }
        }
    }

//    bool fnMode = false;
//
//    TrellisCallback onKey(keyEvent evt) {
//        int id = evt.bit.NUM;
//        if (evt.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING) {
//
//            if (id == FN_BUTTON) {
//                functionNode_t *currentNode = headFunctionNode;
//                while (currentNode != nullptr) {
//                    multiTrellis.setPixelColor(currentNode->fn.keyID, currentNode->fn.color);
//                    currentNode = currentNode->next;
//                }
//                multiTrellis.show();
//                fnMode = true;
//            }
//            if (!fnMode) {
//                on(id);
//            }
//
//        } else if (evt.bit.EDGE == SEESAW_KEYPAD_EDGE_FALLING) {
//            if (id == FN_BUTTON) {
//                functionNode_t *currentNode = headFunctionNode;
//                while (currentNode != nullptr) {
//                    multiTrellis.setPixelColor(currentNode->fn.keyID, PIXEL_OFF);
//                    currentNode = currentNode->next;
//                }
//                fnMode = false;
//            }
//
//            off(id);
//        }
//        return nullptr;
//    }
}