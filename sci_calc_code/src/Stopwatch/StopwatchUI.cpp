#include "StopwatchUI.h"


StopwatchUI::StopwatchUI(int x, int y, int width, int height, Menu* lapMenu) : UIElement(x, y, width, height) {
    this -> lapMenu = lapMenu;
}

void StopwatchUI::init() {
    this -> lapMenu -> init();
    this -> lapMenu -> activate();
}

void StopwatchUI::activate() {
    currentElement = this;
    //init();
}

void StopwatchUI::draw() {
    this -> lapMenu -> update();
    u8g2.drawLine(115, 0, 115, 64);
    if (this -> stopwatch.getIsTicking()) {
        u8g2.drawStr(120, 12, "enter: Pause");
        u8g2.drawStr(120, 24, "Del: Lap");
    }
    else {
        u8g2.drawStr(120, 12, "enter: Start");
        u8g2.drawStr(120, 24, "Del: Reset");
    }
    u8g2.drawStr(120, 48, (10, 10, "Time: " + this -> stopwatch.toTime(this -> stopwatch.getTimeElapsed())).c_str());
}

void StopwatchUI::update() {
    draw();
    stopwatch.update();
    if (kb.getRisingEdgeKey() == std::make_pair(3, 3)) {
        if (this -> stopwatch.getIsTicking() == false) {
            this -> stopwatch.start();
        }
        else {
            this -> stopwatch.pause();
        }
    }
    if (kb.getRisingEdgeKey() == std::make_pair(4, 3)) {
        if (this -> stopwatch.getIsTicking() == false) {
            this -> stopwatch.reset();
            this -> lapMenu -> clear();
        }
        else {
            int tmp = this -> stopwatch.lap();


            std::string strtmp = this -> stopwatch.toTime(tmp);
            std::string strtmp2 = this -> stopwatch.toTime(this -> stopwatch.getTimeElapsed());
            std::string strres = "lap: " + strtmp + ".";
            //this -> lapMenu -> enter();
            UIElement* ptr = new Text(strres);
            ptr -> init();
            this -> lapMenu -> insertElement(ptr, nullptr);
            this -> lapMenu -> scrollDown();

        }
    }
    if (kb.getRisingEdgeKey() == std::make_pair(0, 0)) {
        this -> lapMenu -> aniOut();
        Serial.println("goback2");
        while (!tmpAnimationUI.empty()) {
            u8g2.clearBuffer();
            currentElement -> draw();
            updateTmp();
            u8g2.sendBuffer();
            animateAll();
        }
        goBack();
    }
}