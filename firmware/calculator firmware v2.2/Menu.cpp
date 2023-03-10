#include "Menu.h"

Menu::Menu() : UIElement() {
    this -> menuPos = 0;
    this -> cursorPos = 0;
}

Menu::Menu(int x, int y, int width, int height, int menuSize) : UIElement(x, y, width, height) {
    this -> menuSize = menuSize;
    this -> menuPos = 0;
    this -> cursorPos = 0;
    this -> scrollBar.setX(this -> x + this -> width - 6);
    if (this -> getSize() == 0) {
        this -> scrollBar.setY(this -> y + 5);
        this -> scrollBar.setHeight(0);
        this -> cursor.setX(this -> x);
        this -> cursor.setY(this -> y + 12);
    }
    else {
        this -> scrollBar.setY(this -> y + 5 + (float(getMenuPos()) / float(this -> getSize()) * (this -> height - 10)));
        this -> scrollBar.setHeight(((this -> height - 10) / this -> getSize()));
    }
}

Menu::Menu(int x, int y, int width, int height, int menuSize, std::vector <UIElement*> subElements, std::vector <UIElement*> linkElements) : UIElement(x, y, width, height, subElements) {
    this -> menuSize = menuSize;
    this -> menuPos = 0;
    this -> cursorPos = 0;
    this -> linkElements = linkElements;
    this -> scrollBar.setX(this -> x + this -> width - 6);
    this -> scrollBar.setY(this -> y + 5 + (float(getMenuPos()) / float(this -> getSize()) * (this -> height - 10)));
    this -> scrollBar.setHeight(((this -> height - 10) / this -> getSize()));
}

void Menu::init() {
    //insertAnimation(new Animation(this, SMOOTH, 0, 0, 500));
    this -> cursor.setX(this -> x);
    this -> cursor.setY(this -> y + 12);
    for (int i = this -> menuPos, cnt = 0; cnt < int(this -> subElements.size()); i++, cnt++) {
        subElements[i] -> setX(this -> x);
        subElements[i] -> setY(cnt * 12 + 12);
        this -> subElements[i] -> init();
        //insertAnimation(new Animation(subElements[i], SMOOTH, subElements[i] -> getX(), cnt * 12 + 12, 500));
    }

    for (int i = this -> menuPos, cnt = 0; cnt < int(this -> subElements.size()); i++, cnt++) {
        //subElements[i] -> setX(this -> targetX + 5);
        insertAnimation(new Animation(subElements[i], SMOOTH, this -> targetX + 5, cnt * 12 + 12, 500));
    }

    for (int i = 0; i < this -> linkElements.size(); i++) {
        if (this -> linkElements[i] != nullptr) {
            this -> linkElements[i] -> setParent(this);
        }
    }
    this -> cursor.changeTarget(subElements[0], 500);
    //insertAnimation(new Animation(&(this -> scrollBar), SMOOTH, this -> targetX + this -> width - 6, this -> y + 5 + (float(getMenuPos()) / float(this -> getSize()) * (this -> height - 10)), 500));
}

void Menu::activate() {
    currentElement = this;
    Serial.printf("hello!!!\n");
    //insertAnimation(new Animation(this, SMOOTH, 0, 0, 500));
    Serial.printf("hello again\n");
}

void Menu::deactivate() {
    //insertAnimation(new Animation(this, SMOOTH, 0, -100, 500));
}


void Menu::insertElement(UIElement* targetElement, UIElement* linkElement) {
    
    targetElement -> setX(this -> targetX + 5);
    targetElement -> setY(70);
    insertAnimation(new Animation(targetElement, SMOOTH, targetElement -> getX(), min(this -> menuSize, int(this -> subElements.size())) * 12 + 12, 100));
        
    this -> subElements.push_back(targetElement);
    this -> linkElements.push_back(linkElement);
    targetElement -> init();
    this -> scrollBar.setY(this -> y + 5 + (float(getMenuPos()) / float(this -> getSize()) * (this -> height - 10)));
    this -> scrollBar.setHeight(((this -> height - 10) / this -> getSize()));
    if (linkElement != nullptr) {
        linkElement -> setParent(this);
    }
    this -> cursor.changeTarget(subElements[this -> cursorPos + this -> menuPos], 100);
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
    Serial.println("fgasrgf");
    if (this -> menuPos < int(this -> subElements.size()) - this -> menuSize) {
        for (int i = this -> menuPos, cnt = 0; cnt < min(this -> menuSize + 1, int(this -> subElements.size())); i++, cnt++) {
            insertAnimation(new Animation(subElements[i], SMOOTH, subElements[i] -> getX(), (cnt - 1) * 12 + 12, 100));
        }
        this -> menuPos++;
    }
    return false;
}

