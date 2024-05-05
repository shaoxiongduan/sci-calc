#include "UIElement.h"

UIElement::UIElement() {
    this -> x = this -> targetX = 0;
    this -> y = this -> targetY = 0;
    this -> width = this -> targetWidth = 0;
    this -> height = this -> targetHeight = 0;
    this -> parentElement = nullptr;
    this -> drawParent = false;
    this -> doTransition = true;
}

UIElement::UIElement(int x, int y) {
    this -> x = this -> targetX = x;
    this -> y = this -> targetY = y;
    this -> width = this -> targetWidth = 0;
    this -> height = this -> targetHeight = 0;
    this -> parentElement = nullptr;
    this -> drawParent = false;
    this -> doTransition = true;
}

UIElement::UIElement(int x, int y, int width, int height) {
    this -> x = this -> targetX = x;
    this -> y = this -> targetY = y;
    this -> width = this -> targetWidth = width;
    this -> height = this -> targetHeight = height;
    this -> parentElement = nullptr;
    this -> drawParent = false;
    this -> doTransition = true;
}

UIElement::UIElement(int x, int y, int width, int height, std::vector <UIElement*> subElements) {
    this -> x = this -> targetX = x;
    this -> y = this -> targetY = y;
    this -> width = this -> targetWidth = width;
    this -> height = this -> targetHeight = height;
    this -> subElements = subElements;
    this -> parentElement = nullptr;
    this -> drawParent = false;
    this -> doTransition = true;
}

UIElement::UIElement(int x, int y, bool drawParent) {
    this -> x = this -> targetX = x;
    this -> y = this -> targetY = y;
    this -> width = this -> targetWidth = 0;
    this -> height = this -> targetHeight = 0;
    this -> parentElement = nullptr;
    this -> drawParent = drawParent;
    this -> doTransition = true;
}

UIElement::UIElement(int x, int y, int width, int height, bool drawParent) {
    this -> x = this -> targetX = x;
    this -> y = this -> targetY = y;
    this -> width = this -> targetWidth = width;
    this -> height = this -> targetHeight = height;
    this -> parentElement = nullptr;
    this -> drawParent = drawParent;
    this -> doTransition = true;
}

UIElement::UIElement(int x, int y, int width, int height, std::vector <UIElement*> subElements, bool drawParent) {
    this -> x = this -> targetX = x;
    this -> y = this -> targetY = y;
    this -> width = this -> targetWidth = width;
    this -> height = this -> targetHeight = height;
    this -> subElements = subElements;
    this -> parentElement = nullptr;
    this -> drawParent = drawParent;
    this -> doTransition = true;
}

// Initialize the UIElement. Overriden by specific UIElement child class.
void UIElement::init() {

}

// Activates the UIElement. Overriden by specific UIElement child class. Called when switching curElement.
void UIElement::activate() {

}

// Activates the UIElement. Overriden by specific UIElement child class. Called when switching curElement.
void UIElement::deactivate() {

}

// Inserts a UIElement pointer into the subElements vector. Used in Menu to dynamically insert new elements.
void UIElement::insert(UIElement* UIElement) {
    this -> subElements.push_back(UIElement);
}

// Gets child UIElement pointer by id
UIElement* UIElement::getNode(int id) {
    return this -> subElements[id];
}

// Gets size of subElements
int UIElement::getSize() {
    return this -> subElements.size();
}

// Gets the x coordinate of the UIElement
int UIElement::getX() {
    return this -> x;
}

// Gets the y coordinate of the UIElement
int UIElement::getY() {
    return this -> y;
}

// Gets the targeted x coordinate of the UIElement.
int UIElement::getTargetX() {
    return this -> targetX;
}

// Gets the targeted y coordinate of the UIElement.
int UIElement::getTargetY() {
    return this -> targetY;
}

// Gets the width of the UIElement.
int UIElement::getWidth() {
    return this -> width;
}

// Gets the height of the UIElement.
int UIElement::getHeight() {
    return this -> height;
}

// Gets whether to draw parent element or not.
bool UIElement::getDrawParent() {
    return this -> drawParent;
}

// Gets whether to animate with transition or not.
bool UIElement::isTransition() {
    return this -> doTransition;
}

// Gets the targeted width of the UIElement.
int UIElement::getTargetWidth() {
    return this -> targetWidth;
}

// Gets the targeted height of the UIElement.
int UIElement::getTargetHeight() {
    return this -> targetHeight;
}

// Sets the x coordinate of the UIElement.
void UIElement::setX(int x) {
    this -> x = x;
}

// Sets the y coordinate of the UIElement.
void UIElement::setY(int y) {
    this -> y = y;
}

// Sets the targeted x coordinate of the UIElement.
void UIElement::setTargetX(int x) {
    this -> targetX = x;
}

// Sets the targeted y coordinate of the UIElement.
void UIElement::setTargetY(int y) {
    this -> targetY = y;
}

// Sets the width of the UIElement.
void UIElement::setWidth(int width) {
    this -> width = width;
}

// Sets the height of the UIElement.
void UIElement::setHeight(int height) {
    this -> height = height;
}

// Sets the targeted width of the UIElement.
void UIElement::setTargetWidth(int width) {
    this -> targetWidth = width;
}

// Sets the targeted height of the UIElement.
void UIElement::setTargetHeight(int height) {
    this -> targetHeight = height;
}

// Sets the parent of the UIElement.
void UIElement::setParent(UIElement* parentElement) {
    this -> parentElement = parentElement;
}

// Renders the UIElement. Overriden in specific UIElement child class.
void UIElement::draw() {

}

// Go back to the parent UIElement.
void UIElement:: goBack() {
    this -> deactivate();
    if (this -> parentElement != nullptr) {
        this -> parentElement -> activate();
    }
}

// Updates the UIElement. Called periodically.
void UIElement::update() {

}