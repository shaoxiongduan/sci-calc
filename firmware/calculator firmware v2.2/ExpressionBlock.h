#ifndef EXPRESSION_BLOCK_H
#define EXPRESSION_BLOCK_H

#include "Util.h"
#include "Text.h"
#include "Menu.h"
#include "Cursor.h"
#include "Box.h"
#include "InputBox.h"
#include "Expression.h"

class ExpressionBlock : public UIElement {
    public:
        ExpressionBlock(int x, int y, int width, int height, Expression expression);

        std::string copyAns();

        void activate();

        void draw();

        void update();

    private:
        Text inputText;
        Text ans;
        Expression expression;
        std::string rawRes;
};

#endif