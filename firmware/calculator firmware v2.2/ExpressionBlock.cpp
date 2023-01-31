#include "ExpressionBlock.h"

ExpressionBlock::ExpressionBlock(int x, int y, int width, int height, Expression expression) : UIElement(x, y, width, height) {
    this -> expression = expression;
    this -> inputText.setText(this -> expression.getExpressionString());
    long double tmp = this -> expression.evaluateExpression();
    this -> ans.setText(numToStr(tmp));
    this -> rawRes = std::to_string(tmp);
}

void ExpressionBlock::activate() {
    clipboard = this -> ans.getStr();
}

void ExpressionBlock::draw() {
    this -> inputText.setX(this -> x);
    this -> inputText.setY(this -> y);

    this -> ans.setX(this -> x + 205 - ans.getStr().size() * 5);
    this -> ans.setY(this -> y);

    this -> inputText.draw();
    this -> ans.draw();
}

void ExpressionBlock::update() {
    draw();
    clipboard = this -> rawRes;
    goBack();
}