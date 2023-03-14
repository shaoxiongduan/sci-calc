#ifndef STOPWATCH_UI_H
#define STOPWATCH_UI_H

#include "Animation.h"
#include "Menu.h"
#include "Text.h"
#include "Stopwatch.h"


class StopwatchUI : public UIElement {
    public:
        StopwatchUI(int x, int y, int width, int height, Menu* lapMenu);
        
        void init();
        void activate();

        void draw();
        void update();


    private:
        Stopwatch stopwatch;
        Menu* lapMenu;
};

#endif