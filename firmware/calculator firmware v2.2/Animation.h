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
        
        Animation(int* targetVal, AnimationType aniType, int endVal, int totalTime);

        void init();

        UIElement* getTargetElement();
        int* getTargetVal();

        int getCurDuration();

        int getTotDuration();

        void updateTime();
        
        bool getIsStarted();

        bool getIsFinished();


        void animateLinear();

        void animateIndent();

        void animateBounce();

        void animate();

    protected:
        bool type; // 0 is animation for a whole object, 1 is animation for a single variable
        int* targetVal;
        int startVal, endVal;
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