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

std::string Macro::getMacroString() {
    std::string res;
    for (uint8_t key : this -> keys) {
        std::string cur = getKeyString(key);
        res += cur + "+";
    }
    res.pop_back();
    return res;
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

bool MacroPad::curIsHeld() {
    if (kb.getKey(this -> curPressed.first, this -> curPressed.second).getStatus() == PRESSED) {
        return true;
    }
    return false;
}

void MacroPad::update() {
    float curtime = millis();
    if (sample) {
        //u8g2.drawBox(30, 40, 10, 10);
        std::pair <int, int> curPos = kb.getCurKey();
        u8g2.drawLine(70, 8, 70, 64);
        u8g2.drawStr(80, 12, ("Current Layer: " + this -> layouts[this -> curLayout].getName()).c_str());

        if (!(curPos.first == -1 || curPos.second == -1)) {
            
            u8g2.drawStr(80, 24, "Key");
            u8g2.drawStr(100, 24, (this -> layouts[this -> curLayout].getName() + "pressed.").c_str());
            Serial.printf("Key [%d][%d] from layout %s pressed.\n", curPos.first, curPos.second, this -> layouts[this -> curLayout].getName());
            if (curPos.first == 0 && curPos.second == 4) {
                this -> curLayout = (this -> curLayout + 1) % this -> layouts.size();
            }
            this -> layouts[this -> curLayout].getMacro(curPos.first, curPos.second).writeMacro();
            this -> curPressed = std::make_pair(curPos.first, curPos.second);
        }
        if (curPos.first == -1 && curPos.second == -1) {
            if (this -> curIsHeld()) {
                u8g2.drawStr(80, 24, "Key");
                u8g2.drawStr(100, 24, ("[" + std::to_string(this -> curPressed.first) + "]" + "[" + std::to_string(this -> curPressed.second) + "]: " + this -> layouts[this -> curLayout].getMacro(this -> curPressed.first, this -> curPressed.second).getMacroString() + " held.").c_str());
                Serial.printf("Key [%d][%d] from layout %s held.\n", curPos.first, curPos.second, this -> layouts[this -> curLayout].getName());
            }
            else {
                u8g2.drawStr(80, 24, "No keys pressed.");
            }
            //Serial.println("No key pressed.");
        }
        this -> prevtime = curtime;
        sample = false;
    }
}

void MacroPad::draw() {

}