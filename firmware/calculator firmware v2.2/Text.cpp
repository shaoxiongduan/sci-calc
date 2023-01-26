#include "Text.h"


Text::Text(std::string text) : UIElement() {
    this -> text = text;
}


Text::Text(int x, int y, std::string text) : UIElement(x, y) {
    this -> text = text;
}


Text::Text(int x, int y, int width, int height, std::string text) : UIElement(x, y, width, height) {
    this -> text = text;
    this -> width = this -> targetWidth = width;
    this -> height = this -> targetHeight = height;
}

void Text::init() {
    this -> width = this -> targetWidth = u8g2.getStrWidth(this -> text.c_str());
    this -> height = this -> targetHeight = 10;
}

void Text::draw() {
    u8g2.drawStr(this -> x, this -> y, this -> text.c_str());
}
