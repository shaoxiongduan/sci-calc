#ifndef UIELEMENT_H
#define UIELEMENT_H

#include "Util.h"
#include "Keyboard.h"

extern Keyboard kb;

class UIElement {
    public:

        UIElement();

        UIElement(int x, int y);

        UIElement(int x, int y, int width, int height);

        UIElement(int x, int y, int width, int height, std::vector <UIElement*> subElements);

        void insert(UIElement* UIElement);

        UIElement* getNode(int id);
        
        int getSize();
        
        int getX();

        int getY();

        void setX(int x);

        void setY(int y);

        virtual void draw();

        virtual void drawHighlight();

        virtual bool drawCondition();

        virtual bool moveCondition();

        virtual void drawRecursive();

    protected:
        int x, y; // relative coordinates
        int width, height;
        std::vector <UIElement*> subElements;
};

/********************
TEXT
********************/

class Text : public UIElement {
    public:
        Text(std::string text);
        Text(int x, int y, std::string text);
        Text(int x, int y, int width, int height, std::string text);

        void draw();
        
        void drawHighlight();

    private:
        std::string text;
};

/********************
MENU
********************/

class Menu : public UIElement {
    public:
        
        Menu(int x, int y, int width, int height, int menuSize, std::vector <UIElement*> subElements);
        
        bool moveCursorUp();
        bool moveCursorDown();

        bool moveMenuUp();
        bool moveMenuDown();

        int getMenuPos();

        void scrollUp();

        void scrollDown();

        void drawScrollBar();

        void draw();


        void update();

    private:
        int cursorPos, menuPos;
        int menuSize;

};
#endif