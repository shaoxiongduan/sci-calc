#include "Menu.h"

Menu::Menu() : UIElement() {
    this -> menuPos = 0;
    this -> cursorPos = 0;
}

Menu::Menu(int restX, int restY, int activeX, int activeY, int width, int height, int menuSize) : UIElement(restX, restY, width, height) {
    this -> menuSize = menuSize;
    this -> menuPos = 0;
    this -> cursorPos = 0;
    this -> restX = restX;
    this -> restY = restY;
    this -> activeX = activeX;
    this -> activeY = activeY;
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

Menu::Menu(int restX, int restY, int activeX, int activeY, int width, int height, int menuSize, std::vector <UIElement*> subElements, std::vector <UIElement*> linkElements) : UIElement(restX, restY, width, height, subElements) {
    this -> menuSize = menuSize;
    this -> menuPos = 0;
    this -> cursorPos = 0;
    this -> linkElements = linkElements;
    this -> restX = restX;
    this -> restY = restY;
    this -> activeX = activeX;
    this -> activeY = activeY;
    this -> scrollBar.setX(this -> x + this -> width - 6);
    this -> scrollBar.setY(this -> y + 5 + (float(getMenuPos()) / float(this -> getSize()) * (this -> height - 10)));
    this -> scrollBar.setHeight(((this -> height - 10) / this -> getSize()));
}

void Menu::init() {
    
    //this -> cursor.setX(this -> x);
    //this -> cursor.setY(this -> y + 12);
    for (int i = this -> menuPos, cnt = 0; cnt < int(this -> subElements.size()) && i < int(this -> subElements.size()); i++, cnt++) {
        subElements[i] -> setX(this -> x);
        subElements[i] -> setY(this -> targetY + cnt * 12 + 12);
        this -> subElements[i] -> init();
        //insertAnimation(new Animation(subElements[i], INDENT, subElements[i] -> getX(), cnt * 12 + 12, 500));
    }
    for (int cnt = 0; cnt < int(this -> subElements.size()); cnt++) {
        insertAnimation(new Animation(subElements[cnt], INDENT, this -> targetX + 5, this -> targetY + (cnt - this -> menuPos) * 12 + 12, 100));
    }
    for (int i = 0; i < this -> linkElements.size(); i++) {
        if (this -> linkElements[i] != nullptr) {
            this -> linkElements[i] -> setParent(this);
        }
    }
    //insertAnimation(new Animation(&(this -> scrollBar), SMOOTH, this -> targetX + this -> width - 6, this -> y + 5 + (float(getMenuPos()) / float(this -> getSize()) * (this -> height - 10)), 500));
}

void Menu::activate() {
    //if (getSize() == 0) return;

    currentElement = this;
    aniIn();

}

void Menu::deactivate() {

}

void Menu::aniIn() {
    insertAnimation(new Animation(this, INDENT, this -> activeX, this -> activeY, 500));
    insertAnimation(new Animation(&(this -> scrollBar), INDENT, this -> targetX + this -> width - 6, this -> targetY + 5 + (float(getMenuPos()) / float(this -> getSize()) * (this -> height - 10)), 500));
    //insertAnimation(new Animation(this -> scrollBar, this -> targetX + this -> width - 6, ));
    for (int cnt = 0; cnt < int(this -> subElements.size()); cnt++) {
        insertAnimation(new Animation(subElements[cnt], INDENT, this -> targetX + 5, this -> targetY + (cnt - this -> menuPos) * 12 + 12, 500));
    }
    if (this -> getSize() != 0) {
        this -> cursor.changeTarget(subElements[this -> cursorPos + this -> menuPos], 500);
    }
}

void Menu::aniOut() {
    insertAnimation(new Animation(this, INDENTINV, this -> restX, this -> restY, 500));
    for (int cnt = 0; cnt < int(this -> subElements.size()); cnt++) {
        insertAnimation(new Animation(subElements[cnt], INDENTINV, this -> targetX + 5, this -> targetY + (cnt - this -> menuPos) * 12 + 12, 500));
        insertTmpAnimationPointer(subElements[cnt]);
    }
    insertTmpAnimationPointer(this);
    if (this -> getSize() != 0) {
        this -> cursor.changeTarget(subElements[this -> cursorPos + this -> menuPos], 500);
    }
    insertAnimation(new Animation(&(this -> scrollBar), INDENTINV, this -> targetX + this -> width - 6, this -> targetY + 5 + (float(getMenuPos()) / float(this -> getSize()) * (this -> height - 10)), 500));
    insertTmpAnimationPointer(&(this -> scrollBar));
}

void Menu::insertElement(UIElement* targetElement, UIElement* linkElement) {
    
    targetElement -> setX(this -> targetX + 5);
    targetElement -> setY(70);
    insertAnimation(new Animation(targetElement, INDENT, targetElement -> getX(), min(this -> menuSize, int(this -> subElements.size())) * 12 + 12, 100));
        
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
            insertAnimation(new Animation(subElements[i], BOUNCE, subElements[i] -> getX(), cnt * 12 + 12, 100));
        }
        return true;
    }

    return false;
}

