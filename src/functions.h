//
// Created by Rasheed Abdul-Aziz on 10/23/20.
//
#include <Arduino.h>

#ifndef UNTZACHTVONACHT_FUNCTIONS_H
#define UNTZACHTVONACHT_FUNCTIONS_H

namespace functions {
    typedef struct button {
        uint32_t color;
        uint16_t keyID;
//        void (*onPress)(int keyID);
//        void (*onRelease)(int keyID);
    } button_t;

    void add(button_t *button);

    void add(uint32_t color, uint16_t keyID, void (*onPress)(int), void (*onRelease)(int));

    void init(uint16_t keyID, uint32_t color);
}


#endif //UNTZACHTVONACHT_FUNCTIONS_H
