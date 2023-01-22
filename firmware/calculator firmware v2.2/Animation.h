#ifndef ANIMATION_H
#define ANIMATION_H

#include "Util.h"
#include "UIElement.h"

class Animation {
    public:
        Animation(UIElement* targetUI, AnimationType aniType, int startX, int startY, int endX, int endY, int totalTime);
        
        Animation(UIElement* targetUI, AnimationType aniType, int endX, int endY, int totalTime);

        void init();

        int getCurDuration();

        int getTotDuration();

        void updateTime();
        
        bool getIsStarted();

        bool getIsFinished();

        void animateSmooth();

        void animateIndent();

        void animate();

    protected:
        UIElement* targetUI;
        int startX, startY, endX, endY;
        AnimationType aniType;
        int prevTime;
        int startTime;
        int totalTime;
        bool isStarted, isFinished;
};

extern std::list <Animation*> animations;

void insertAnimation(Animation* animation);
void animateAll();

#endif