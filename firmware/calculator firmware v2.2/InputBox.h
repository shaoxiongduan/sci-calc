#ifndef INPUT_BOX_H
#define INPUT_BOX_H

#include "Animation.h"
#include "Cursor.h"
#include "Box.h"

class InputBox : public UIElement {
    public:
        
        InputBox(int x, int y, int width, int height, int maxChar);
        
        void init();
        void activate();
        void deactivate();

        void insertStr(std::string insertStr);
        void deleteStr();

        bool moveCursorLeft();
        bool moveCursorRight();

        bool moveStrLeft();
        bool moveStrRight();

        int getStrPos();

        void scrollLeft();

        void scrollRight();
        std::string enter();

        void draw();


        void update();

    private:
        int cursorPos, strPos, maxChar;
        Cursor cursor;
        std::string str;
        
};


#endif