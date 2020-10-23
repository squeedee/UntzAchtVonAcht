//
// Created by Rasheed Abdul-Aziz on 10/23/20.
//
#include "functions.h"
#include <Arduino.h>
#include <Adafruit_NeoTrellis.h>
#include "buttons.h"

namespace functions {
    uint32_t fnKeyColor;
    bool isFn = false;

    TrellisCallback handleFunctionButton(keyEvent event);

    typedef struct functionNode {
        button_t *button;
        struct functionNode *next;
    } functionNode_t;

    functionNode_t *headFunctionNode = nullptr;

    functionNode_t *lastFunctionNode = headFunctionNode;

    void displayCombos(bool visible);


    // color is the color of the Fn button
    void init(uint16_t fnKeyID, uint32_t fnColor) {
        fnKeyColor = fnColor;
        buttons::trellis.activateKey(fnKeyID, SEESAW_KEYPAD_EDGE_RISING, true);
        buttons::trellis.activateKey(fnKeyID, SEESAW_KEYPAD_EDGE_FALLING, true);
        buttons::trellis.registerCallback(fnKeyID, handleFunctionButton);
    }

    TrellisCallback handleFunctionButton(keyEvent event) {
        if (event.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING) {
            buttons::trellis.setPixelColor(event.bit.NUM, fnKeyColor);
            displayCombos(true);
            isFn = true;
        } else {
            buttons::trellis.setPixelColor(event.bit.NUM, PIXEL_OFF);
            displayCombos(false);
            isFn = false;
        }
        buttons::trellis.show();
    }

    void displayCombos(bool visible) {
        functionNode_t *currentNode = headFunctionNode;
        while (currentNode != nullptr) {
            int32_t color = visible ? currentNode->button->color: PIXEL_OFF;
            buttons::trellis.setPixelColor(currentNode->button->keyID, color);
            currentNode = currentNode->next;
        }
    }

    TrellisCallback handleFunctionCombo(keyEvent event) {
        if (!isFn) return nullptr;
,uuuuuuuuu,6
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
            if (event.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING) {
                buttons::trellis.setPixelColor(event.bit.NUM, targetButton->highlight);
            } else {
                buttons::trellis.setPixelColor(event.bit.NUM, targetButton->color);
            }
            buttons::trellis.show();
        }
    }


    void addCombo(button_t *button) {
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

    void addCombo(uint32_t color, uint32_t highlight, uint16_t keyID, void (*onPress)(int), void (*onRelease)(int)) {
        auto *button = new button_t{};

        button->keyID = keyID;
        button->color = color;
        button->highlight = highlight;
//        button->onRelease = onRelease;
//        button->onPress = onPress;

        addCombo(button);
    }
}