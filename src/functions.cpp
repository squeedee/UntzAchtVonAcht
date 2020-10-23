//
// Created by Rasheed Abdul-Aziz on 10/23/20.
//
#include "functions.h"
#include <Arduino.h>
#include <Adafruit_NeoTrellis.h>
#include "buttons.h"

namespace functions {
    uint32_t fnKeyColor;

    TrellisCallback handleFunctionButton(keyEvent event);

    typedef struct functionNode {
        button_t *button;
        struct functionNode *next;
    } functionNode_t;

    functionNode_t *headFunctionNode = nullptr;

    functionNode_t *lastFunctionNode = headFunctionNode;

    void init(uint16_t keyID, uint32_t color) {
        fnKeyColor = color;
        buttons::trellis.activateKey(keyID, SEESAW_KEYPAD_EDGE_RISING, true);
        buttons::trellis.activateKey(keyID, SEESAW_KEYPAD_EDGE_FALLING, true);
        buttons::trellis.registerCallback(keyID, handleFunctionButton);
    }


    void enableCombos();

    void disableCombos();

    TrellisCallback handleFunctionButton(keyEvent event) {
        if (event.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING) {
            buttons::trellis.setPixelColor(event.bit.NUM, fnKeyColor);
            enableCombos();
        } else {
            buttons::trellis.setPixelColor(event.bit.NUM, PIXEL_OFF);
            disableCombos();
        }
        buttons::trellis.show();
    }

    void enableCombos() {
        functionNode_t *currentNode = headFunctionNode;
        while (currentNode != nullptr) {
            buttons::trellis.setPixelColor(currentNode->button->keyID, currentNode->button->color);
            currentNode = currentNode->next;
        }
    }

    void disableCombos() {
        functionNode_t *currentNode = headFunctionNode;
        while (currentNode != nullptr) {
            buttons::trellis.setPixelColor(currentNode->button->keyID, PIXEL_OFF);
            currentNode = currentNode->next;
        }
    }


    TrellisCallback handleFunctionCombo(keyEvent event) {
        button_t *targetButton;
        functionNode_t *currentNode = headFunctionNode;
        while (currentNode != nullptr) {
            if (currentNode->button->keyID == event.bit.NUM) {
                targetButton = currentNode->button;
                break;
            }
            currentNode = currentNode->next;
        }

        if (targetButton != nullptr) {
            Serial.println("Found handler");
            if (event.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING) {
//                buttons::trellis.setPixelColor(event.bit.NUM, targetFn->color);
            } else {
//                buttons::trellis.setPixelColor(event.bit.NUM, PIXEL_OFF);
            }
//            buttons::trellis.show();
        }
    }


    void add(button_t *button) {
        functionNode_t *newNode;
        newNode = (functionNode_t *) malloc(sizeof(functionNode_t));
        newNode->button = button;
        if (lastFunctionNode == nullptr) {
            headFunctionNode = newNode;
        } else {
            lastFunctionNode->next = newNode;
        }

        lastFunctionNode = newNode;

        buttons::trellis.activateKey(button->keyID, SEESAW_KEYPAD_EDGE_RISING, true);
        buttons::trellis.activateKey(button->keyID, SEESAW_KEYPAD_EDGE_FALLING, true);
        buttons::trellis.registerCallback(button->keyID, handleFunctionCombo);
    }

    void add(uint32_t color, uint16_t keyID, void (*onPress)(int), void (*onRelease)(int)) {
        auto *button = new button_t{};

        button->keyID = keyID;
        button->color = color;
//        button->onRelease = onRelease;
//        button->onPress = onPress;

        add(button);
    }
}