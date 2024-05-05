#include "Box.h"

Box::Box() : UIElement() {
    this -> width = 3;
}

void Box::draw() {
    u8g2.drawBox(constrain(this -> x, 0, WIDTH), constrain(this -> y, 0, HEIGHT), constrain(this -> width + (this -> x - constrain(this -> x, 0, WIDTH)), 0, WIDTH), constrain(this -> height + (this -> y - constrain(this -> y, 0, HEIGHT)), 0, HEIGHT));
}
