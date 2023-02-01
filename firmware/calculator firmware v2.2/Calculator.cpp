#include "Calculator.h"

Calculator::Calculator(int x, int y, int width, int height, Menu* calcMenu, InputBox* expressionInput) : UIElement(x, y, width, height) {
    this -> calcMenu = calcMenu;
    this -> expressionInput = expressionInput;
    this -> mode = 0;
}
void Calculator::init() {

}

void Calculator::activate() {
    currentElement = this;
    Serial.printf("hello!!!\n");
    //insertAnimation(new Animation(this, SMOOTH, 0, 0, 500));
    Serial.printf("hello again\n");
}

void Calculator::insertExpression() {
    this -> expressionInput -> insertStr(clipboard);
    clipboard = "";
    mode = 0;
}

void Calculator::enter() {
    UIElement* ptr = new ExpressionBlock(0, 0, 206, 12, Expression(this -> expressionInput -> getStr()));
    this -> calcMenu -> insertElement(ptr, ptr);
    this -> expressionInput -> clearStr();
    this -> calcMenu -> scrollDown();
}

void Calculator::draw() {
    if (this -> mode == 0) {
        //Serial.println("ehfouveheocvheo");
        this -> calcMenu -> draw();
        //Serial.println("ehfouveheocvheo");
        this -> expressionInput -> update();
    }
    if (this -> mode == 1) {
        this -> calcMenu -> update();
        this -> expressionInput -> draw();
    }
    calcLayout.draw();
}

void Calculator::update() {
    //Serial.println("update calc");
    //Serial.println("ehfouveheocvheo");
    std::string str = calcLayout.updateString();
    if (str == "TAB") {
        this -> mode = !(this -> mode);
        return;
    }
    else if (clipboard != "") {
        insertExpression();
    }
    else if (str == "ENTER" && this -> expressionInput -> getStr() != "" && this -> mode == 0) {
        enter();
    }
    else if (str == "ESC") {
        Serial.println("goback");
        goBack();
    }
    draw();
}