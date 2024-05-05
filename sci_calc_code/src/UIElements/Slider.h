#ifndef SLIDER_H
#define SLIDER_H

#include "../Animation/Animation.h"
#include "ProgressBar.h"


class Slider : public UIElement {
    public:
        Slider(std::string name, int startVal, int endVal);
        Slider(std::string name, int* linkValue, int startVal, int endVal);
        Slider(std::string name, int x, int y, int* linkValue, int startVal, int endVal);

        void incrementValue();
        void decrementValue();
        void incrementStep();
        void decrementStep();
        void init();
        void activate();
        void draw();
        void drawUpdated();
        void update();
        
    private:
        std::string name;
        int value;
        int startVal, endVal;
        int stepVal;
        int* linkVal;
        ProgressBar progressBar;
};

#endif