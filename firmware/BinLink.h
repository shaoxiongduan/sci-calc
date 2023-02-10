#ifndef BIN_LINK_H
#define BIN_LINK_H

#include "Util.h"
#include "Animation.h"

class BinLink : public UIElement {
    public: 
        BinLink(std::string path);

        void activate();

        void draw();

        void update();

    private:
        std::string path;
}; 

#endif