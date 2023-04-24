#ifndef LIST_SELECTOR_H
#define LIST_SELECTOR_H

#include "Animation.h"
#include "Text.h"

class ListSelector : public UIElement {
    public:
        ListSelector(std::string name, int startVal, int endVal);
        ListSelector(std::string name, int* linkValue, int startVal, int endVal);
        ListSelector(std::string name, int x, int y, int* linkValue, int startVal, int endVal);

        void incrementValue();
        void decrementValue();
        void init();
        void activate();
        void draw();
        void drawUpdated();
        void update();
        
    private:
        std::string name;
        int value;
        int startVal, endVal;
        int* linkVal;
        std::vector <int*> linkElements;
};

#endif