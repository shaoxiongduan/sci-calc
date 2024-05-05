#include "ListSelector.h"

ListSelector::ListSelector(std::string name, int startVal, int endVal) : UIElement() {
    this -> name = name;
    this -> value = startVal;
    this -> startVal = startVal;
    this -> endVal = endVal;
    this -> linkVal = nullptr;
}

