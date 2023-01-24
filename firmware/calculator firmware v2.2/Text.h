#ifndef TEXT_H
#define TEXT_H

#include "Animation.h"

class Text : public UIElement {
    public:
        Text(std::string text);
        Text(int x, int y, std::string text);
        Text(int x, int y, int width, int height, std::string text);

        void init();

        void draw();
        
        void drawHighlight();

    private:
        std::string text;
};

#endif