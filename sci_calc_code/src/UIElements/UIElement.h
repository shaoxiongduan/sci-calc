#ifndef UIELEMENT_H
#define UIELEMENT_H

#include "../Utils/Util.h"
#include "../Utils/Keyboard.h"
#include "../Utils/Macropad.h"

extern Keyboard kb;
extern MacroPad calcLayout;
extern std::string clipboard;

class UIElement {
    public:

        UIElement();
        UIElement(int x, int y);
        UIElement(int x, int y, int width, int height);
        UIElement(int x, int y, int width, int height, std::vector <UIElement*> subElements);
        UIElement(int x, int y, bool drawParent);
        UIElement(int x, int y, int width, int height, bool drawParent);
        UIElement(int x, int y, int width, int height, std::vector <UIElement*> subElements, bool drawParents);

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
        bool getDrawParent();
        bool isTransition();
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
        virtual void goBack();
        virtual void update();

    protected:
        int x, y, targetX, targetY;
        int width, height, targetWidth, targetHeight;
        std::vector <UIElement*> subElements;
        UIElement* parentElement;
        bool drawParent, doTransition;
};

extern UIElement* currentElement;

#endif