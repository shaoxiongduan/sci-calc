#include "Util.h"

int lastNode = -1;
std::string tokenStr[MAXOP] = {"+", "-", "*", "/", "^", "sqrt", "ln", "exp", "sin", "cos", "tan", "sec", "csc", "cot", "asin", "acos", "atan", "(", ")", "=", "-", "NUM", "VAR"};
U8G2_SSD1322_NHD_256X64_F_4W_HW_SPI u8g2(U8G2_R2, SPI_CS, SPI_DC);


byte ROW_MISO[ROWCNT] = {32, 35, 34, 39, 36};
byte COL_MOSI[COLCNT] = {25, 26, 27, 14, 12, 13};

char keys[ROWCNT][COLCNT] = {
    {'i', '/', '*', '-', 'a', 'b'},
    {'7', '8', '9', '+', 'c', 'd'},
    {'4', '5', '6', '^', 'e', 'f'},
    {'1', '2', '3', 'e', 'g', 'h'},
    {'0', '.', 'f', 'd', 'i', 'j'}
};

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