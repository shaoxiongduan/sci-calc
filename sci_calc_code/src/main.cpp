
//#include <U8g2lib.h>
//#include <U8x8lib.h>

#include "UIMain.h"




BleKeyboard bleKeyboard("SCI-CALC", "SHAP", 100);



void init() {
    u8g2.begin();
    u8g2.setFontMode(0);
    Serial.begin(115200);
    u8g2.setFont(u8g2_font_profont10_mf);
    u8g2.setFontPosCenter();
    u8g2.setFontMode(1);
    u8g2.enableUTF8Print();

    Serial.begin(115200);
   //first init and check SD card
    if (!SD.begin(4)) {
        rebootEspWithReason("Card Mount Failed");
    }

    uint8_t cardType;
    cardType = SD.cardType();
    if (cardType == CARD_NONE) {
        rebootEspWithReason("No SD_MMC card attached");
    }
    pinMode(36, INPUT);
    initFromFile();
}





void setup() {
    init();
    kb.init();
    bleKeyboard.begin();
    currentElement -> init();
    u8g2.clearBuffer();
    currentElement -> activate();
}

void loop() { 
    animateAll();
    u8g2.clearBuffer();
    kb.update();
    drawSidebar();
    currentElement -> update();
    updateTmp();
    u8g2.sendBuffer();
}