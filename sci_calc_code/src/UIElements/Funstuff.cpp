#include "Funstuff.h"

Funstuff::Funstuff() : UIElement(0, 0, 256, 64) {
    this -> expression = "default";
}
Funstuff::Funstuff(std::string expression) : UIElement(0, 0, 256, 64) {
    this -> expression = expression;
}

void Funstuff::activate() {
    currentElement = this;
    HIDE_SIDEBAR = true;
}

void Funstuff::drawDefaultSmile() {
    /*
    delay(500);
    u8g2.setFont(u8g2_font_crox5hb_tf);
    u8g2.setFontDirection(1);
    u8g2.drawUTF8(WIDTH / 2, HEIGHT / 2 - 20, " :)");
    u8g2.sendBuffer();
    delay(500);
    u8g2.clearBuffer();
    u8g2.drawUTF8(WIDTH / 2, HEIGHT / 2 - 20, " :D");
    u8g2.sendBuffer();
    delay(500);
    u8g2.clearBuffer();
    u8g2.drawUTF8(WIDTH / 2, HEIGHT / 2 - 20, " :P");
    u8g2.sendBuffer();
    delay(500);
    u8g2.clearBuffer();
    u8g2.drawUTF8(WIDTH / 2, HEIGHT / 2 - 20, " :(");
    u8g2.sendBuffer();
    delay(500);
    u8g2.clearBuffer();
    u8g2.drawUTF8(WIDTH / 2, HEIGHT / 2 - 20, " :o");

    u8g2.setFontDirection(0);
    u8g2.setFont(u8g2_font_crox3hb_tf);
    u8g2.sendBuffer();
    delay(500);
    u8g2.clearBuffer();
    u8g2.drawUTF8(WIDTH / 2 - 15, HEIGHT / 2, "^_^");
    u8g2.sendBuffer();
    delay(500);
    u8g2.clearBuffer();
    u8g2.drawUTF8(WIDTH / 2 - 15, HEIGHT / 2, ">w<");
    u8g2.sendBuffer();
    delay(500);
    u8g2.clearBuffer();
    u8g2.drawUTF8(WIDTH / 2 - 15, HEIGHT / 2, "O_o");
    u8g2.sendBuffer();
    delay(500);
    u8g2.clearBuffer();
    u8g2.drawUTF8(WIDTH / 2 - 15, HEIGHT / 2, "o_O");
    */
    u8g2.setFont(u8g2_font_fub42_tf);
    u8g2.setFontDirection(1);
    u8g2.drawUTF8(WIDTH / 2, HEIGHT / 2 - 40, " :)");
    u8g2.sendBuffer();
    u8g2.setFont(u8g2_font_profont10_mf);
    u8g2.setFontDirection(0);
}

void Funstuff::draw() {
    if (this -> expression == "default") {
        drawDefaultSmile();
    }
    drawDefaultSmile();
}

void Funstuff::update() {
    draw();
    //Serial.println("vuuhfofhdoijfhdiovndiosjdoifjdiofhdoifjdsso");

    if (kb.getKey(0, 0).getIsPressed()) {
        goBack();
        HIDE_SIDEBAR = false;
    }
}