
//#include <U8g2lib.h>
//#include <U8x8lib.h>

#include "Util.h"
#include "Node.h"
#include "Expression.h"
#include "Keyboard.h"
#include "Macropad.h"

Keyboard kb;
BleKeyboard bleKeyboard("SCI-CALC", "SHAP", 100);

Macro layout1[5][6] = {
        {Macro({KEY_ESC}), Macro({'/'}), Macro({'*'}), Macro({'-'}), Macro({'8'}), Macro({'8'})},
        {Macro({'7'}), Macro({'8'}), Macro({'9'}), Macro({'+'}), Macro({'8'}), Macro({'8'})},
        {Macro({'4'}), Macro({'5'}), Macro({'6'}), Macro({'^'}), Macro({'8'}), Macro({'8'})},
        {Macro({'1'}), Macro({'2'}), Macro({'3'}), Macro({KEY_RETURN}), Macro({'8'}), Macro({'8'})},
        {Macro({'0'}), Macro({'.'}), Macro({'8'}), Macro({KEY_BACKSPACE}), Macro({'8'}), Macro({'8'})}
};

MacroPad macroPad({ 
    Layout("standard", layout1)
});




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
    kb.printKeys();
    macroPad.update();
    //Serial.println("hello");
    u8g2.sendBuffer();
    //delay(100);
    //u8g2.drawBox(30, 40, 10, 10);
}
