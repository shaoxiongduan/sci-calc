#ifndef TEXT_H
#define TEXT_H

#include "../Animation/Animation.h"

class Text : public UIElement {
    public:
        Text();
        Text(std::string text);
        Text(int x, int y, std::string text);
        Text(int x, int y, int width, int height, std::string text);
        
        void setText(std::string text);
        std::string getStr();

        void init();
        void draw();
        void update();

    private:
        std::string text;
};

#endif