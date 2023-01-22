#include "Text.h"


Text::Text(std::string text) : UIElement() {
    this -> text = text;
}

Text::Text(int x, int y, std::string text) : UIElement(x, y) {
    this -> text = text;
}


Text::Text(int x, int y, int width, int height, std::string text) : UIElement(x, y, width, height) {
    this -> text = text;
}

void Text::draw() {
    u8g2.drawStr(this -> x, this -> y, this -> text.c_str());
}

void Text::drawHighlight() {
    u8g2.setDrawColor(0);
    this -> draw();
    u8g2.setDrawColor(1);
}

