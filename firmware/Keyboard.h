#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "Util.h"



class Key {
    public:

        Key();

        Key(int id);

        void modifyKey(float statusTime, float startPress, float endPress, bool isPressed, KeyStatus status, int clickCnt);

        void updateKey(bool curState, float curtime);

        bool getIsPressed();

        int getClickCnt();

        float getStatusTime();

        KeyStatus getStatus();

        Key getKey();



    private:
        int id;
        float statusTime, startPress, endPress;
        int clickCnt;
        bool isPressed;
        KeyStatus status;
};

class Keyboard {
    public:
        Keyboard();

        void init();

        void update();

        std::pair <int, int> getRisingEdgeKey();
        
        std::pair <int, int> getFallingEdgeKey();

        std::pair <int, int> getChangedKey();

        Key getKey(int row, int col);

        void printKeys();

    private:
        float prevtime;
        Key keys[ROWCNT][COLCNT]; // [row][column]
};

#endif