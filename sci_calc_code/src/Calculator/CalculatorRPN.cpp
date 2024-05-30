#include "CalculatorRPN.h"


CalculatorRPN::CalculatorRPN(int x, int y, int width, int height) : UIElement(x, y, width, height) {
    this -> isNegative = false;
}
void CalculatorRPN::init() {

}

void CalculatorRPN::activate() {
    currentElement = this;
}

void CalculatorRPN::enter() {
    
    

}

void CalculatorRPN::drawReg(int x, int y, std::string name, long double value) {
    u8g2.setDrawColor(2);
    u8g2.drawRBox(x + 5, y + 2, u8g2.getStrWidth(name.c_str()) + 4, 12, 0);
    u8g2.drawStr(x + 7, y + 2 + 7, name.c_str());
    u8g2.drawRFrame(x + 5 + u8g2.getStrWidth(name.c_str()) + 4 - 1, y + 2, 100, 12, 0);
    u8g2.setDrawColor(1);
    u8g2.drawStr(x + 37, y + 2 + 7, numToStr(value).c_str());
}

void CalculatorRPN::drawInfo(int x, int y, std::string keyStr, std::string funcStr) {
    u8g2.setDrawColor(2);
    u8g2.drawRBox(x + 5, y + 2, u8g2.getStrWidth(keyStr.c_str()) + 4, 12, 0);
    u8g2.drawStr(x + 7, y + 2 + 7, keyStr.c_str());
    u8g2.setDrawColor(1);
    u8g2.drawStr(x + u8g2.getStrWidth(keyStr.c_str()) + 4 + 1 + 6, y + 2 + 7, (funcStr).c_str());
}

void CalculatorRPN::draw() {
    // u8g2.setDrawColor(2);
    // u8g2.drawRBox(5, 2, 29, 12, 0);
    // u8g2.drawStr(7, 2 + 7, "t REG");
    // u8g2.drawRFrame(5 + 29 - 1, 2, 55, 12, 0);
    // u8g2.setDrawColor(1);
    // u8g2.drawStr(37, 9, numToStr(this -> RPN.getT()).c_str());
    // u8g2.drawStr(37, 9 + 14, numToStr(this -> RPN.getZ()).c_str());
    // u8g2.drawStr(37, 9 + 14 * 2, numToStr(this -> RPN.getY()).c_str());
    // u8g2.drawStr(37, 9 + 14 * 3, numToStr(this -> RPN.getX()).c_str());
    drawReg(0, 0, "T REG", this -> RPN.getT());
    drawReg(0, 14, "Z REG", this -> RPN.getZ());
    drawReg(0, 28, "Y REG", this -> RPN.getY());
    drawReg(0, 42, "X REG", this -> RPN.getX());

    drawInfo(134, 0, "TAB", "POP STACK");
    drawInfo(134, 14, "RPN", "SWAP XY");
    drawInfo(134, 28, "ENT", "PUSH STACK");
    drawInfo(134, 42, "(SHFT)DEL", "C/AC");
    //u8g2.drawStr(37, 9 + 14 * 4, (this -> numstr).c_str());
    //calcLayout.draw();
    u8g2.drawLine(135, 2, 135, 64 - 9);
    u8g2.drawStr(215, 24, ("Cur:" + calcLayout.getLayout().getName()).c_str());
    std::string str = calcLayout.updateString();
    //Serial.println(str.c_str());
    //u8g2.setDrawColor(0);
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

void CalculatorRPN::addToNumStr(std::string str) {
    if (str == "-") {
        this -> isNegative = true;
    }
    if (str == ".") {
        if (this -> numstr.find('.') != -1) {
            return;
        }
    }
    this -> numstr += str;
}

long double CalculatorRPN::parseNumStr() {
    long double res = 0;
    bool pastDecimalPoint = false;
    long double cnt = 1;
    for (char c : this -> numstr) {
        if (pastDecimalPoint) cnt *= 10;
        if (c == '.') pastDecimalPoint = true;
        if ('0' <= c && c <= '9') res = res * 10 + (c - '0');
    }
    res /= cnt;
    if (this -> isNegative) {
        //res = -res;
    }
    return res;
}

void CalculatorRPN::update() {
    std::string str = calcLayout.updateString();
    Serial.println(str.c_str());
    if (str == "") {

    }
    else if (strIsOperator(str)) {
        this -> RPN.evaluate(convertToEnum(str));
        this -> numstr = "";
        this -> isNegative = false;
        Serial.println("operator");
    }
    else if (strIsNum(str)) {
        addToNumStr(str);
        this -> RPN.setX(parseNumStr());
        this -> isNegative = false;
        Serial.println("number");
    }
    else if (str == "ENTER") {
        this -> RPN.push();
        this -> numstr = "";
        this -> isNegative = false;
        Serial.println("push");
    }
    else if (str == "ESC") {
        goBack();
    }
    else if (str == "BKSP") {
        if (kb.getKey(4, 0).getIsPressed()) {
            Serial.println("AC!!!!");
            this -> RPN.clearAll();
        }
        else {
            this -> RPN.clearX();
        }
        this -> numstr = "";
    }
    else if (str == "TAB") {
        this -> RPN.pop();
    }
    else if (str == "MODE SWITCH") {
        angleMode = !angleMode;
    }
    else if (str == "RPN SWITCH") {
        this -> RPN.swap();
        this -> numstr = numToStr(this -> RPN.getX());
    }
    draw();
}