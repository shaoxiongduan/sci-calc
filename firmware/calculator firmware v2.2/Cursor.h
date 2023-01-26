#ifndef CURSOR_H
#define CURSOR_H

#include "Animation.h"

class Cursor : public UIElement {
    public:
        Cursor();

        Cursor(UIElement* target);

        void changeTarget(UIElement* target);

        void changeTarget(UIElement* target, int time);

        void changeTarget(int x, int y, int width, int height, int time);


        void draw();

    private:
        UIElement* target;
};

#endif