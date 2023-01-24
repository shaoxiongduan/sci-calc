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

        virtual void init();

        virtual void activate();
        virtual void deactivate();

        void insert(UIElement* UIElement);

        UIElement* getNode(int id);
        
        int getSize();
        
        int getX();

        int getY();

        int getTargetX();

        int getTargetY();

        int getWidth();

        int getHeight();

        int getTargetWidth();

        int getTargetHeight();

        void setX(int x);

        void setY(int y);

        void setTargetX(int x);

        void setTargetY(int y);
       
        void setWidth(int width);

        void setHeight(int height);

        void setTargetWidth(int width);

        void setTargetHeight(int height);
       
        void setParent(UIElement* parentElement);

        virtual void draw();

        virtual void drawHighlight();

        virtual bool drawCondition();

        virtual bool moveCondition();

        virtual void drawRecursive();

        virtual void goBack();

        virtual void update();

    protected:
        int x, y, targetX, targetY;
        int width, height, targetWidth, targetHeight;
        std::vector <UIElement*> subElements;
        UIElement* parentElement;
};

extern UIElement* currentElement;

#endif