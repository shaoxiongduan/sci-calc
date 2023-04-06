#include "Sidebar.h"

int curtime = 0;
std::string batterylevel;

void drawSidebar() {
    u8g2.drawRFrame(213, 0, 43, 64, 2);
    if (millis() - curtime > 500) {
        batterylevel = numToStr(analogRead(36) / 4095.0 * 2 * 3.3).substr(0, 3);
        curtime = millis();
    }
    u8g2.drawStr(215, 12, ("bat:" + batterylevel + "V").c_str());
}