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

