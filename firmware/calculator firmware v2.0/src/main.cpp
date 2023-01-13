
//#include <U8g2lib.h>
//#include <U8x8lib.h>

#include "Util.h"
#include "Node.h"
#include "Expression.h"
#include "Keyboard.h"


void init() {
    u8g2.begin();
    u8g2.setFontMode(0);
    Serial.begin(115200);
    u8g2.setFont(u8g2_font_profont10_mf);
    u8g2.setFontPosCenter();
    u8g2.drawBox(30, 40, 10, 10);
    Serial.print("hello00"); 


}

Keyboard kb;


void setup() {
    init();
    kb.init();
    u8g2.sendBuffer();
}

void loop() {
    //Serial.flush();
    u8g2.clearBuffer();
    kb.update();
    kb.printKeys();
    Serial.println("hello");
    u8g2.sendBuffer();
    delay(10);
    //u8g2.drawBox(30, 40, 10, 10);
}
