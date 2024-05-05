#include "Macropad.h"

Macro::Macro() {
    this -> keys = {};
    this -> name = "";
}

Macro::Macro(std::vector <uint16_t> keys) {
    this -> keys = keys;
    this -> name = "";
}

Macro::Macro(std::vector <uint16_t> keys, std::string name) {
    this -> keys = keys;
    this -> name = name;
}

void Macro::writeMacro() {
    if (this -> keys.empty()) {
        return;
    }
    if (bleKeyboard.isConnected()) {
        
        for (uint16_t key : this -> keys) {
            Serial.println(key);
            bleKeyboard.press(key);
        }
        bleKeyboard.releaseAll();
    }
}

std::string Macro::getMacroString() {
    if (this -> keys.empty()) {
        return "";
    }
    if (this -> name != "") {
        return this -> name;
    }
    std::string res;
    for (uint16_t key : this -> keys) {
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
    this -> curLayout = 0;
    this -> prevLayout = 0;
    this -> nxtLayout = 1;
}

Layout MacroPad::getLayout() {
    return this -> layouts[this -> curLayout];
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
        std::pair <int, int> curPos = kb.getChangedKey();
        for (int i = 4; i <= 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (kb.getKey(j, i).getIsPressed()) {
                    u8g2.setDrawColor(0);
                    u8g2.setFontMode(0);
                    u8g2.drawStr((i - 4) * 36 + 4, j * 12 + 10, this -> layouts[this -> curLayout].getMacro(j, i).getMacroString().c_str());
                    u8g2.setDrawColor(1);
                    u8g2.setFontMode(1);
                }
                else {
                    u8g2.drawStr((i - 4) * 36 + 4, j * 12 + 10, this -> layouts[this -> curLayout].getMacro(j, i).getMacroString().c_str());
                }
            }
        }
        u8g2.drawLine(70, 4, 70, 60);
        if (!bleKeyboard.isConnected()) {
            u8g2.drawStr(77, 9, "Bluetooth: not connected.");
            return;
        }
        u8g2.drawStr(77, 9, "Bluetooth: connected!");
        u8g2.drawStr(77, 21, ("Current Layer: " + this -> layouts[this -> curLayout].getName()).c_str());

        if (!(curPos.first == -1 || curPos.second == -1)) {
            this -> curPressed = std::make_pair(curPos.first, curPos.second);
            
            u8g2.drawStr(77, 33, "Key");
            u8g2.drawStr(97, 33, (this -> layouts[this -> curLayout].getName() + "pressed.").c_str());
            if (this -> layouts[this -> curLayout].getMacro(this -> curPressed.first, this -> curPressed.second).getMacroString() == "LAYER SWITCH") {
                if (kb.getKey(this -> curPressed.first, this -> curPressed.second).getClickCnt() == 1) {
                    if (kb.getKey(this -> curPressed.first, this -> curPressed.second).getStatus() == RISING_EDGE) { // toggle layer switch
                        this -> curLayout = this -> nxtLayout;
                    }
                    else {
                        this -> curLayout = this -> prevLayout;
                    }
                }
                if (kb.getKey(this -> curPressed.first, this -> curPressed.second).getClickCnt() == 2) { // switch between layers (locked)
                    if (kb.getKey(this -> curPressed.first, this -> curPressed.second).getStatus() == RISING_EDGE) { // toggle layer switch

                        this -> curLayout = (this -> curLayout + 1) % this -> layouts.size();
                        this -> prevLayout = this -> curLayout;
                        this -> nxtLayout = (this -> curLayout + 1) % this -> layouts.size();
                    }
                }
            }
            else if (kb.getKey(this -> curPressed.first, this -> curPressed.second).getStatus() == RISING_EDGE) {
                Serial.println("executing...");
                this -> layouts[this -> curLayout].getMacro(curPressed.first, curPressed.second).writeMacro();
                Serial.println("execution done!");
            }
            else if (kb.getKey(this -> curPressed.first, this -> curPressed.second).getStatus() == FALLING_EDGE) {
                //this -> layouts[this -> curLayout].getMacro(curPressed.first, curPressed.second).writeMacro();
            }
        }
        if (curPos.first == -1 && curPos.second == -1) {
            if (this -> curIsHeld()) {
                u8g2.drawStr(77, 33, "Key");
                u8g2.drawStr(97, 33, ("[" + std::to_string(this -> curPressed.first) + "]" + "[" + std::to_string(this -> curPressed.second) + "]: " + this -> layouts[this -> curLayout].getMacro(this -> curPressed.first, this -> curPressed.second).getMacroString() + " pressed").c_str());
                u8g2.drawStr(162, 45, ("Clicks: " + std::to_string(kb.getKey(this -> curPressed.first, this -> curPressed.second).getClickCnt()) + ".").c_str());
                u8g2.drawStr(77, 45, ("held for: " + std::to_string(int(kb.getKey(this -> curPressed.first, this -> curPressed.second).getStatusTime())) + "ms.").c_str());
                Serial.printf("Key [%d][%d] from layout %s held.\n", curPressed.first, curPressed.second, this -> layouts[this -> curLayout].getName().c_str());
            }
            else {
                u8g2.drawStr(77, 33, "No keys pressed.");
            }
            //Serial.println("No key pressed.");
        }
        this -> prevtime = curtime;
        sample = false;    
    }

}

