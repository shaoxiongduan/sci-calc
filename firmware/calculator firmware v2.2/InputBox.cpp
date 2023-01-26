#include "InputBox.h"



InputBox::InputBox(int x, int y, int width, int height, int maxChar) : UIElement(x, y, width, height) {
    this -> strPos = 0;
    this -> cursorPos = 0;
    this -> maxChar = maxChar;
    this -> width = this -> targetWidth = width;
    this -> height = this -> targetHeight = height;
    this -> cursor.setX(this -> x);
    this -> cursor.setY(this -> y + 12);
    this -> cursor.setWidth(5);
    this -> cursor.setHeight(12);
}

void InputBox::init() {
    
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



bool InputBox::moveCursorLeft() {
    if (this -> cursorPos > 0) {
        this -> cursorPos--;
        return true;
    }
    return false;
}

bool InputBox::moveCursorRight() {
    if (this -> cursorPos < this -> maxChar && this -> cursorPos < int(this -> str.size())) {
        this -> cursorPos++;
        return true;
    }
    return false;
}

bool InputBox::moveStrLeft() {
    if (this -> strPos > 0) {
        this -> strPos--;
        return true;
    }

    return false;
}

bool InputBox::moveStrRight() {
    if (this -> strPos < int(this -> str.size()) - this -> maxChar) {
        this -> strPos++;
    }
    return false;
}

void InputBox::scrollLeft() {
    if (!moveCursorLeft()) {
        moveStrLeft();
    }
    else {
        this -> cursor.changeTarget(this -> cursor.getX() - 5, this -> cursor.getY(), this -> cursor.getWidth(), this -> cursor.getHeight(), 100);
    }
}

void InputBox::scrollRight() {
    if (!moveCursorRight()) {
        moveStrRight();
    }
    else {
        this -> cursor.changeTarget(this -> cursor.getX() + 5, this -> cursor.getY(), this -> cursor.getWidth(), this -> cursor.getHeight(), 100);
    }
}

void InputBox::insertStr(std::string insertStr) {
    this -> str.insert(this -> getStrPos(), insertStr);
    Serial.printf("sttr size: %d\n", this -> str.size());
    scrollRight();
}

void InputBox::deleteStr() {
    this -> str.erase(this -> getStrPos(), 1);
    Serial.printf("sttr size: %d\n", this -> str.size());
    scrollLeft();
}



std::string InputBox::enter() {
    Serial.println(this -> str.c_str());
    return this -> str;
}

void InputBox::draw() {
    u8g2.drawRFrame(this -> x, this -> y - 6, this -> width, this -> height, 1);
    u8g2.drawStr(this -> x, this -> y, (this -> str.substr(this -> strPos, min(this -> maxChar, int(this -> str.size()) - this -> strPos))).c_str());
}



void InputBox::update() {
    this -> cursor.draw();
    //Serial.printf("cursorPos: %d, strPos: %d/n", this -> cursorPos, this -> strPos);
    //Serial.printf("key: [%d][%d]\n", kb.getRisingEdgeKey().first, kb.getRisingEdgeKey().second);
    //draw();
    this -> parentElement -> draw();
    if (kb.getRisingEdgeKey() == std::make_pair(2, 0)) {
        //Serial.printf("UP\n");
        scrollLeft();
    }
    else if (kb.getRisingEdgeKey() == std::make_pair(2, 2)) {
        //Serial.printf("down\n");
        scrollRight();
    }
    else if (kb.getRisingEdgeKey() == std::make_pair(3, 3)) {
        enter();
    }
    else if (kb.getRisingEdgeKey() == std::make_pair(0, 0)) {
        goBack();
    }
    else if (kb.getRisingEdgeKey() == std::make_pair(4, 3)) {
        Serial.println("deleting str");
        deleteStr();
    }
    else if (kb.getRisingEdgeKey() != std::make_pair(-1, -1)) {

        insertStr(calcLayout.updateString());
    }
    if (kb.getRisingEdgeKey() != std::make_pair(-1, -1)) {

        Serial.printf("curpos: %d\n", getStrPos());
    }

}