#ifndef UIMAIN_H
#define UIMAIN_H

#include "./Utils/Util.h"
#include "./UIElements/Text.h"
#include "./UIElements/Menu.h"
#include "./UIElements/Cursor.h"
#include "./UIElements/Box.h"
#include "./UIElements/InputBox.h"
#include "./Calculator/ExpressionBlock.h"
#include "./Calculator/Calculator.h"
#include "./Calculator/CalculatorRPN.h"
#include "./Utils/Macropad.h"
#include "./Macropad/MacropadUI.h"
#include "./Utils/Keyboard.h"
#include "ESP32Time.h"
#include "./UIElements/BinLink.h"
#include "./Stopwatch/StopwatchUI.h"
#include "./UIElements/ChineseText.h"
#include "./UIElements/Checkbox.h"
#include "./UIElements/Funstuff.h"
#include "./UIElements/Slider.h"


extern std::string clipboard;
extern Keyboard kb;
extern ESP32Time rtc;


extern Macro layout1[5][6];
extern Macro layout2[5][6];
extern Macro layout3[5][6];
extern Macro layout4[5][6];
extern MacroPad macroPad;
extern MacroPad calcLayout;
extern MacropadUI macropadUI;

extern Menu menu;

void displayTime();


#endif