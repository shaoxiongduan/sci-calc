#ifndef FUNSTUFF_H
#define FUNSTUFF_H

#include "../Utils/Util.h"
#include "../Utils/Keyboard.h"
#include "../Animation/Animation.h"


extern Keyboard kb;


class Funstuff : public UIElement {
    public:
        Funstuff();
        Funstuff(std::string expression);
        void activate();

        void update();

        void drawDefaultSmile();

        void draw();

    private:
        std::string expression;
        bool isBlink;
        bool isVertical;
};

#endif