bool Menu::moveMenuDown() {
    if (this -> menuPos < int(this -> subElements.size()) - this -> menuSize) {
        for (int i = this -> menuPos, cnt = 0; cnt < min(this -> menuSize + 1, int(this -> subElements.size())); i++, cnt++) {
            insertAnimation(new Animation(subElements[i], BOUNCE, subElements[i] -> getX(), (cnt - 1) * 12 + 12, 100));
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
    insertAnimation(new Animation(&(this -> scrollBar), LINEAR, this -> targetX + this -> width - 6, this -> y + 5 + (float(getMenuPos()) / float(this -> getSize()) * (this -> height - 10)), 100));
}

void Menu::scrollDown() {
    if (!moveCursorDown()) {
        moveMenuDown();
    }
    this -> cursor.changeTarget(subElements[this -> menuPos + this -> cursorPos]);    
    //moveCursorDown();
    insertAnimation(new Animation(&(this -> scrollBar), LINEAR, this -> targetX + this -> width - 6, this -> y + 5 + (float(getMenuPos()) / float(this -> getSize()) * (this -> height - 10)), 100));
}

int Menu::getMenuPos() {
    return this -> cursorPos + this -> menuPos;
}

void Menu::drawScrollBar() {
    u8g2.drawLine(constrain(this -> x + this -> width - 5, 0, WIDTH), constrain(this -> y + 4, 0, HEIGHT), constrain(this -> x + this -> width - 5, 0, WIDTH), constrain(this -> y + this -> height - 4, 0, HEIGHT));
    //this -> scrollBar.setX(this -> x + this -> width - 6);
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
    if (this -> linkElements[this -> menuPos + this -> cursorPos] != nullptr && this -> linkElements[this -> menuPos + this -> cursorPos] != this) {
        
        if (this -> linkElements[this -> menuPos + this -> cursorPos] -> isTransition()) {
            aniOut();
            
            while (!tmpAnimationUI.empty()) {
                u8g2.setDrawColor(0);
                u8g2.drawBox(0, 0, 210, 64);
                u8g2.setDrawColor(1);
                currentElement -> draw();
                updateTmp();
                u8g2.sendBuffer();
                animateAll();
            }
        }
        this -> deactivate();
        this -> linkElements[this -> menuPos + this -> cursorPos] -> init();
        this -> linkElements[this -> menuPos + this -> cursorPos] -> activate();
    }
}

void Menu::draw() {
    //u8g2.setClipWindow(this -> x, this -> y, this -> width, this -> height);
    int drawX = constrain(this -> x, 0, WIDTH);
    int drawY = constrain(this -> y, 0, HEIGHT);
    u8g2.drawRFrame(drawX, drawY, constrain(this -> width + (this -> x - drawX), 0, WIDTH), constrain(this -> height + (this -> y - drawY), 0, HEIGHT), 3);
    for (int i = this -> menuPos, cnt = 0; cnt < min(this -> menuSize, int(this -> subElements.size())); i++, cnt++) {
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
    if (kb.getRisingEdgeKey() == std::make_pair(0, 0) && this -> parentElement != this && this -> parentElement != nullptr) {
        aniOut();

        while (!tmpAnimationUI.empty()) {
            this -> scrollBar.setY(this -> y + 5 + (float(getMenuPos()) / float(this -> getSize()) * (this -> height - 10)));
            u8g2.setDrawColor(0);
            u8g2.drawBox(0, 0, 210, 64);
            u8g2.setDrawColor(1);
            currentElement -> draw();
            drawSidebar();
            updateTmp();
            u8g2.sendBuffer();
            animateAll();
        }

        goBack();
    }


    draw();
    this -> cursor.draw();
}