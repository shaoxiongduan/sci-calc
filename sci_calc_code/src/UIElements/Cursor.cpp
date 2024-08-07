#include "Cursor.h"

Cursor::Cursor() : UIElement(0, 0, 10, 12) {
    this -> isVisible = true;
    this -> target = nullptr;
    this -> mode = 0;
}

Cursor::Cursor(bool mode) : UIElement(0, 0, 10, 12) {
    this -> isVisible = true;
    this -> target = nullptr;
    this -> mode = mode;
}

Cursor::Cursor(UIElement* target, bool mode) : UIElement(0, 0, 10, 12) {
    this -> isVisible = true;
    this -> target = target;
    this -> mode = mode;
}

void Cursor::setMode(bool mode) {
    this -> mode = mode;
}

void Cursor::setVisible(bool isVisible) {
    this -> isVisible = isVisible;
}

void Cursor::changeTarget(UIElement* target) {
    this -> target = target;
    insertAnimation(new Animation(this, INDENT, this -> target -> getTargetX(), this -> target -> getTargetY(), this -> target -> getTargetWidth(), this -> target -> getTargetHeight(), 100));
}

void Cursor::changeTarget(UIElement* target, int time) {
    this -> target = target;
    insertAnimation(new Animation(this, INDENT, this -> target -> getTargetX(), this -> target -> getTargetY(), this -> target -> getTargetWidth(), this -> target -> getTargetHeight(), time));
}

void Cursor::changeTarget(UIElement* target, int time, int delayTime) {
    this -> target = target;
    insertAnimation(new Animation(this, INDENT, this -> target -> getTargetX(), this -> target -> getTargetY(), this -> target -> getTargetWidth(), this -> target -> getTargetHeight(), time, delayTime));
}

void Cursor::changeTarget(int x, int y, int width, int height, int time) {
    insertAnimation(new Animation(this, INDENT, x, y, width, height, time));
}


void Cursor::draw() {
    if (this -> target == nullptr || ! this -> isVisible) {
        return; //Don't draw cursor
    }
    if (mode) {
        u8g2.drawLine(this -> x - 1, this -> y - 6 + 1, this -> x - 1, this -> y - 6 + this -> height - 3);
    }
    else {
        if (cursorMode == false) {
            u8g2.drawRFrame(this -> x - 1, this -> y - 1 - 6, this -> width + 2, this -> height + 2, 2);
        }
        else {
            u8g2.setDrawColor(2);
            u8g2.drawRBox(this -> x - 1, this -> y - 1 - 6, this -> width + 2, this -> height + 2, 0);
            u8g2.setDrawColor(1);
        }
    }
}

