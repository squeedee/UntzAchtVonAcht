//
// Created by Rasheed Abdul-Aziz on 10/22/20.
//
#include <Adafruit_NeoTrellis.h>
#include "buttons.h"


namespace buttons {
    Adafruit_NeoTrellis trellisi[ROWS / 4][COLS / 4] = {
        {Adafruit_NeoTrellis(TOP_LEFT_ADDR),    Adafruit_NeoTrellis(TOP_RIGHT_ADDR)},
        {Adafruit_NeoTrellis(BOTTOM_LEFT_ADDR), Adafruit_NeoTrellis(BOTTOM_RIGHT_ADDR)}
    };

    Adafruit_MultiTrellis multiTrellis((Adafruit_NeoTrellis *) trellisi, ROWS / 4, COLS / 4);

    uint32_t button_colors[ROWS * COLS];

    functionNode_t *headFunctionNode = nullptr;
    functionNode_t *lastFunctionNode = headFunctionNode;

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

    void off(int id) {
        multiTrellis.setPixelColor(id, PIXEL_OFF);
        multiTrellis.show();
    }

    void off(int x, int y) {
        off(id(x, y));
    }

    void on(int id) {
        multiTrellis.setPixelColor(id, button_colors[id]);
        multiTrellis.show();
    }

    void on(int x, int y) {
        on(id(x, y));
    }

    void flashAll(int amount, int low, int high, int delayTime) {
        int color;
        int dbl = amount * 2;
        for (int i = 0; i < dbl; i++) {
            if (i <= amount) {
                color = map(i, 0, amount, low, high);
            } else {
                color = map(dbl - i, 0, amount, low, high);
            }

            for (int y = 0; y < ROWS; y++) {
                for (int x = 0; x < COLS; x++) {
                    multiTrellis.setPixelColor(x, y, seesaw_NeoPixel::Color(color, color, color));
                }
            }
            multiTrellis.show();
            if (delayTime > 0) {
                delay(delayTime);
            }
        }
    }

    void setup_colors() {
        int buttonId = 0;
        int buttonTotal = COLS * ROWS;
        for (int y = 0; y < ROWS; y++) {
            for (int x = 0; x < COLS; x++) {
                button_colors[buttonId] = wheel(map(buttonId, 0, buttonTotal, 0, 255));
                buttonId++;
            }
        }
    }

    bool fnMode = false;

    TrellisCallback onKey(keyEvent evt) {
        int id = evt.bit.NUM;
        if (evt.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING) {

            if (id == FN_BUTTON) {
                functionNode_t *currentNode = headFunctionNode;
                while (currentNode != nullptr) {
                    multiTrellis.setPixelColor(currentNode->fn.keyID, currentNode->fn.color);
                    currentNode = currentNode->next;
                }
                multiTrellis.show();
                fnMode = true;
            }
            if (!fnMode) {
                on(id);
            }

        } else if (evt.bit.EDGE == SEESAW_KEYPAD_EDGE_FALLING) {
            if (id == FN_BUTTON) {
                functionNode_t *currentNode = headFunctionNode;
                while (currentNode != nullptr) {
                    multiTrellis.setPixelColor(currentNode->fn.keyID, PIXEL_OFF);
                    currentNode = currentNode->next;
                }
                fnMode = false;
            }

            off(id);
        }
        return nullptr;
    }


    bool init() {
        setup_colors();

        if (multiTrellis.begin()) {
            flashAll(4, 0, 35, 0);
            for (int y = 0; y < ROWS; y++) {
                for (int x = 0; x < COLS; x++) {
                    multiTrellis.activateKey(x, y, SEESAW_KEYPAD_EDGE_RISING, true);
                    multiTrellis.activateKey(x, y, SEESAW_KEYPAD_EDGE_FALLING, true);
                    multiTrellis.registerCallback(x, y, onKey);
                    multiTrellis.setPixelColor(id(x, y), PIXEL_OFF);
                }
            }
            multiTrellis.show();
            return true;
        } else {
            return false;
        }
    }


    void read() {
        multiTrellis.read();
    }


    void addFunction(function fn) {
        functionNode_t *newNode;
        newNode = (functionNode_t *) malloc(sizeof(functionNode_t));
        newNode->fn = fn;
        if (lastFunctionNode == nullptr) {
            headFunctionNode = newNode;
        } else {
            lastFunctionNode->next = newNode;
        }

        lastFunctionNode = newNode;
    }

    function addFunction(uint32_t color, uint8_t keyID, void (*onPress)(int), void (*onRelease)(int)) {
        struct function fn{
            .color = color,
            .keyID = keyID,
            .onPress = onPress,
            .onRelease = onRelease,
        };

        addFunction(fn);
        return fn;
    }

}