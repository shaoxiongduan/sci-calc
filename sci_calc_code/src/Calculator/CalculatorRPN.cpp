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

void CalculatorRPN::draw() {
    u8g2.setDrawColor(2);
    u8g2.drawRBox(5, 2, 29, 12, 0);
    u8g2.drawStr(7, 2 + 7, "A REG");
    u8g2.drawRFrame(5 + 29 - 1, 2, 55, 12, 0);
    u8g2.setDrawColor(1);
    u8g2.drawStr(37, 9, numToStr(this -> RPN.getT()).c_str());
    u8g2.drawStr(37, 9 + 14, numToStr(this -> RPN.getZ()).c_str());
    u8g2.drawStr(37, 9 + 14 * 2, numToStr(this -> RPN.getY()).c_str());
    u8g2.drawStr(37, 9 + 14 * 3, numToStr(this -> RPN.getX()).c_str());
    //u8g2.drawStr(37, 9 + 14 * 4, (this -> numstr).c_str());
    //calcLayout.draw();
   
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
        this -> RPN.push(parseNumStr());
        this -> numstr = "";
        this -> isNegative = false;
        Serial.println("push");
    }
    else if (str == "ESC") {
        goBack();
    }
    else if (str == "BKSP") {
        this -> RPN.clearX();
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