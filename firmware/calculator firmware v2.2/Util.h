#ifndef UTIL_H
#define UTIL_H

#include <Arduino.h>
#include <U8g2lib.h>
#include <U8x8lib.h>
#include <BleKeyboard.h>
#include <string>
#include <cmath>
#include <vector>
#include <queue>
#include <stack>
#include <sstream>
#include <list>
#include <map>

#include <Update.h>
#include <FS.h>
#include <SD.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#define SPI_CLK 18
#define SPI_DATA 23
#define SPI_CS 5
#define SPI_DC 16
#define SPI_RESET 17

extern U8G2_SSD1322_NHD_256X64_F_4W_HW_SPI u8g2;

const int REFRESH_DURATION = 10; // in milliseconds
const float DELTA_TIME = 100; // in milliseconds
extern bool sample;
const int MAXOP = 25;
const int MAXANI = 100;
const long double EPSILON = 1e-8;
const int WIDTH = 256;
const int HEIGHT = 64;
const int MAXNODES = 1000;

const uint16_t KEY_LAYER_SWITCH = 0xFC;
const uint16_t KEY_EXP = 0xFD;
const uint16_t KEY_LN = 0xFE;
const uint16_t KEY_SIN = 0xFF;
const uint16_t KEY_COS = 0x100;
const uint16_t KEY_TAN = 0x101;
const uint16_t KEY_SEC = 0x102;
const uint16_t KEY_CSC = 0x103;
const uint16_t KEY_COT = 0x104;
const uint16_t KEY_ASIN = 0x105;
const uint16_t KEY_ACOS = 0x106;
const uint16_t KEY_ATAN = 0x107;
const uint16_t KEY_SQRT = 0x108;
const uint16_t KEY_MODE_SWITCH = 0x109;
const uint16_t KEY_AUTOCLICK = 0x10A;
const byte ROWCNT = 5;
const byte COLCNT = 6;
extern byte ROW_MISO[ROWCNT];
extern byte COL_MOSI[COLCNT];



extern char keys[ROWCNT][COLCNT];
//extern Keypad keypad;

enum KeyStatus {
    NOT_PRESSED, PRESSED, RISING_EDGE, FALLING_EDGE
};

enum Element {
    MENU, TEXT
};

enum AnimationType {
    LINEAR, INDENT, INDENTINV, BOUNCE
};

extern AnimationType menuScroll;
extern AnimationType menuEntry;
extern AnimationType cursorScroll;
extern AnimationType sliderMove;

//void printKeys();

extern BleKeyboard bleKeyboard;

extern int lastNode;

enum Token {
    ADD, SUB, MUL, DIV, POW, SQRT, LN, EXP, SIN, COS, TAN, SEC, CSC, COT, ASIN, ACOS, ATAN, LPARA, RPARA, EQUALS, NEGATIVE, NUM, VAR
};

//settings
extern bool cursorMode;

extern bool angleMode;
extern std::string tokenStr[MAXOP];

std::string getKeyString(uint16_t x);
bool strIsOperator(std::string str);
bool cmpLongDouble(long double a, long double b);
int getPrecedenceToken(Token token);
Token convertToEnum(std::string s);
std::string convertToString(Token t);
std::string numToStr(long double x);
std::string numToStrRaw(long double x);
void performUpdate(Stream &updateSource, size_t updateSize);
void updateFromFS(fs::FS &fs, std::string);
void rebootEspWithReason(std::string reason);
bool checkSyntax(std::string str);

void initFromFile();
#endif