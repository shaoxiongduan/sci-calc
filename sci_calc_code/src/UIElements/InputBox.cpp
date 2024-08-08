#include "InputBox.h"

InputBox::InputBox() : UIElement() {
    this -> strPos = 0;
    this -> cursorPos = 0;
    this -> maxChar = 0;
    this -> width = this -> targetWidth = 0;
    this -> height = this -> targetHeight = 0;
    this -> cursor.setX(this -> x + 1);
    this -> cursor.setY(this -> y);
    this -> cursor.setTargetX(this -> x + 1);
    this -> cursor.setTargetY(this -> y);
    this -> cursor.setWidth(5);
    this -> cursor.setHeight(12);
    this -> cursor.setMode(1);
}

InputBox::InputBox(int x, int y, int width, int height, int maxChar) : UIElement(x, y, width, height) {
    this -> strPos = 0;
    this -> cursorPos = 0;
    this -> maxChar = maxChar;
    this -> width = this -> targetWidth = width;
    this -> height = this -> targetHeight = height;
    this -> cursor.setX(this -> x + 1);
    this -> cursor.setY(this -> y);
    this -> cursor.setTargetX(this -> x + 1);
    this -> cursor.setTargetY(this -> y);
    this -> cursor.setWidth(5);
    this -> cursor.setHeight(12);
    this -> cursor.setMode(1);
}

void InputBox::init() {
    this -> cursor.setMode(1);
    this -> cursor.changeTarget(this -> targetX + 1, this -> cursor.getY(), this -> cursor.getWidth(), this -> cursor.getHeight(), 500);
}

int InputBox::getStrPos() {
    return this -> cursorPos + this -> strPos;
}

void InputBox::activate() {
    currentElement = this;
    Serial.printf("hello!!!\n");
    //insertAnimation(new Animation(this, SMOOTH, 0, 0, 500));
    Serial.printf("hello again\n");
}

void InputBox::deactivate() {
    //insertAnimation(new Animation(this, SMOOTH, 0, -100, 500));
}



int InputBox::moveCursorLeft(int x) {
    int tmp = min(x, this -> cursorPos);
    this -> cursorPos -= tmp;
    return tmp;
}

int InputBox::moveCursorRight(int x) {
    int tmp = min(x, min(this -> maxChar - this -> cursorPos, int(this -> str.size()) - this -> cursorPos - this -> strPos));
    this -> cursorPos += tmp;
    return tmp;
}

void InputBox::moveStrLeft(int x) {
    if (this -> strPos - x >= 0) {
        this -> strPos -= x;
    }
}

void InputBox::moveStrRight(int x) {
    if (this -> strPos <= int(this -> str.size()) - this -> maxChar - x) {
        this -> strPos += x;
    }
}

void InputBox::scrollLeft(int x) {
    int tmp = moveCursorLeft(x);
    if (tmp == 0) {
        moveStrLeft(x);
    }
    else {
        this -> cursor.changeTarget(this -> cursor.getTargetX() - 5 * tmp, this -> cursor.getTargetY(), this -> cursor.getWidth(), this -> cursor.getHeight(), 100);
        moveStrLeft(x - tmp);
    }
}

void InputBox::scrollRight(int x) {
    int tmp = moveCursorRight(x);
    if (tmp == 0) {
        moveStrRight(x);
    }
    else {
        this -> cursor.changeTarget(this -> cursor.getTargetX() + 5 * tmp, this -> cursor.getTargetY(), this -> cursor.getWidth(), this -> cursor.getHeight(), 100);
        moveStrRight(x - tmp);
    }
}

void InputBox::insertStr(std::string insertStr) {
    this -> str.insert(this -> getStrPos(), insertStr);
    Serial.printf("sttr size: %d\n", this -> str.size());
    scrollRight(insertStr.size());
}

void InputBox::deleteStr() {
    if (this -> cursorPos + this -> strPos == 0) return;
    this -> str.erase(this -> getStrPos() - 1, 1);
    Serial.printf("sttr size: %d\n", this -> str.size());
    scrollLeft(1);
}

std::string InputBox::getStr() {
    return this -> str;
}

void InputBox::setStr(std::string str) {
    this -> str = str;
}

void InputBox::clearStr() {
    this -> str = "";
    this -> strPos = 0;
    this -> cursorPos = 0;
    this -> cursor.setX(this -> x + 1);
    this -> cursor.setY(this -> y);
    this -> cursor.setTargetX(this -> targetX + 1);
    this -> cursor.setTargetY(this -> targetY);
    this -> cursor.setWidth(5);
    this -> cursor.setHeight(12);
    this -> cursor.changeTarget(this -> cursor.getTargetX(), this -> cursor.getTargetY(), this -> cursor.getWidth(), this -> cursor.getHeight(), 100);
}


std::string InputBox::enter() {
    Serial.println(this -> str.c_str());
    return this -> str;
}

void InputBox::draw() {
    u8g2.drawStr(this -> x + 1, this -> y, (this -> str.substr(this -> strPos, min(this -> maxChar, int(this -> str.size()) - this -> strPos))).c_str());
    u8g2.drawRFrame(this -> x, this -> y - 6, this -> width, this -> height, 1);
    this -> cursor.setY(this -> y);
}



void InputBox::update() {
    //Serial.printf("this cursor: %d, %d\n", this -> cursor.getTargetX(), this -> cursor.getTargetY());
    //Serial.printf("cursorPos: %d, strPos: %d/n", this -> cursorPos, this -> strPos);
    //Serial.printf("key: [%d][%d]\n", kb.getRisingEdgeKey().first, kb.getRisingEdgeKey().second);
    draw();
    this -> cursor.draw();
    std::string str = calcLayout.updateString();
    if (currentElement == this) {
    this -> parentElement -> draw();
    }
    if (str == "LEFT") {
        //Serial.printf("UP\n");
        scrollLeft(1);
    }
    else if (str == "RIGHT") {
        //Serial.printf("down\n");
        scrollRight(1);
    }
    else if (str == "ENTER") {
        //enter();
    }
    else if (str == "ESC") {
        goBack();
    }
    else if (str == "BKSP") {
        Serial.println("deleting str");
        deleteStr();
    }
    else if ((kb.getRisingEdgeKey() != std::make_pair(-1, -1)) && ((str != "RIGHT" && str != "LEFT" && str != "UP" && str != "DOWN" && str != "LAYER SWITCH" && str != "MODE SWITCH" && str != "RPN SWITCH"))) {
        Serial.println("funciwdi");
        insertStr(calcLayout.updateString());
    }
    if (kb.getRisingEdgeKey() != std::make_pair(-1, -1)) {

        Serial.printf("curpos: %d\n", getStrPos());
    }

}