void Menu::scrollUp() {
    if (!moveCursorUp()) {
        moveMenuUp();
    }
    this -> cursor.changeTarget(subElements[this -> menuPos + this -> cursorPos]);
    //moveCursorUp();
    insertAnimation(new Animation(&(this -> scrollBar), SMOOTH, this -> targetX + this -> width - 6, this -> y + 5 + (float(getMenuPos()) / float(this -> getSize()) * (this -> height - 10)), 100));
}

void Menu::scrollDown() {
    if (!moveCursorDown()) {
        moveMenuDown();
    }
    this -> cursor.changeTarget(subElements[this -> menuPos + this -> cursorPos]);    
    //moveCursorDown();
    insertAnimation(new Animation(&(this -> scrollBar), SMOOTH, this -> targetX + this -> width - 6, this -> y + 5 + (float(getMenuPos()) / float(this -> getSize()) * (this -> height - 10)), 100));
}

int Menu::getMenuPos() {
    return this -> cursorPos + this -> menuPos;
}

void Menu::drawScrollBar() {
    u8g2.drawLine(this -> x + this -> width - 5, this -> y + 4, this -> x + this -> width - 5, this -> y + this -> height - 4);
    this -> scrollBar.setX(this -> x + this -> width - 6);
    this -> scrollBar.draw();
    //u8g2.drawBox(this -> x + this -> width - 6, this -> y + 5 + (float(getMenuPos()) / float(this -> getSize()) * (this -> height - 10)), 3, ((this -> height - 10) / this -> getSize()));
    //insertAnimation(new Animation(&(this -> scrollBar), SMOOTH, this -> targetX + this -> width - 6, this -> y + 5 + (float(getMenuPos()) / float(this -> getSize()) * (this -> height - 10)), 100));
}

void Menu::clear() {
    this -> menuSize = menuSize;
    this -> menuPos = 0;
    this -> cursorPos = 0;
    this -> scrollBar.setX(this -> x + this -> width - 6);
    if (this -> getSize() == 0) {
        this -> scrollBar.setY(this -> y + 5);
        this -> scrollBar.setHeight(0);
        this -> cursor.setX(this -> x);
        this -> cursor.setY(this -> y + 12);
    }
    else {
        this -> scrollBar.setY(this -> y + 5 + (float(getMenuPos()) / float(this -> getSize()) * (this -> height - 10)));
        this -> scrollBar.setHeight(((this -> height - 10) / this -> getSize()));
    }
    this -> subElements.clear();
    this -> linkElements.clear();
}

void Menu::enter() {
    if (this -> linkElements[this -> menuPos + this -> cursorPos] != nullptr) {
        this -> linkElements[this -> menuPos + this -> cursorPos] -> init();
        this -> linkElements[this -> menuPos + this -> cursorPos] -> activate();
    }
}

void Menu::draw() {
    u8g2.setClipWindow(this -> x, this -> y, this -> width, this -> height);
    u8g2.drawRFrame(this -> x, this -> y, this -> width, this -> height, 3);
    for (int i = this -> menuPos, cnt = 0; cnt < min(this -> menuSize, int(this -> subElements.size())); i++, cnt++) {
        //Serial.print("Hello");
        //subElements[i] -> setY(cnt * (this -> height / this -> menuSize) + (this -> height / this -> menuSize) / 2);
        subElements[i] -> draw();
    }
    drawScrollBar();
    u8g2.setClipWindow(0, 0, 256, 64);
}



void Menu::update() {
    //Serial.printf("cursorPos: %d, menuPos: %d/n", this -> cursorPos, this -> menuPos);
    //Serial.printf("key: [%d][%d]\n", kb.getRisingEdgeKey().first, kb.getRisingEdgeKey().second);
    if (this -> getSize() > 0) {
        if (kb.getRisingEdgeKey() == std::make_pair(1, 1)) {
            //Serial.printf("UP\n");
            scrollUp();
        }
        if (kb.getRisingEdgeKey() == std::make_pair(3, 1)) {
            //Serial.printf("down\n");
            scrollDown();
        }
        if (kb.getRisingEdgeKey() == std::make_pair(3, 3)) {
            enter();
        }
    }
    if (kb.getRisingEdgeKey() == std::make_pair(0, 0)) {
        goBack();
    }
    draw();
    this -> cursor.draw();
}