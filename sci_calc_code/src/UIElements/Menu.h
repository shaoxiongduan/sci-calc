#ifndef MENU_H
#define MENU_H

#include "../Animation/Animation.h"
#include "Cursor.h"
#include "Box.h"
#include "Sidebar.h"

/*
The Menu class is a specialized user interface element that extends the UIElement class.
The Menu class has two core components, the SubElements, which function as the displaying part for the subElements in the menu, and LinkElements, which are pointers linking to the element to be activated when activated (Duh!).
*/

class Menu : public UIElement {
    public:
        Menu();

        Menu(int restX, int restY, int activeX, int activeY, int width, int height, int menuSize);
        Menu(int restX, int restY, int activeX, int activeY, int width, int height, int menuSize, std::vector <UIElement*> subElements, std::vector <UIElement*> linkElements);

        void init();
        void activate();
        void deactivate();

        void aniIn();
        void aniOut();

        void insertElement(UIElement* targetElement, UIElement* linkElement);

        bool moveCursorUp();
        bool moveCursorDown();

        bool moveMenuUp();
        bool moveMenuDown();

        int getMenuPos();

        void scrollUp();

        void scrollDown();

        void drawScrollBar();

        void clear(); 

        void enter();

        void draw();


        //void showMenu(uint8_t dir); // 0 up 1 right 2 down 3 left


        void update();

    private:
        int cursorPos, menuPos;
        int restX, restY, activeX, activeY;
        int menuSize;
        Cursor cursor;
        Box scrollBar;
        std::vector <UIElement*> linkElements;
        
};

#endif