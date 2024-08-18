#include "EvaluatorRPN.h"

EvaluatorRPN::EvaluatorRPN() {
    this -> x = this -> y = this -> z = this -> t = this -> store = 0;
}

// Rolls the stack down
void EvaluatorRPN::rollDown() {
    float tmpx = this -> x;
    this -> x = this -> y;
    this -> y = this -> z;
    this -> z = this -> t;
    this -> t = tmpx;
}

// Rolls the stack up
void EvaluatorRPN::rollUp() {
    float tmpx = this -> x;
    this -> x = this -> y;
    this -> y = this -> z;
    this -> z = this -> t;
    this -> t = tmpx;
}

// Pushes an element into the stack, overriding the store register
void EvaluatorRPN::push() {
    this -> store = this -> t;
    this -> t = this -> z;
    this -> z = this -> y;
    this -> y = this -> x;
    this -> x = 0;
}

// Pops the stack and drops the value from the store register down
void EvaluatorRPN::pop() {
    this -> x = this -> y;
    this -> y = this -> z;
    this -> z = this -> t;
    this -> t = this -> store;
}

// Swaps register X and Y
void EvaluatorRPN::swap() {
    float tmpx = this -> x;
    this -> x = this -> y;
    this -> y = tmpx;
}

void EvaluatorRPN::clearX() {
    this -> x = 0;
}

void EvaluatorRPN::clearAll() {
    this -> x = this -> y = this -> z = this -> t = this -> store = 0;
}

// Evaluates the operation inputted. Returns true if the operation is valid, and false if it is an invalid operation
bool EvaluatorRPN::evaluate(Token op) {
    switch (op) {
        case NUM: return false;
        case VAR: return false;
        case NEGATIVE: return false;
        case ADD: this -> x += this -> y; this -> y = 0; return true;
        case SUB: this -> x = this -> y - this -> x; this -> y = 0; return true;
        case MUL: this -> x *= this -> y; this -> y = 0; return true;
        case DIV:
            if (this -> x != 0) {
                this -> x = this -> y / this -> x; this -> y = 0; return true;
            }
            else {
                return false;
            }
        case POW: this -> x = pow(this -> x, this -> y); this -> y = 0; return true;
        case SQRT: this -> x = sqrtl(this -> x); return true;
        case LN: this -> x = logl(this -> x); return true;
        case EXP: this -> x = expl(this -> x); return true;
        case SIN: this -> x = sinl((angleMode ? 0.0174532925 : 1.0) * this -> x);
        case COS: this -> x = cosl((angleMode ? 0.0174532925 : 1.0) * this -> x);
        case TAN: this -> x = tanl((angleMode ? 0.0174532925 : 1.0) * this -> x);
        case SEC: this -> x = 1.0 / cosl((angleMode ? 0.0174532925 : 1.0) * this -> x);
        case CSC: this -> x = 1.0 / sinl((angleMode ? 0.0174532925 : 1.0) * this -> x);
        case COT: this -> x = 1.0 / tanl((angleMode ? 0.0174532925 : 1.0) * this -> x);
        case ASIN: this -> x = (angleMode ? 57.2957795 : 1.0) * asinl(this -> x);
        case ACOS: this -> x = (angleMode ? 57.2957795 : 1.0) * acosl(this -> x);
        case ATAN: this -> x = (angleMode ? 57.2957795 : 1.0) * atanl(this -> x);
        default: return false;
    }
}

long double EvaluatorRPN::getX() {
    return this -> x;
}

long double EvaluatorRPN::getY() {
    return this -> y;
}

long double EvaluatorRPN::getZ() {
    return this -> z;
}

long double EvaluatorRPN::getT() {
    return this -> t;
}

long double EvaluatorRPN::getStore() {
    return this -> store;
}

void EvaluatorRPN::setX(long double x) {
    this -> x = x;
}