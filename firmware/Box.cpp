#include "Box.h"

Box::Box() : UIElement() {
    this -> width = 3;
}

void Box::draw() {
    u8g2.drawBox(this -> x, this -> y, this -> width, this -> height);
}