std::string MacroPad::updateString() {
    float curtime = millis();
    if (sample) {
        //u8g2.drawBox(30, 40, 10, 10);
        std::pair <int, int> curPos = kb.getChangedKey();
        if (!(curPos.first == -1 || curPos.second == -1)) {
            this -> curPressed = std::make_pair(curPos.first, curPos.second);
            
            //Serial.printf("Key [%d][%d] from layout %s pressed.\n", curPressed.first, curPressed.second, this -> layouts[this -> curLayout].getName().c_str());
            if (this -> layouts[this -> curLayout].getMacro(this -> curPressed.first, this -> curPressed.second).getMacroString() == "LAYER SWITCH") {
                if (kb.getKey(this -> curPressed.first, this -> curPressed.second).getClickCnt() == 1) {
                    if (kb.getKey(this -> curPressed.first, this -> curPressed.second).getStatus() == RISING_EDGE) { // toggle layer switch
                        this -> curLayout = this -> nxtLayout;
                    }
                    else {
                        this -> curLayout = this -> prevLayout;
                    }
                }
                if (kb.getKey(this -> curPressed.first, this -> curPressed.second).getClickCnt() == 2) { // switch between layers (locked)
                    if (kb.getKey(this -> curPressed.first, this -> curPressed.second).getStatus() == RISING_EDGE) { // toggle layer switch

                        this -> curLayout = (this -> curLayout + 1) % this -> layouts.size();
                        this -> prevLayout = this -> curLayout;
                        this -> nxtLayout = (this -> curLayout + 1) % this -> layouts.size();
                        //Serial.printf("curlayout: %d\n", curLayout);
                    }
                }
                return this -> layouts[this -> curLayout].getMacro(curPressed.first, curPressed.second).getMacroString();
            }
            else if (kb.getKey(this -> curPressed.first, this -> curPressed.second).getStatus() == RISING_EDGE) {
                return this -> layouts[this -> curLayout].getMacro(curPressed.first, curPressed.second).getMacroString();
            }
        }
        this -> prevtime = curtime;
        sample = false;
    }
    std::string tmp = "";
    return tmp;
}

void MacroPad::draw() {
    u8g2.drawRFrame(223, 0, 33, 64, 3);
    u8g2.drawStr(225, 9, ("Cur:" + this -> layouts[this -> curLayout].getName()).c_str());
    std::string str = updateString();
    //Serial.println(str.c_str());
    if (kb.getKey(4, 0).getIsPressed()) {
        u8g2.setDrawColor(0);
        u8g2.drawStr(225, 21, "SL");
        u8g2.setDrawColor(1);
    }

}