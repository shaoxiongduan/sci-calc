#ifndef ANIMATION_H
#define ANIMATION_H

#include "Util.h"
#include "UIElement.h"

class Animation {
    public:
        //Animation(UIElement* targetUI, AnimationType aniType, int startX, int startY, int endX, int endY, int totalTime);
        
        Animation(UIElement* targetUI, AnimationType aniType, int endX, int endY, int totalTime);

        //Animation(UIElement* targetUI, AnimationType aniType, int startX, int startY, int endX, int endY, int startWidth, int startHeight, int endWidth, int endHeight, int totalTime);
        
        Animation(UIElement* targetUI, AnimationType aniType, int endX, int endY, int endWidth, int endHeight, int totalTime);
        

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
        int startWidth, startHeight, endWidth, endHeight;
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