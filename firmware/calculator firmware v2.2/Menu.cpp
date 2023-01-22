#include "Menu.h"

Menu::Menu(int x, int y, int width, int height, int menuSize, std::vector <UIElement*> subElements) : UIElement(x, y, width, height, subElements) {
    this -> menuSize = menuSize;
    this -> menuPos = 0;
    this -> cursorPos = 0;
}

void Menu::initMenu() {
    for (int i = this -> menuPos, cnt = 0; cnt < int(this -> subElements.size()); i++, cnt++) {
        insertAnimation(new Animation(subElements[i], SMOOTH, subElements[i] -> getX(), cnt * 12 + 12, 100));
    }
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
        for (int i = this -> menuPos, cnt = 0; cnt < min(this -> menuSize + 1, int(this -> subElements.size())); i++, cnt++) {
            insertAnimation(new Animation(subElements[i], SMOOTH, subElements[i] -> getX(), cnt * 12 + 12, 100));
        }
        return true;
    }

    return false;
}

bool Menu::moveMenuDown() {
    if (this -> menuPos < int(this -> subElements.size()) - this -> menuSize) {
        for (int i = this -> menuPos, cnt = 0; cnt < min(this -> menuSize + 1, int(this -> subElements.size())); i++, cnt++) {
            insertAnimation(new Animation(subElements[i], SMOOTH, subElements[i] -> getX(), subElements[i] -> getY(), subElements[i] -> getX(), (cnt - 1) * 12 + 12, 100));
        }
        this -> menuPos++;
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
    u8g2.drawBox(this -> x + this -> width - 6, this -> y + 5 + (float(getMenuPos()) / float(this -> getSize()) * (this -> height - 10)), 3, ((this -> height - 10) / this -> getSize()));
}

void Menu::draw() {
    u8g2.drawRFrame(this -> x, this -> y, this -> width, this -> height, 3);
    drawScrollBar();
    for (int i = this -> menuPos, cnt = 0; cnt < min(this -> menuSize, int(this -> subElements.size())); i++, cnt++) {
        //Serial.print("Hello");
        //subElements[i] -> setY(cnt * (this -> height / this -> menuSize) + (this -> height / this -> menuSize) / 2);
        //subElements[i] -> setY(cnt * 12 + 12);
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
    //Serial.printf("cursorPos: %d, menuPos: %d/n", this -> cursorPos, this -> menuPos);
    //Serial.printf("key: [%d][%d]\n", kb.getRisingEdgeKey().first, kb.getRisingEdgeKey().second);
    if (kb.getRisingEdgeKey() == std::make_pair(1, 1)) {
        //Serial.printf("UP\n");
        scrollUp(); 
    }
    if (kb.getRisingEdgeKey() == std::make_pair(3, 1)) {
        //Serial.printf("down\n");
        scrollDown();
    }
    draw();
}