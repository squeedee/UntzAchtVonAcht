//
// Created by Rasheed Abdul-Aziz on 10/23/20.
//
#include <Arduino.h>

#ifndef UNTZACHTVONACHT_FUNCTIONS_H
#define UNTZACHTVONACHT_FUNCTIONS_H

namespace functions {
    typedef struct button {
        uint32_t color;
        uint32_t highlight;
        uint16_t keyID;
//        void (*onPress)(int keyID);
//        void (*onRelease)(int keyID);
    } button_t;

    void addCombo(button_t *button);

    void addCombo(uint32_t color, uint32_t highlight, uint16_t keyID, void (*onPress)(int), void (*onRelease)(int));

    void init(uint16_t fnKeyID, uint32_t fnColor);
}


#endif //UNTZACHTVONACHT_FUNCTIONS_H
