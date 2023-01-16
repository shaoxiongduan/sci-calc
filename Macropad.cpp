#include "Macropad.h"

Macro::Macro() {

}

Macro::Macro(std::vector <uint8_t> keys) {
    this -> keys = keys;
}

void Macro::writeMacro() {
    if (bleKeyboard.isConnected()) {
        
        for (uint8_t key : this -> keys) {
            Serial.println(key);
            bleKeyboard.press(key);
        }
        bleKeyboard.releaseAll();
    }
}

Layout::Layout(std::string name, Macro macros[ROWCNT][COLCNT]) {
    this -> name = name;
    for (int i = 0; i < ROWCNT; i++) {
        for (int j = 0; j < COLCNT; j++) {
            this -> macros[i][j] = macros[i][j];
        }
    }
}

std::string Layout::getName() {
    return this -> name;
}

Macro Layout::getMacro(int row, int col) {
    return this -> macros[row][col];
}

MacroPad::MacroPad(std::vector <Layout> layouts) {
    this -> layouts = layouts;
}

void MacroPad::update() {
    float curtime = millis();
    if (sample) {
        //u8g2.drawBox(30, 40, 10, 10);
        std::pair <int, int> curPos = kb.getCurKey();
        if (curPos.first == -1 && curPos.second == -1) {
            u8g2.drawStr(80, 12, "No keys pressed.");
            //Serial.println("No key pressed.");
        }
        else {
            u8g2.drawStr(80, 12, "Key");
            u8g2.drawStr(100, 12, (this -> layouts[this -> curLayout].getName() + "pressed.").c_str());
            Serial.printf("Key [%d][%d] from layout %s pressed.\n", curPos.first, curPos.second, this -> layouts[this -> curLayout].getName());
            this -> layouts[this -> curLayout].getMacro(curPos.first, curPos.second).writeMacro();
        }
        this -> prevtime = curtime;
        sample = false;
    }
}

void MacroPad::draw() {

}