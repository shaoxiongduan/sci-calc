#include "MacropadUI.h"

MacropadUI::MacropadUI(MacroPad* macropad) : UIElement(0, 0, 256, 64) {
    this -> macropad = macropad;
}

void MacropadUI::activate() {
    currentElement = this;
}

void MacropadUI::draw() {
    this -> macropad -> update();
    u8g2.drawStr(80, 60, "Hold esc for 1 second to go back");
}

void MacropadUI::update() {
    draw();
    //Serial.println("vuuhfofhdoijfhdiovndiosjdoifjdiofhdoifjdsso");

    if (kb.getKey(0, 0).getIsPressed() && kb.getKey(0, 0).getStatusTime() >= 1000) {
        Serial.println("gobackcc");
        goBack();
    }
}