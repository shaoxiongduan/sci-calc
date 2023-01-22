#ifndef MENU_H
#define MENU_H

#include "Animation.h"

class Menu : public UIElement {
    public:
        
        Menu(int x, int y, int width, int height, int menuSize, std::vector <UIElement*> subElements);
        
        void initMenu();

        bool moveCursorUp();
        bool moveCursorDown();

        bool moveMenuUp();
        bool moveMenuDown();

        int getMenuPos();

        void scrollUp();

        void scrollDown();

        void drawScrollBar();

        void draw();

        void showMenu(uint8_t dir); // 0 up 1 right 2 down 3 left


        void update();

    private:
        int cursorPos, menuPos;
        int menuSize;

};

#endif