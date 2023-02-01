#ifndef MACROPAD_UI_H
#define MACROPAD_UI_H

#include "Macropad.h"
#include "Util.h"
#include "Animation.h"

class MacropadUI : public UIElement {
    public:
        MacropadUI(MacroPad* macropad);

        void activate();

        void draw();

        void update();

    private:
        MacroPad* macropad;
};

#endif