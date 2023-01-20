#include "UIElement.h"

UIElement::UIElement() {
    this -> x = 0;
    this -> y = 0;
    this -> width = 0;
    this -> height = 0;
}

UIElement::UIElement(int x, int y) {
    this -> x = x;
    this -> y = y;
    this -> width = 0;
    this -> height = 0;
}

UIElement::UIElement(int x, int y, int width, int height) {
    this -> x = x;
    this -> y = y;
    this -> width = width;
    this -> height = height;
}

UIElement::UIElement(int x, int y, int width, int height, std::vector <UIElement*> subElements) {
    this -> x = x;
    this -> y = y;
    this -> width = width;
    this -> height = height;
    this -> subElements = subElements;
}

void UIElement::insert(UIElement* UIElement) {
    this -> subElements.push_back(UIElement);
}

UIElement* UIElement::getNode(int id) {
    return this -> subElements[id];
}

int UIElement::getSize() {
    return this -> subElements.size();
}

int UIElement::getX() {
    return this -> x;            
}

int UIElement::getY() {
    return this -> y;
}

void UIElement::setX(int x) {
    this -> x = x;
}

void UIElement::setY(int y) {
    this -> y = y;
}

void UIElement::draw() {

}

void UIElement::drawHighlight() {

}

bool UIElement::drawCondition() {

}

bool UIElement::moveCondition() {

}

void UIElement::drawRecursive() {
    this -> draw();
    for (UIElement* subElement : this -> subElements) {
        if (subElement -> drawCondition()) {
            subElement -> drawRecursive();
        }
    }
}

/********************
TEXT
********************/

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

/********************
MENU
********************/
Menu::Menu(int x, int y, int width, int height, int menuSize, std::vector <UIElement*> subElements) : UIElement(x, y, width, height, subElements) {
    this -> menuSize = menuSize;
    this -> menuPos = 0;
    this -> cursorPos = 0;
}

bool Menu::moveCursorUp() {
    if (this -> cursorPos > 0) {
        this -> cursorPos--;
        return true;
    }
    return false;
}

bool Menu::moveCursorDown() {
    if (this -> cursorPos < menuSize - 1 && this -> cursorPos < int(this -> subElements.size()) - 1) {
        this -> cursorPos++;
        return true;
    }
    return false;
}

bool Menu::moveMenuUp() {
    if (this -> menuPos > 0) {
        this -> menuPos--;
        return true;
    }
    return false;
}

bool Menu::moveMenuDown() {
    if (this -> menuPos < int(this -> subElements.size()) - this -> menuSize) {
        this -> menuPos++;
        return true;
    }
    return false;
}

void Menu::scrollUp() {
    if (moveCursorUp()) {
        return;
    }
    moveMenuUp();
    //moveCursorUp();
}

void Menu::scrollDown() {
    if (moveCursorDown()) {
        return;
    }
    moveMenuDown();
    //moveCursorDown();
}

int Menu::getMenuPos() {
    return this -> cursorPos + this -> menuPos;
}

void Menu::drawScrollBar() {
    u8g2.drawLine(this -> x + this -> width - 5, this -> y + 4, this -> x + this -> width - 5, this -> y + this -> height - 4);
    u8g2.drawBox(this -> width - 6, 5 + (float(getMenuPos()) / float(this -> getSize()) * (this -> height - 10)), 3, ((this -> height - 10) / this -> getSize()));
}

void Menu::draw() {
    u8g2.drawRFrame(this -> x, this -> y, this -> width, this -> height, 3);
    drawScrollBar();
    for (int i = this -> menuPos, cnt = 0; cnt < min(this -> menuSize, int(this -> subElements.size())); i++, cnt++) {
        //Serial.print("Hello");
        //subElements[i] -> setY(cnt * (this -> height / this -> menuSize) + (this -> height / this -> menuSize) / 2);
        subElements[i] -> setY(cnt * 12 + 12);
        subElements[i] -> setX(this -> x + 5);
        if (cnt == cursorPos) {
            subElements[i] -> drawHighlight();
        }
        else {
            subElements[i] -> draw();
        }
    }
}


void Menu::update() {
    Serial.printf("cursorPos: %d, menuPos: %d/n", this -> cursorPos, this -> menuPos);
    Serial.printf("key: [%d][%d]\n", kb.getRisingEdgeKey().first, kb.getRisingEdgeKey().second);
    if (kb.getRisingEdgeKey() == std::make_pair(1, 1)) {
        Serial.printf("UP\n");
        scrollUp(); 
    }
    if (kb.getRisingEdgeKey() == std::make_pair(3, 1)) {
        Serial.printf("down\n");
        scrollDown();
    }
    draw();
}