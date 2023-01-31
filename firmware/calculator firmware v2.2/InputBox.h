#ifndef INPUT_BOX_H
#define INPUT_BOX_H

#include "Animation.h"
#include "Cursor.h"
#include "Box.h"

class InputBox : public UIElement {
    public:
        
        InputBox();
        

        InputBox(int x, int y, int width, int height, int maxChar);
        
        void init();
        void activate();
        void deactivate();

        std::string getStr();
        void setStr(std::string str);
        void clearStr();
        
        void insertStr(std::string insertStr);
        void deleteStr();

        int moveCursorLeft(int x);
        int moveCursorRight(int x);

        void moveStrLeft(int x);
        void moveStrRight(int x);

        int getStrPos();

        void scrollLeft(int x);

        void scrollRight(int x);
        std::string enter();

        void draw();


        void update();

    private:
        int cursorPos, strPos, maxChar;
        Cursor cursor;
        std::string str;
        
};


#endif