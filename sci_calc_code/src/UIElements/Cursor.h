#ifndef CURSOR_H
#define CURSOR_H

#include "../Animation/Animation.h"

class Cursor : public UIElement {
    public:
        Cursor();

        Cursor(bool mode);

        Cursor(UIElement* target, bool mode);

        void setMode(bool mode);

        void changeTarget(UIElement* target);

        void changeTarget(UIElement* target, int time);
        void changeTarget(UIElement* target, int time, int delayTime);
        void changeTarget(int x, int y, int width, int height, int time);


        void draw();

    private:
        UIElement* target;
        bool mode; // 0: box, 1: line
};

#endif