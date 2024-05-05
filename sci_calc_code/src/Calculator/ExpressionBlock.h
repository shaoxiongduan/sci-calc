#ifndef EXPRESSION_BLOCK_H
#define EXPRESSION_BLOCK_H

#include "../Utils/Util.h"
#include "../UIElements/Text.h"
#include "../UIElements/Menu.h"
#include "../UIElements/Cursor.h"
#include "../UIElements/Box.h"
#include "../UIElements/InputBox.h"
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