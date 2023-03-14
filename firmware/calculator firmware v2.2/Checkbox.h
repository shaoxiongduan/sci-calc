#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "Animation.h"

class Checkbox : public UIElement {
    public:
        Checkbox();
        Checkbox(bool* linkBool);
        Checkbox(int x, int y, bool* linkBool);
        void draw();
        
    private:
        bool state;
        bool* linkBool;
};

#endif