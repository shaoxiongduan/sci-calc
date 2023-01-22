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

#endif