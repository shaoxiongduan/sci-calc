#ifndef CALCULATOR_RPN_H
#define CALCULATOR_RPN_H

#include "../Animation/Animation.h"
#include "../UIElements/Text.h"
#include "../UIElements/Menu.h"
#include "../UIElements/Cursor.h"
#include "../UIElements/Box.h"
#include "../UIElements/InputBox.h"
#include "EvaluatorRPN.h"

class CalculatorRPN : public UIElement {
    public:
        CalculatorRPN(int x, int y, int width, int height);
        
        void init();
        void insertExpression();
        void activate();

        void addToNumStr(std::string str);
        long double parseNumStr();

        void enter();

        void draw();

        void update();

    private:
        std::string numstr;
        EvaluatorRPN RPN;
        bool isNegative;
};

#endif