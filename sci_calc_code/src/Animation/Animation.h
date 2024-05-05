#ifndef ANIMATION_H
#define ANIMATION_H

#include "../Utils/Util.h"
#include "../UIElements/UIElement.h"

class Animation {
    public:

        Animation(UIElement* targetUI, AnimationType aniType, int endX, int endY, int totalTime);
        Animation(UIElement* targetUI, AnimationType aniType, int endX, int endY, int endWidth, int endHeight, int totalTime);
        Animation(int* targetVal, AnimationType aniType, int endVal, int totalTime);

        Animation(UIElement* targetUI, AnimationType aniType, int endX, int endY, int totalTime, int delayTime);
        Animation(UIElement* targetUI, AnimationType aniType, int endX, int endY, int endWidth, int endHeight, int totalTime, int delayTime);
        Animation(int* targetVal, AnimationType aniType, int endVal, int totalTime, int delayTime);


        void init();
        void initAni();
        UIElement* getTargetElement();
        int* getTargetVal();
        int getCurDuration();
        int getTotDuration();
        void updateTime();
        bool getIsStarted();
        bool getIsAnimating();
        bool checkTime();
        bool getIsFinished();
        void animateLinear();
        void animateIndent();
        void animateIndentInv();
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
        int createTime;
        int totalTime;
        int delayTime;
        bool isStarted, isFinished, isAnimating;
};

extern std::map <UIElement*, Animation*> animationsUI;
extern std::map <int*, Animation*> animationsInt;
extern std::list <UIElement*> tmpAnimationUI;


void insertAnimation(Animation* animation);
void insertTmpAnimationPointer(int* tmpInt);
void insertTmpAnimationPointer(UIElement* tmpUI);
void animateAll();
void updateTmp();

#endif