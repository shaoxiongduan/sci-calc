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
const long double EPSILON = 1e-8;
const int MAXNODES = 1000;
const uint8_t KEY_LAYER_SWITCH = 0xFC;

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
//void printKeys();

extern BleKeyboard bleKeyboard;

extern int lastNode;

enum Token {
    ADD, SUB, MUL, DIV, POW, SQRT, LN, EXP, SIN, COS, TAN, SEC, CSC, COT, ASIN, ACOS, ATAN, LPARA, RPARA, EQUALS, NEGATIVE, NUM, VAR
};

extern std::string tokenStr[MAXOP];

std::string getKeyString(uint8_t x);
bool strIsOperator(std::string str);
bool cmpLongDouble(long double a, long double b);
int getPrecedenceToken(Token token);
Token convertToEnum(std::string s);
std::string convertToString(Token t);

#endif