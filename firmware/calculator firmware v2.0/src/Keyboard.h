#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "Util.h"



class Key {
    public:

        Key();

        Key(int id);

        void modifyKey(float pressTime, float startPress, float endPress, bool isPressed, KeyStatus status);

        void updateKey(bool curState, float curtime);

        bool getIsPressed();

        float getPressTime();

        KeyStatus getStatus();

        Key getKey();



    private:
        int id;
        float pressTime, startPress, endPress;
        bool isPressed;
        KeyStatus status;
};

class Keyboard {
    public:
        Keyboard();

        void init();

        void update();

        Key getKey(int row, int col);

        void printKeys();

    private:
        Key keys[ROWCNT][COLCNT]; // [row][column]
};

#endif