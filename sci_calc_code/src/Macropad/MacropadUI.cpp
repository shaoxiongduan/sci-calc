#include "MacropadUI.h"

MacropadUI::MacropadUI(MacroPad* macropad) : UIElement(0, 0, 256, 64) {
    this -> macropad = macropad;
}

void MacropadUI::activate() {
    currentElement = this;
}

void MacropadUI::draw() {
    u8g2.drawRFrame(0, 0, 210, 64, 3);
    this -> macropad -> update();
    u8g2.drawStr(78, 58, "Hold esc to go back");
}

void MacropadUI::update() {
    draw();
    //Serial.println("vuuhfofhdoijfhdiovndiosjdoifjdiofhdoifjdsso");

    if (kb.getKey(0, 0).getIsPressed() && kb.getKey(0, 0).getStatusTime() >= 1000) {
        Serial.println("gobackcc");
        goBack();
    }
}