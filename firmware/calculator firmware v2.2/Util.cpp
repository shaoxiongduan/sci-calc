#include "Util.h"

int lastNode = -1;
std::string tokenStr[MAXOP] = {"+", "-", "*", "/", "^", "sqrt", "ln", "exp", "sin", "cos", "tan", "sec", "csc", "cot", "asin", "acos", "atan", "(", ")", "=", "-", "NUM", "VAR"};
U8G2_SSD1322_NHD_256X64_F_4W_HW_SPI u8g2(U8G2_R0, SPI_CS, SPI_DC);


bool sample = false;
byte ROW_MISO[ROWCNT] = {33, 32, 35, 34, 39};
byte COL_MOSI[COLCNT] = {13, 12, 14, 27, 26, 25};

char keys[ROWCNT][COLCNT] = {
    {'i', '/', '*', '-', 'a', 'b'},
    {'7', '8', '9', '+', 'c', 'd'},
    {'4', '5', '6', '^', 'e', 'f'},
    {'1', '2', '3', 'e', 'g', 'h'},
    {'0', '.', 'f', 'd', 'i', 'j'}
};

AnimationType menuScroll = BOUNCE;
AnimationType cursorScroll = LINEAR;
AnimationType menuEntry = BOUNCE;
AnimationType sliderMove = BOUNCE;

//BleKeyboard bleKeyboard("SCI-CALC", "SHAP", 100);


//Keypad keypad = Keypad(makeKeymap(keys), ROW_MISO, COL_MOSI, ROWCNT, COLCNT);

/*
void printKeys() {
    Serial.print(keypad.getKeys());
    for (int i = 0; i < ROWCNT; i++) {
        for (int j = 0; j < COLCNT; j++) {
            bool flag = false;
            for (int k = 0; k < LIST_MAX; k++) {
                if (keys[i][j] == keypad.key[k].kchar) {
                    flag = true;
                }
            }

            if (flag) {
                std::string status;
                switch (keypad.key[i].kstate) {
                    case IDLE:
                        status = "I";
                        break;
                    case PRESSED:
                        status = "P";
                        break;
                    case HOLD:
                        status = "H";
                        break;
                    case RELEASED:
                        status = "R";
                        break;
                    default:
                        status = "N";
                }
                u8g2.setDrawColor(0);
                u8g2.drawStr(j * 12, i * 12 + 12, status.c_str());
                u8g2.setDrawColor(1);
            }
            else {
                u8g2.drawStr(j * 12, i * 12 + 12, "N");
            }
        }
    }
}
*/

std::string getKeyString(uint16_t x) {
    switch (x) {
        case KEY_LEFT_CTRL: return "L CTRL";
        case KEY_LEFT_SHIFT: return "L SHIFT";
        case KEY_LEFT_ALT: return "L ALT";
        case KEY_LEFT_GUI: return "L GUI";
        case KEY_RIGHT_CTRL: return "R CTRL";
        case KEY_RIGHT_SHIFT: return "R SHIFT";
        case KEY_RIGHT_ALT: return "R ALT";
        case KEY_RIGHT_GUI: return "R GUI";

        case KEY_UP_ARROW: return "UP";
        case KEY_DOWN_ARROW: return "DOWN";
        case KEY_LEFT_ARROW: return "LEFT";
        case KEY_RIGHT_ARROW: return "RIGHT";
        case KEY_BACKSPACE: return "BKSP";
        case KEY_TAB: return "TAB";
        case KEY_RETURN: return "ENTER";
        case KEY_ESC: return "ESC";
        case KEY_INSERT: return "INS";
        case KEY_PRTSC: return "PRTSC";
        case KEY_DELETE: return "DEL";
        case KEY_PAGE_UP: return "PG UP";
        case KEY_PAGE_DOWN: return "PG DN";
        case KEY_HOME: return "HOME";
        case KEY_END: return "END";
        case KEY_CAPS_LOCK: return "CAPS LK";
        case KEY_F1: return "F1";
        case KEY_F2: return "F2";
        case KEY_F3: return "F3";
        case KEY_F4: return "F4";
        case KEY_F5: return "F5";
        case KEY_F6: return "F6";
        case KEY_F7: return "F7";
        case KEY_F8: return "F8";
        case KEY_F9: return "F9";
        case KEY_F10: return "F10";
        case KEY_F11: return "F11";
        case KEY_F12: return "F12";
        case KEY_F13: return "F13";
        case KEY_F14: return "F14";
        case KEY_F15: return "F15";
        case KEY_F16: return "F16";
        case KEY_F17: return "F17";
        case KEY_F18: return "F18";
        case KEY_F19: return "F19";
        case KEY_F20: return "F20";
        case KEY_F21: return "F21";
        case KEY_F22: return "F22";
        case KEY_F23: return "F23";
        case KEY_F24: return "F24";
        case KEY_LAYER_SWITCH: return "LAYER SWITCH";
        case KEY_EXP: return "exp";
        case KEY_LN: return "ln";
        case KEY_SIN: return "sin";
        case KEY_COS: return "cos";
        case KEY_TAN: return "tan";
        case KEY_ASIN: return "asin";
        case KEY_ACOS: return "acos";
        case KEY_ATAN: return "atan";
        case KEY_SEC: return "sec";
        case KEY_CSC: return "csc";
        case KEY_COT: return "cot";
        case KEY_SQRT: return "sqrt";
        case KEY_MODE_SWITCH: return "MODE SWITCH";
        default:
            std::string res(1, char(x));
        return res;
    }
}

