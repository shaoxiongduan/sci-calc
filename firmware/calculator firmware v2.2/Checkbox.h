#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "Animation.h"


class Checkbox : public UIElement {
    public:
        Checkbox(std::string name);
        Checkbox(std::string name, bool* linkBool);
        Checkbox(std::string name, int x, int y, bool* linkBool);

        void changeState();
        void init();
        void activate();
        void draw();
        void update();
        
        int checkboxAni;

    private:
        std::string name;
        bool state;
        bool* linkBool;
};

#endif