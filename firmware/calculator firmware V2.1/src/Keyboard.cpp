#include "Keyboard.h"

Key::Key() {

}

Key::Key(int id) {
    this -> id = id;
    this -> status = NOT_PRESSED;
}

void Key::modifyKey(float pressTime, float startPress, float endPress, bool isPressed, KeyStatus status) {
    this -> pressTime = pressTime;
    this -> startPress = startPress;
    this -> endPress = endPress;
    this -> isPressed = isPressed;
    this -> status = status;
}

void Key::updateKey(bool curState, float curtime) {
    if (curState) {
        if (!(this -> isPressed)) {
            this -> isPressed = true;
            this -> status = RISING_EDGE;
            this -> pressTime = 0;
            this -> startPress = curtime;
        }
        else if (this -> isPressed) {
            this -> status = PRESSED;
            this -> pressTime = curtime - startPress;
        }
    }
    else {
        if (!(this -> isPressed)) {
            this -> status = NOT_PRESSED;
        }
        else if (this -> isPressed) {
            this -> isPressed = false;
            this -> status = FALLING_EDGE;
            this -> pressTime = 0;
            this -> endPress = curtime;
            this -> startPress = 0;
        }
    }
}

Key Key::getKey() {
    return *this;
}

bool Key::getIsPressed() {
    return this -> isPressed;
}

float Key::getPressTime() {
    return this -> pressTime;
}

KeyStatus Key::getStatus() {
    return this -> status;
}


Keyboard::Keyboard() {
    
}

void Keyboard::init() {
    for (int i = 0; i < ROWCNT; i++) {
        pinMode(ROW_MISO[i], INPUT_PULLDOWN);
    }
    for (int i = 0; i < COLCNT; i++) {
        pinMode(COL_MOSI[i], OUTPUT);
        digitalWrite(COL_MOSI[i], LOW);
    }
}


void Keyboard::update() {
    float curtime = millis();
    if (curtime - this -> prevtime > REFRESH_DURATION) {
        sample = true;
        for (int i = 0; i < COLCNT; i++) {
            int curCol = COL_MOSI[i];
            for (int j = 0; j < ROWCNT; j++) {
                digitalWrite(curCol, HIGH);
                //delay(10);
                int curRow = ROW_MISO[j];
                //Serial.printf("Key[%d][%d]: [%d][%d] %d\n", j, i, curRow, curCol, digitalRead(curRow));
                this -> keys[j][i].updateKey(digitalRead(curRow), curtime);
                digitalWrite(curCol, LOW);  
            }
            //delay(10);
        }
    }
    this -> prevtime = curtime;
}

Key Keyboard::getKey(int row, int col) {
    return this -> keys[row][col];
}

std::pair <int, int> Keyboard::getCurKey() {
    for (int i = 0; i < ROWCNT; i++) {
        for (int j = 0; j < COLCNT; j++) {
            if (this -> keys[i][j].getStatus() == RISING_EDGE) {
                return std::make_pair(i, j);
            }
        }
    }
    return std::make_pair(-1, -1);
}

void Keyboard::printKeys() {
    for (int i = 0; i < ROWCNT; i++) {
        for (int j = 0; j < COLCNT; j++) {
            //Serial.printf("Key[%d][%d]: isPressed: %d, pressTime: %lf\n", i, j, this -> keys[i][j].getIsPressed(), this -> keys[i][j].getPressTime());
            std::string status;
            switch (this -> keys[i][j].getStatus()) {
                case NOT_PRESSED:
                    status = "N";
                    break;
                case PRESSED:
                    status = "P";
                    break;
                case RISING_EDGE:
                    status = "R";
                    break;
                case FALLING_EDGE:
                    status = "F";
                    break;
                default:
                    status = "N";
            }
            if (this -> keys[i][j].getIsPressed()) {
                u8g2.setDrawColor(0);
                u8g2.drawStr(j * 12, i * 12 + 12, status.c_str());
                //delay(10);
                u8g2.setDrawColor(1);
            }
            else {
                u8g2.drawStr(j * 12, i * 12 + 12, status.c_str());
                //delay(10);
            }
        }
    }
    //Serial.print("\n");
}