bool strIsOperator(std::string str) {
    for (int i = 0; i < MAXOP; i++) {
        if (str == tokenStr[i]) return true;
    }
    return false;
}

bool cmpLongDouble(long double a, long double b) {
    if (fabsl(a - b) <= EPSILON) return true;
    return false;
}



int getPrecedenceToken(Token token) {
    switch(token) {
        case EQUALS: return 0;
        case ADD: case SUB: return 1;
        case MUL: case DIV: return 2;
        case POW: return 3;
        case SIN: case COS: case TAN: case SEC: case CSC: case COT: case ASIN: case ACOS: case ATAN: case LN: case EXP: case SQRT: case NEGATIVE: return 4;
        default: return 5;
    }
}


Token convertToEnum(std::string s) {
    if (s == "+") return ADD;
    if (s == "-") return SUB;
    if (s == "*") return MUL;
    if (s == "/") return DIV;
    if (s == "^") return POW;
    if (s == "sqrt") return SQRT;
    if (s == "ln") return LN;
    if (s == "exp") return EXP;
    if (s == "sin") return SIN;
    if (s == "cos") return COS;
    if (s == "tan") return TAN;
    if (s == "sec") return SEC;
    if (s == "csc") return CSC;
    if (s == "cot") return COT;
    if (s == "asin") return ASIN;
    if (s == "acos") return ACOS;
    if (s == "atan") return ATAN;
    if (s == "(") return LPARA;
    if (s == ")") return RPARA;
    if (s == "=") return EQUALS;
    if ('0' <= s[0] && s[0] <= '9' || s[0] == '.') return NUM;
    return VAR;
}

std::string convertToString(Token t) {
    if (t == ADD) return "ADD";
    if (t == SUB) return "SUB";
    if (t == MUL) return "MUL";
    if (t == DIV) return "DIV";
    if (t == POW) return "POW";
    if (t == SQRT) return "SQRT";
    if (t == LN) return "LN";
    if (t == EXP) return "EXP";
    if (t == SIN) return "SIN";
    if (t == COS) return "COS";
    if (t == TAN) return "TAN";
    if (t == SEC) return "SEC";
    if (t == CSC) return "CSC";
    if (t == COT) return "COT";
    if (t == ASIN) return "ASIN";
    if (t == ACOS) return "ACOS";
    if (t == ATAN) return "ATAN";
    if (t == LPARA) return "LPARA";
    if (t == RPARA) return "RPARA";
    if (t == NUM) return "NUM";
    if (t == EQUALS) return "EQUALS";
    if (t == NEGATIVE) return "NEGATIVE";
    return "VAR";
}

std::string numToStr(long double x) {
    float tmp = float(x);
    std::ostringstream ss;
    ss.precision(6);
    ss << tmp;

    return ss.str();
}

std::string numToStrRaw(long double x) {
    float tmp = float(x);
    std::ostringstream ss;
    ss.precision(6);
    ss << tmp;

    return ss.str();
}

void performUpdate(Stream &updateSource, size_t updateSize) {
    if (Update.begin(updateSize)) {      
        size_t written = Update.writeStream(updateSource);
        if (written == updateSize) {
            Serial.println("Written : " + String(written) + " successfully");
        }
        else {
            Serial.println("Written only : " + String(written) + "/" + String(updateSize) + ". Retry?");
        }
        if (Update.end()) {
            Serial.println("OTA done!");
            if (Update.isFinished()) {
                Serial.println("Update successfully completed. Rebooting.");
            }
            else {
                Serial.println("Update not finished? Something went wrong!");
            }
        }
        else {
            Serial.println("Error Occurred. Error #: " + String(Update.getError()));
        }

    }
    else {
        Serial.println("Not enough space to begin OTA");
    }
}

// check given FS for valid update.bin and perform update if available
void updateFromFS(fs::FS &fs, std::string path) {
    u8g2.clearBuffer();
    u8g2.sendBuffer();
    u8g2.drawButtonUTF8(128, 32, U8G2_BTN_HCENTER|U8G2_BTN_BW1, 34,  2,  3, ("writing " + path + " to ROM...").c_str());
    u8g2.sendBuffer();

    File updateBin = fs.open(path.c_str());
    if (updateBin) {
        if(updateBin.isDirectory()){
            Serial.println(("Error, " + path + " is not a file").c_str());
            updateBin.close();
            return;
        }

        size_t updateSize = updateBin.size();

        if (updateSize > 0) {
            Serial.println("Try to start update");
            performUpdate(updateBin, updateSize);
        }
        else {
            Serial.println("Error, file is empty");
        }

        updateBin.close();
    
        // whe finished remove the binary from sd card to indicate end of the process
        //fs.remove("/update.bin");      
    }
    else {
        Serial.println("Could not load update.bin from sd root");
    }
}

void rebootEspWithReason(std::string reason) {
    Serial.println(reason.c_str());
    delay(100);
    ESP.restart();
}

