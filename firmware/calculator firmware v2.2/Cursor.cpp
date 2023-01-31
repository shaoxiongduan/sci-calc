#include "Cursor.h"

Cursor::Cursor() : UIElement(0, 0, 10, 12) {
    this -> target = nullptr;
    this -> mode = 0;
}

Cursor::Cursor(bool mode) : UIElement(0, 0, 10, 12) {
    this -> target = nullptr;
    this -> mode = mode;
}

Cursor::Cursor(UIElement* target, bool mode) : UIElement(0, 0, 10, 12) {
    this -> target = target;
    this -> mode = mode;
}

void Cursor::setMode(bool mode) {
    this -> mode = mode;
}

void Cursor::changeTarget(UIElement* target) {
    this -> target = target;
    insertAnimation(new Animation(this, SMOOTH, this -> target -> getTargetX(), this -> target -> getTargetY(), this -> target -> getTargetWidth(), this -> target -> getTargetHeight(), 100));
}

void Cursor::changeTarget(UIElement* target, int time) {
    this -> target = target;
    insertAnimation(new Animation(this, SMOOTH, this -> target -> getTargetX(), this -> target -> getTargetY(), this -> target -> getTargetWidth(), this -> target -> getTargetHeight(), time));
}

void Cursor::changeTarget(int x, int y, int width, int height, int time) {
    insertAnimation(new Animation(this, SMOOTH, x, y, width, height, time));
}

void Cursor::draw() {
    if (mode) {
        u8g2.drawLine(this -> x - 1, this -> y - 1 - 6, this -> x - 1, this -> y - 1 - 6 + this -> height + 2);
    }
    else {
        u8g2.drawRFrame(this -> x - 1, this -> y - 1 - 6, this -> width + 2, this -> height + 2, 2);
    }
}

