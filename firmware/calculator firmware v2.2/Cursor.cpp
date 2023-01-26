#include "Cursor.h"

Cursor::Cursor() : UIElement(0, 0, 10, 12) {
    this -> target = nullptr;
}

Cursor::Cursor(UIElement* target) : UIElement(0, 0, 10, 12) {
    this -> target = target;
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
    u8g2.drawRFrame(this -> x - 1, this -> y - 1 - 6, this -> width + 2, this -> height + 2, 2);
}
