#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include "Animation.h"

class ProgressBar : public UIElement {
    public:
        ProgressBar();
        ProgressBar(int x, int y, int totalLen, int curLen);

        void setLen(int curLen);
        int getTotalLen();

        void draw();

        // Needs to be public for access in Animation class
        int totalLen, curLen;
};

#endif