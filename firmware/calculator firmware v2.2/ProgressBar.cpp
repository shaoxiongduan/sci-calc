#include "ProgressBar.h"

ProgressBar::ProgressBar() : UIElement() {
    this -> totalLen = 0;
    this -> curLen = 0;
}

ProgressBar::ProgressBar(int x, int y, int totalLen, int curLen) : UIElement(x, y) {
    this -> totalLen = totalLen;
    this -> curLen = curLen;
}

void ProgressBar::setLen(int curLen) {
    Serial.println("testtt");
    insertAnimation(new Animation(&(this -> curLen), SMOOTH, curLen, 100));
}

int ProgressBar::getTotalLen() {
    return this -> totalLen;
}

void ProgressBar::draw() {
    //Serial.println(this -> curLen);
    u8g2.drawFrame(this -> x, this -> y, this -> totalLen, 8);
    u8g2.drawBox(this -> x, this -> y, this -> curLen, 8);
}