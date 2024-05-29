#ifndef EVALUATOR_RPN_H
#define EVALUATOR_RPN_H

#include "../Utils/Util.h"

class EvaluatorRPN {
    public:
        EvaluatorRPN();

        bool evaluate(Token op);

        void rollDown();
        void rollUp();
        void push(long double num);
        void pop();
        void swap();
        void clearX();
        void clearAll();
        long double getX();
        long double getY();
        long double getZ();
        long double getT();
        long double getStore();
        void setX(long double x);

    private:
        long double x, y, z, t, store;
};

#endif