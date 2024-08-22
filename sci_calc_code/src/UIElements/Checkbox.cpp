#include "Checkbox.h"

Checkbox::Checkbox(std::string name) {
    this -> name = name;
    this -> state = false;
    this -> linkBool = nullptr;
    this -> checkboxAni = 0;
    this -> doTransition = false;
}

Checkbox::Checkbox(std::string name, bool* linkBool) {
    this -> name = name;
    this -> state = *linkBool;
    this -> linkBool = linkBool;
    this -> checkboxAni = 0;
    this -> doTransition = false;
}

Checkbox::Checkbox(std::string name, int x, int y, bool* linkBool) {
    this -> name = name;
    this -> x = x;
    this -> y = y;
    this -> state = *linkBool;
    this -> linkBool = linkBool;
    this -> checkboxAni = 0;
    this -> doTransition = false;
}

void Checkbox::init() {
    this -> width = this -> targetWidth = u8g2.getStrWidth(this -> name.c_str());
    this -> height = this -> targetHeight = 10;
    this -> checkboxAni = (this -> state ? 6 : 0);
}

void Checkbox::activate() {
    changeState();
}

void Checkbox::changeState() {
    this -> state = !(this -> state);
    insertAnimation(new Animation(&(this -> checkboxAni), LINEAR, (this -> state ? 6 : 0), 100));
    if (this -> linkBool == nullptr) return;
    *(this -> linkBool) = (this -> state);
}

void Checkbox::draw() {
    u8g2.drawStr(this -> x, this -> y, (this -> name.substr(0, min(int(this -> name.size()), this -> width / 5))).c_str());
    u8g2.drawFrame(this -> x + this -> width + 5, this -> y - 6, 10, 10);
    u8g2.drawBox(this -> x + this -> width + 5 + (9 - this -> checkboxAni) / 2 + 1, this -> y + (9 - this -> checkboxAni) / 2 - 6 + 1, this -> checkboxAni, this -> checkboxAni);
}

void Checkbox::update() {
    draw();
}