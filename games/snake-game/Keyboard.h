#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <Arduino.h>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <sstream>
#include <list>

#include <Update.h>
#include <FS.h>
#include <SD.h>

const int REFRESH_DURATION = 10; // in milliseconds
const int DELTA_TIME = 100;
const int ROWCNT = 5;
const int COLCNT = 6;

enum KeyStatus {
    NOT_PRESSED, PRESSED, RISING_EDGE, FALLING_EDGE
};

extern byte ROW_MISO[ROWCNT];
extern byte COL_MOSI[COLCNT];
extern bool sample;



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