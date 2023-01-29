#include "ExpressionBlock.h"

ExpressionBlock::ExpressionBlock(int x, int y, int width, int height, Expression expression) : UIElement(x, y, width, height) {
    this -> expression = expression;
    this -> inputText.setText(this -> expression.getExpressionString());
    this -> ans.setText(std::to_string(this -> expression.evaluateExpression()));
}

void ExpressionBlock::activate() {
    clipboard = this -> ans.getStr();
}

void ExpressionBlock::draw() {
    this -> inputText.setX(this -> x);
    this -> inputText.setY(this -> y);

    this -> ans.setX(this -> x + 150);
    this -> ans.setY(this -> y);

    this -> inputText.draw();
    this -> ans.draw();
}

void ExpressionBlock::update() {
    draw();
    clipboard = this -> ans.getStr();
    goBack();
}