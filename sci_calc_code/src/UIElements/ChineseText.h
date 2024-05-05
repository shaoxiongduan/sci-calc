#ifndef CHINESE_TEXT_H
#define CHINESE_TEXT_H

#include "../Animation/Animation.h"


class ChineseText : public UIElement {
    public:
        ChineseText(int type);
        
        void setType(int type);

        void init();
        void activate();
        void draw();
        void update();

    private:
        int type;
        int pos;
};

#endif