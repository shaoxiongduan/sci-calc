#include "Checkbox.h"

Checkbox::Checkbox() {
    this -> state = false;
    this -> linkBool = nullptr;
}

Checkbox::Checkbox(bool* linkBool) {
    this -> state = false;
    this -> linkBool = linkBool;
}

Checkbox::Checkbox(int x, int y, bool* linkBool) {
    this -> x = x;
    this -> y = y;
    this -> state = false;
    this -> linkBool = linkBool;
}
