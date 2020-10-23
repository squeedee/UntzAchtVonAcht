//
// Created by Rasheed Abdul-Aziz on 10/22/20.
//

#ifndef UNTZACHTVONACHT_BUTTONS_H
#define UNTZACHTVONACHT_BUTTONS_H

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

#define FN_BUTTON 0

namespace buttons {
    bool init();
    void read();

    struct function {
        uint32_t color;
        uint8_t keyID;
        void (*onPress)(int keyID);
        void (*onRelease)(int keyID);
    };

    typedef struct functionNode {
        function fn;
        struct functionNode *next;
    } functionNode_t;

    void addFunction(function fn);

    function addFunction(uint32_t color, uint8_t keyID,
                         void (*onPress)(int),
                         void (*onRelease)(int));


}

#endif //UNTZACHTVONACHT_BUTTONS_H
