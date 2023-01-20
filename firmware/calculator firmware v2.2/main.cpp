
//#include <U8g2lib.h>
//#include <U8x8lib.h>

#include "Util.h"
#include "Node.h"
#include "Expression.h"
#include "Keyboard.h"
#include "Macropad.h"
#include "UIElement.h"

Keyboard kb;
BleKeyboard bleKeyboard("SCI-CALC", "SHAP", 100);

Macro layout1[5][6] = {
    {Macro({KEY_ESC}), Macro({'/'}), Macro({'*'}), Macro({'-'}), Macro({KEY_LEFT_GUI, 'a'}), Macro({'8'})},
    {Macro({'7'}), Macro({'8'}), Macro({'9'}), Macro({'+'}), Macro({KEY_LEFT_GUI, 'c'}), Macro({KEY_LEFT_GUI, 'v'})},
    {Macro({'4'}), Macro({'5'}), Macro({'6'}), Macro({'^'}), Macro({KEY_LEFT_GUI, 'x'}), Macro({KEY_LEFT_GUI, 's'})},
    {Macro({'1'}), Macro({'2'}), Macro({'3'}), Macro({KEY_RETURN}), Macro({'8'}), Macro({'8'})},
    {Macro({KEY_LAYER_SWITCH}), Macro({'0'}), Macro({'.'}), Macro({KEY_BACKSPACE}), Macro({'8'}), Macro({'8'})}
};

Macro layout2[5][6] = { 
    {Macro({KEY_ESC}), Macro({'('}), Macro({')'}), Macro({'-'}), Macro({'8'}), Macro({'8'})},
    {Macro({'7'}), Macro({KEY_UP_ARROW}), Macro({'9'}), Macro({'+'}), Macro({KEY_LEFT_GUI, 'c'}), Macro({KEY_LEFT_GUI, 'v'})},
    {Macro({KEY_LEFT_ARROW}), Macro({'5'}), Macro({KEY_RIGHT_ARROW}), Macro({KEY_LEFT_GUI, 'x'}), Macro({KEY_LEFT_GUI, 's'})},
    {Macro({'1'}), Macro({KEY_DOWN_ARROW}), Macro({'3'}), Macro({KEY_RETURN}), Macro({'8'}), Macro({'8'})},
    {Macro({KEY_LAYER_SWITCH}), Macro({'0'}), Macro({'.'}), Macro({KEY_BACKSPACE}), Macro({'8'}), Macro({'8'})}
};

MacroPad macroPad({ 
    Layout("standard", layout1),
    Layout("layout 2", layout2)
    
});


Text text1("Hello world");
Text text2("i like cats"); 
Text text3("kitcats are delicious");
Text text4("i love undy");
Text text5("pp is god");
Text text6("idk what to write now");
Text text7("idk what to write now");
Text text8("lol this is a prototype");
Text text9("sci-calc by SHAO");

Menu menu(0, 0, 200, 64, 4, {&text1, &text2, &text3, &text4, &text5, &text6, &text7, &text8, &text9});


void init() {
    u8g2.begin();
    
    u8g2.setFontMode(0);
    Serial.begin(115200);
    u8g2.setFont(u8g2_font_profont10_mf);
    u8g2.setFontPosCenter();
    //u8g2.drawBox(30, 40, 10, 10);
    //Serial.print("hello00"); 
}




void setup() {
    init();
    kb.init();
    bleKeyboard.begin();

    u8g2.sendBuffer();
}

void loop() { 
    //Serial.flush();
    u8g2.clearBuffer();
    kb.update();
    //kb.printKeys();
    //macroPad.update();

    menu.update();
    //Serial.println("hello");
    u8g2.sendBuffer();
    //delay(100);
    //u8g2.drawBox(30, 40, 10, 10);
}