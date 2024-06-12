#include "Calculator.h"

int curtimesyntax = 0;
bool state = false;

Calculator::Calculator(int x, int y, int width, int height, Menu* calcMenu, InputBox* expressionInput) : UIElement(x, y, width, height) {
    this -> calcMenu = calcMenu;
    this -> expressionInput = expressionInput;
    this -> mode = 0;
}
void Calculator::init() {
    this -> calcMenu -> init();
    this -> calcMenu -> activate();
}

void Calculator::activate() {
    currentElement = this;
    insertAnimation(new Animation(this -> expressionInput, INDENT, 0, 57, 500));
}

void Calculator::insertExpression() {
    this -> expressionInput -> insertStr(clipboard);
    clipboard = "";
    mode = 0;
}

void Calculator::enter() {
    if (!syntaxChecker.checkSyntax(this -> expressionInput -> getStr())) {
        state = true;
        curtimesyntax = millis();
    }
    if (state) {
        if (millis() - curtimesyntax > 200) {
            state = false;
        }
        else {
            draw();
            u8g2.drawRFrame(70, 17, 76, 12, 2);
            u8g2.drawStr(73, 24, "INVALID SYNTAX");
            u8g2.sendBuffer();
            delay(400);
            return;
        }
    }
    UIElement* ptr = new ExpressionBlock(0, 0, 196, 12, Expression(this -> expressionInput -> getStr(), RPNMode));
    this -> calcMenu -> insertElement(ptr, ptr);
    this -> expressionInput -> clearStr();
    this -> calcMenu -> scrollDown();
}

void Calculator::draw() {
    
    if (this -> mode == 0) {
        this -> calcMenu -> draw();
        this -> expressionInput -> update();
    }
    if (this -> mode == 1) {
        this -> calcMenu -> update();
        this -> expressionInput -> draw();
    }
   
    u8g2.drawStr(215, 24, ("Cur:" + calcLayout.getLayout().getName()).c_str());
    std::string str = calcLayout.updateString();
    if (kb.getKey(4, 0).getIsPressed()) {
        u8g2.drawStr(215, 36, "SL");

    }
    if (kb.getKey(4, 5).getIsPressed()) {
        u8g2.drawStr(227, 36, "TAB");

    }
    if (angleMode == 0) {
        u8g2.drawStr(215, 48, "RAD");
    }
    else {
        u8g2.drawStr(215, 48, "DEG");
    }
    u8g2.setDrawColor(1);
}

void Calculator::update() {
    std::string str = calcLayout.updateString();
    if (str == "TAB") {
        if (this -> calcMenu -> getSize() > 0) {
            this -> mode = !(this -> mode);
        }
        return;
    }
    else if (clipboard != "") {
        insertExpression();
    }
    else if (str == "ENTER" && this -> expressionInput -> getStr() != "" && this -> mode == 0) {
        enter();
    }
    else if (str == "ESC") {
        this -> calcMenu -> aniOut();
        insertAnimation(new Animation(this -> expressionInput, INDENTINV, 0, 64, 500));
        insertTmpAnimationPointer(this -> expressionInput);
        while (!tmpAnimationUI.empty()) {
            u8g2.setDrawColor(0);
            u8g2.drawBox(0, 0, 210, 64);
            u8g2.setDrawColor(1);
            currentElement -> draw();
            updateTmp();
            u8g2.sendBuffer();
            animateAll();
        }
        
        goBack();
    }
    else if (str == "MODE SWITCH") {
        angleMode = !angleMode;
    }
    else if (str == "RPN") {
        RPNMode = !RPNMode;
    }
    draw();
}