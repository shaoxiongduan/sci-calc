#include "UIElement.h"

UIElement::UIElement() {
    this -> x = this -> targetX = 0;
    this -> y = this -> targetY = 0;
    this -> width = this -> targetWidth = 0;
    this -> height = this -> targetHeight = 0;
    this -> parentElement = nullptr;
}

UIElement::UIElement(int x, int y) {
    this -> x = this -> targetX = x;
    this -> y = this -> targetY = y;
    this -> width = this -> targetWidth = 0;
    this -> height = this -> targetHeight = 0;
    this -> parentElement = nullptr;
}

UIElement::UIElement(int x, int y, int width, int height) {
    this -> x = this -> targetX = x;
    this -> y = this -> targetY = y;
    this -> width = this -> targetWidth = width;
    this -> height = this -> targetHeight = height;
    this -> parentElement = nullptr;
}

UIElement::UIElement(int x, int y, int width, int height, std::vector <UIElement*> subElements) {
    this -> x = this -> targetX = x;
    this -> y = this -> targetY = y;
    this -> width = this -> targetWidth = width;
    this -> height = this -> targetHeight = height;
    this -> subElements = subElements;
    this -> parentElement = nullptr;
}

void UIElement::init() {

}

void UIElement::activate() {

}

void UIElement::deactivate() {

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

int UIElement::getTargetX() {
    return this -> targetX;
}

int UIElement::getTargetY() {
    return this -> targetY;
}

int UIElement::getWidth() {
    return this -> width;
}

int UIElement::getHeight() {
    return this -> height;
}

int UIElement::getTargetWidth() {
    return this -> targetWidth;
}

int UIElement::getTargetHeight() {
    return this -> targetHeight;
}

void UIElement::setX(int x) {
    this -> x = x;
}

void UIElement::setY(int y) {
    this -> y = y;
}

void UIElement::setTargetX(int x) {
    this -> targetX = x;
}

void UIElement::setTargetY(int y) {
    this -> targetY = y;
}

void UIElement::setWidth(int width) {
    this -> width = width;
}

void UIElement::setHeight(int height) {
    this -> height = height;
}

void UIElement::setTargetWidth(int width) {
    this -> targetWidth = width;
}

void UIElement::setTargetHeight(int height) {
    this -> targetHeight = height;
}

void UIElement::setParent(UIElement* parentElement) {
    this -> parentElement = parentElement;
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

void UIElement::goBack() {
    Serial.printf("deactivating\n");
    this -> deactivate();
    Serial.printf("deactivated!\n");
    if (this -> parentElement != nullptr) {
        
        this -> parentElement -> activate();
    }
    Serial.printf("activated parent!\n");
}

void UIElement::update() {

}