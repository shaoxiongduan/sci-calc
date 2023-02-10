
//#include <U8g2lib.h>
//#include <U8x8lib.h>

#include "Util.h"
#include "Node.h"
#include "Expression.h"
#include "Keyboard.h"
#include "Macropad.h"
#include "UIMain.h"




BleKeyboard bleKeyboard("SCI-CALC", "SHAP", 100);


void init() {
    u8g2.begin();
    u8g2.setFontMode(0);
    Serial.begin(115200);
    u8g2.setFont(u8g2_font_profont10_mf);
    u8g2.setFontPosCenter();
    //u8g2.drawBox(30, 40, 10, 10);
    //Serial.print("hello00"); 
    uint8_t cardType;
   Serial.begin(115200);
   //Serial.println("Welcome to the SD-Update example!");

   // You can uncomment this and build again
   // Serial.println("Update successfull");

   //first init and check SD card
   if (!SD.begin(4)) {
      rebootEspWithReason("Card Mount Failed");
   }

   cardType = SD.cardType();

   if (cardType == CARD_NONE) {
      rebootEspWithReason("No SD_MMC card attached");
   }
}





void setup() {
    init();
    rtc.setTime(00, 00, 22, 1, 2, 2023);
    kb.init();
    bleKeyboard.begin();
    currentElement -> init();
    u8g2.clearBuffer();
    //pinMode()
}

void loop() { 
    //Serial.flush();
    u8g2.clearBuffer();
    kb.update();
    //kb.printKeys();
    //macroPad.update();
    currentElement -> update();
    //Serial.println("hello");
    displayTime();
    u8g2.sendBuffer();
    animateAll();
    //delay(100);
    //u8g2.drawBox(30, 40, 10, 10);
}