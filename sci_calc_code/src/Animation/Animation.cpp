#include "Animation.h"


/*
ANIMATION ENGINE:
The animation engine handles every silky smooth transition you see on screen.
When adding an animation to a UIElement, it appends it into the animation queue.
When finished animating it will pop that animation from the queue.

The animation engine supports different types of animations with different easing curves.
Three types are available for quick use: Linear (Linear), Indent (Think of your mouse scrollwheel), and Bounce (BOING!)

More animation styles can be easily added by specifying the easing function (more information of these functions can be found at easings.net).
*/

/*
Constructs a animation object
```TargetUI: UIElement*```: pointer to the targeted UIElement object to animate.
```aniType: bool```: animation type (LINEAR, INDENT, or BOUNCE)
```endX, endY: int```: the ending position of the UIElement (in pixels)
```totalTime```: the total duration of the animation (in milliseconds)
*/
Animation::Animation(UIElement* targetUI, AnimationType aniType, int endX, int endY, int totalTime) {
    this -> type = false;
    this -> targetUI = targetUI;
    this -> aniType = aniType; 
    this -> startX = targetUI -> getX();
    this -> startY = targetUI -> getY();
    this -> endX = endX;
    this -> endY = endY;
    this -> targetUI -> setTargetX(endX);
    this -> targetUI -> setTargetY(endY);
    this -> startWidth = targetUI -> getWidth();
    this -> startHeight = targetUI -> getHeight();
    this -> endWidth = targetUI -> getWidth();
    this -> endHeight = targetUI -> getHeight();
    this -> totalTime = totalTime;
    this -> isFinished = false;
    this -> isStarted = false;
    this -> isAnimating = false;
    this -> delayTime = 0;
}

/*
Constructs a animation object
```TargetUI: UIElement*```: pointer to the targeted UIElement object to animate.
```aniType: bool```: animation type (LINEAR, INDENT, or BOUNCE)
```endX, endY, endWidth, endHeight: int```: the ending position and dimensions of the UIElement (in pixels)
```totalTime```: the total duration of the animation (in milliseconds)
*/
Animation::Animation(UIElement* targetUI, AnimationType aniType, int endX, int endY, int endWidth, int endHeight, int totalTime) {
    this -> type = false;
    this -> targetUI = targetUI;
    this -> aniType = aniType;
    this -> startX = targetUI -> getX();
    this -> startY = targetUI -> getY();
    this -> endX = endX;
    this -> endY = endY;
    this -> startWidth = targetUI -> getWidth();
    this -> startHeight = targetUI -> getHeight();
    this -> targetUI -> setTargetX(endX);
    this -> targetUI -> setTargetY(endY);
    this -> endWidth = endWidth;
    this -> endHeight = endHeight;
    this -> targetUI -> setTargetWidth(endWidth);
    this -> targetUI -> setTargetHeight(endHeight);
    this -> totalTime = totalTime;
    this -> isFinished = false;
    this -> isStarted = false;
    this -> isAnimating = false;
    this -> delayTime = 0;
}

/*
Constructs a animation object, used to animate individual values
```TargetVal: int*```: pointer to the targeted value to animate.
```aniType: bool```: animation type (LINEAR, INDENT, or BOUNCE)
```endVal: int```: the ending value
```totalTime```: the total duration of the animation (in milliseconds)
*/
Animation::Animation(int* targetVal, AnimationType aniType, int endVal, int totalTime) {
    this -> type = true;
    this -> targetVal = targetVal;
    this -> aniType = aniType;
    this -> startVal = *(targetVal);
    this -> endVal = endVal;
    this -> totalTime = totalTime;
    this -> isFinished = false;
    this -> isStarted = false;
    this -> isAnimating = false;
    this -> delayTime = 0;
}

/*
Constructs a animation object
```TargetUI: UIElement*```: pointer to the targeted UIElement object to animate.
```aniType: bool```: animation type (LINEAR, INDENT, or BOUNCE)
```endX, endY: int```: the ending position of the UIElement (in pixels)
```totalTime: int```: the total duration of the animation (in milliseconds)
```delayTime: int```: the delay duration of the animation before it starts (in milliseconds)
*/
Animation::Animation(UIElement* targetUI, AnimationType aniType, int endX, int endY, int totalTime, int delayTime) {
    this -> type = false;
    this -> targetUI = targetUI;
    this -> aniType = aniType;
    this -> startX = targetUI -> getX();
    this -> startY = targetUI -> getY();
    this -> endX = endX;
    this -> endY = endY;
    this -> targetUI -> setTargetX(endX);
    this -> targetUI -> setTargetY(endY);
    this -> startWidth = targetUI -> getWidth();
    this -> startHeight = targetUI -> getHeight();
    this -> endWidth = targetUI -> getWidth();
    this -> endHeight = targetUI -> getHeight();
    this -> totalTime = totalTime;
    this -> isFinished = false;
    this -> isStarted = false;
    this -> isAnimating = false;
    this -> delayTime = delayTime;
}

/*
Constructs a animation object
```TargetUI: UIElement*```: pointer to the targeted UIElement object to animate.
```aniType: bool```: animation type (LINEAR, INDENT, or BOUNCE)
```endX, endY, endWidth, endHeight: int```: the ending position and dimensions of the UIElement (in pixels)
```totalTime: int```: the total duration of the animation (in milliseconds)
```delayTime: int```: the delay duration of the animation before it starts (in milliseconds)
*/
Animation::Animation(UIElement* targetUI, AnimationType aniType, int endX, int endY, int endWidth, int endHeight, int totalTime, int delayTime) {
    this -> type = false;
    this -> targetUI = targetUI;
    this -> aniType = aniType;
    this -> startX = targetUI -> getX();
    this -> startY = targetUI -> getY();
    this -> endX = endX;
    this -> endY = endY;
    this -> startWidth = targetUI -> getWidth();
    this -> startHeight = targetUI -> getHeight();
    this -> targetUI -> setTargetX(endX);
    this -> targetUI -> setTargetY(endY);
    this -> endWidth = endWidth;
    this -> endHeight = endHeight;
    this -> targetUI -> setTargetWidth(endWidth);
    this -> targetUI -> setTargetHeight(endHeight);
    this -> totalTime = totalTime;
    this -> isFinished = false;
    this -> isStarted = false;
    this -> isAnimating = false;
    this -> delayTime = delayTime;
}

/*
Constructs a animation object, used to animate individual values
```TargetVal: int*```: pointer to the targeted value to animate.
```aniType: bool```: animation type (LINEAR, INDENT, or BOUNCE)
```endVal: int```: the ending value
```totalTime: int```: the total duration of the animation (in milliseconds)
```delayTime: int```: the delay duration of the animation before the animation starts (in milliseconds)
*/
Animation::Animation(int* targetVal, AnimationType aniType, int endVal, int totalTime, int delayTime) {
    this -> type = true;
    this -> targetVal = targetVal;
    this -> aniType = aniType;
    this -> startVal = *(targetVal);
    this -> endVal = endVal;
    this -> totalTime = totalTime;
    this -> isFinished = false;
    this -> isStarted = false;
    this -> isAnimating = false;
    this -> delayTime = delayTime;
}

// Initializes the animation
void Animation::init() {
    this -> createTime = millis();
    this -> isStarted = true;
}

// Checks whether if the animation is supposed to begin
bool Animation::checkTime() {
    return (millis() - this -> createTime >= this -> delayTime);
}

// Starts the animation
void Animation::initAni() {
    this -> prevTime = millis();
    this -> startTime = millis();
    this -> isAnimating = true;
}

// Gets the targeted UIElement
UIElement* Animation::getTargetElement() {
    return this -> targetUI;
}

// Gets the targeted value
int* Animation::getTargetVal() {
    return this -> targetVal;
}

// Gets the current elapsed time
int Animation::getCurDuration() {
    int curTime = millis();
    return curTime - this -> prevTime;
}

// Gets the total Duration of the animation
int Animation::getTotDuration() {
    return this -> totalTime;
}


bool Animation::getIsStarted() {
    return this -> isStarted;
}

bool Animation::getIsFinished() {
    return this -> isFinished;
}

bool Animation::getIsAnimating() {
    return this -> isAnimating;
}

void Animation::updateTime() {
    this -> prevTime = millis();
}

void Animation::animateLinear() {
    if (this -> type == 0) {
        if (getCurDuration() > 10 && !this -> isFinished) {
            int curX = this -> targetUI -> getX();
            int curY = this -> targetUI -> getY();

            float tmp = float(int(millis()) - this -> startTime) / float(totalTime);
            float easingVal = tmp;

            int nxtX = (this -> startX + int(easingVal * (this -> endX - this -> startX)));
            int nxtY = (this -> startY + int(easingVal * (this -> endY - this -> startY)));
            int nxtWidth = (this -> startWidth + int(easingVal * (this -> endWidth - this -> startWidth)));
            int nxtHeight = (this -> startHeight + int(easingVal * (this -> endHeight - this -> startHeight)));
            
            this -> targetUI -> setX(nxtX);
            this -> targetUI -> setY(nxtY);
            this -> targetUI -> setWidth(nxtWidth);
            this -> targetUI -> setHeight(nxtHeight);
            
            updateTime();
        }
        if (millis() - this -> startTime >= totalTime) {
            this -> targetUI -> setX(this -> endX);
            this -> targetUI -> setY(this -> endY);
            this -> targetUI -> setWidth(endWidth);
            this -> targetUI -> setHeight(endHeight);
            this -> isFinished = true;
        }
    }
    else if (this -> type == 1) {
        if (getCurDuration() > 10 && !this -> isFinished) {
            int curVal = *(this -> targetVal);

            float tmp = float(int(millis()) - this -> startTime) / float(totalTime);
            float easingVal = tmp;

            int nxtVal = (this -> startVal + int(easingVal * (this -> endVal - this -> startVal)));
            *(this -> targetVal) = nxtVal;
            Serial.println(*(this -> targetVal));
            updateTime();
        }
        if (millis() - this -> startTime >= totalTime) {
            *(this -> targetVal) = this -> endVal;
            this -> isFinished = true;
        }
    }
}

void Animation::animateIndent() {
if (this -> type == 0) {
        if (getCurDuration() > 10 && !this -> isFinished) {
            int curX = this -> targetUI -> getX();
            int curY = this -> targetUI -> getY();

            float tmp = float(int(millis()) - this -> startTime) / float(totalTime);
            
            float easingVal = 1 - pow(2, -10 * tmp);

            int nxtX = (this -> startX + int(easingVal * (this -> endX - this -> startX)));
            int nxtY = (this -> startY + int(easingVal * (this -> endY - this -> startY)));
            int nxtWidth = (this -> startWidth + int(easingVal * (this -> endWidth - this -> startWidth)));
            int nxtHeight = (this -> startHeight + int(easingVal * (this -> endHeight - this -> startHeight)));
            
            this -> targetUI -> setX(nxtX);
            this -> targetUI -> setY(nxtY);
            this -> targetUI -> setWidth(nxtWidth);
            this -> targetUI -> setHeight(nxtHeight);
            
            updateTime();
        }
        if (millis() - this -> startTime >= totalTime) {
            this -> targetUI -> setX(this -> endX);
            this -> targetUI -> setY(this -> endY);
            this -> targetUI -> setWidth(endWidth);
            this -> targetUI -> setHeight(endHeight);
            this -> isFinished = true;
        }
    }
    else if (this -> type == 1) {
        if (getCurDuration() > 10 && !this -> isFinished) {
            int curVal = *(this -> targetVal);

            float tmp = float(int(millis()) - this -> startTime) / float(totalTime);
            float easingVal = 1 - pow(2, -10 * tmp);
            
            int nxtVal = (this -> startVal + int(easingVal * (this -> endVal - this -> startVal)));
            *(this -> targetVal) = nxtVal;
            updateTime();
        }
        if (millis() - this -> startTime >= totalTime) {
            *(this -> targetVal) = this -> endVal;
            this -> isFinished = true;
        }
    }
}

void Animation::animateIndentInv() {
if (this -> type == 0) {
        if (getCurDuration() > 10 && !this -> isFinished) {
            int curX = this -> targetUI -> getX();
            int curY = this -> targetUI -> getY();

            float tmp = float(int(millis()) - this -> startTime) / float(totalTime);
            
            float easingVal = pow(2, 10 * tmp - 10);

            int nxtX = (this -> startX + int(easingVal * (this -> endX - this -> startX)));
            int nxtY = (this -> startY + int(easingVal * (this -> endY - this -> startY)));
            int nxtWidth = (this -> startWidth + int(easingVal * (this -> endWidth - this -> startWidth)));
            int nxtHeight = (this -> startHeight + int(easingVal * (this -> endHeight - this -> startHeight)));
            
            this -> targetUI -> setX(nxtX);
            this -> targetUI -> setY(nxtY);
            this -> targetUI -> setWidth(nxtWidth);
            this -> targetUI -> setHeight(nxtHeight);
            
            updateTime();
        }
        if (millis() - this -> startTime >= totalTime) {
            this -> targetUI -> setX(this -> endX);
            this -> targetUI -> setY(this -> endY);
            this -> targetUI -> setWidth(endWidth);
            this -> targetUI -> setHeight(endHeight);
            this -> isFinished = true;
        }
    }
    else if (this -> type == 1) {
        if (getCurDuration() > 10 && !this -> isFinished) {
            int curVal = *(this -> targetVal);

            float tmp = float(int(millis()) - this -> startTime) / float(totalTime);
            float easingVal = pow(2, 10 * tmp - 10);
            
            int nxtVal = (this -> startVal + int(easingVal * (this -> endVal - this -> startVal)));
            *(this -> targetVal) = nxtVal;
            updateTime();
        }
        if (millis() - this -> startTime >= totalTime) {
            *(this -> targetVal) = this -> endVal;
            this -> isFinished = true;
        }
    }
}

void Animation::animateBounce() { // a bouncy easing curve
    if (this -> type == 0) {
        if (getCurDuration() > 10 && !this -> isFinished) {
            int curX = this -> targetUI -> getX();
            int curY = this -> targetUI -> getY();

            float tmp = float(int(millis()) - this -> startTime) / float(totalTime);
            
            float easingVal = pow(2, -10 * tmp) * sin((tmp * 10 - 0.75) * (2 * 3.14 / 3)) + 1;

            int nxtX = (this -> startX + int(easingVal * (this -> endX - this -> startX)));
            int nxtY = (this -> startY + int(easingVal * (this -> endY - this -> startY)));
            int nxtWidth = (this -> startWidth + int(easingVal * (this -> endWidth - this -> startWidth)));
            int nxtHeight = (this -> startHeight + int(easingVal * (this -> endHeight - this -> startHeight)));
            
            this -> targetUI -> setX(nxtX);
            this -> targetUI -> setY(nxtY);
            this -> targetUI -> setWidth(nxtWidth);
            this -> targetUI -> setHeight(nxtHeight);
            
            updateTime();
        }
        if (millis() - this -> startTime >= totalTime) {
            this -> targetUI -> setX(this -> endX);
            this -> targetUI -> setY(this -> endY);
            this -> targetUI -> setWidth(endWidth);
            this -> targetUI -> setHeight(endHeight);
            this -> isFinished = true;
        }
    }
    else if (this -> type == 1) {
        if (getCurDuration() > 10 && !this -> isFinished) {
            int curVal = *(this -> targetVal);

            float tmp = float(int(millis()) - this -> startTime) / float(totalTime);
            float easingVal = pow(2, -10 * tmp) * sin((tmp * 10 - 0.75) * (2 * 3.14 / 3)) + 1;
            
            int nxtVal = (this -> startVal + int(easingVal * (this -> endVal - this -> startVal)));
            *(this -> targetVal) = nxtVal;
            updateTime();
        }
        if (millis() - this -> startTime >= totalTime) {
            *(this -> targetVal) = this -> endVal;
            this -> isFinished = true;
        }
    }
}

// Animate UIElement
void Animation::animate() {
    switch (this -> aniType) {
        case LINEAR:
            animateLinear();
            break;
        case INDENT:
            animateIndent();
            break;
        case INDENTINV:
            animateIndentInv();
            break;
        case BOUNCE:
            animateBounce(); 
        default:
            break;
    }
}

std::map <UIElement*, Animation*> animationsUI; // A map that stores which UIElement corresponds to which Animation object
std::map <int*, Animation*> animationsInt; // A map that stores which animated int corresponds to which Animation object
std::list <UIElement*> tmpAnimationUI; // A list of UIElements that need animating
int durationWhole = 0;

// An element might have multiple animations added to it at once, this mapping procedure makes sure that only the latest animation gets animated
void insertAnimation(Animation* animation) {
    if (animation -> getTargetElement() != nullptr) {
        animationsUI[animation -> getTargetElement()] = animation;
    }
    else {
        animationsInt[animation -> getTargetVal()] = animation;
    }   
}

// Returns if the target value has finished animating or not
bool isFinished(int* targetInt) {
    return animationsInt.find(targetInt) == animationsInt.end();
}

// Returns if the UIElement has finished animating or not
bool isFinished(UIElement* targetUI) {
    return animationsUI.find(targetUI) == animationsUI.end();
}


void insertTmpAnimationPointer(UIElement* tmpUI) {
    tmpAnimationUI.push_back(tmpUI);
}

// Main animation procedure
void animateAll() {
    if (millis() - durationWhole < 5) return;
    durationWhole = millis();
    for (auto animation = animationsUI.begin(); animation != animationsUI.end();) {
        if (!((animation -> second) -> getIsFinished())) {
            if (!((animation -> second) -> getIsStarted())) {
                animation -> second -> init();
            }
            else if ((animation -> second) -> checkTime() && !((animation -> second) -> getIsAnimating())) {
                animation -> second -> initAni();
            }

            if ((animation -> second) -> getIsAnimating()) {
                animation -> second -> animate();
            }

            ++animation;
        }
        else {
            animation = animationsUI.erase(animation);
        }
    }

    for (auto animation = animationsInt.begin(); animation != animationsInt.end();) {
        if (!((animation -> second) -> getIsFinished())) {
            if (!((animation -> second) -> getIsStarted())) {
                animation -> second -> init();
            }
            else if ((animation -> second) -> checkTime() && !((animation -> second) -> getIsAnimating())) {
                animation -> second -> initAni();
            }

            if ((animation -> second) -> getIsAnimating()) {
                animation -> second -> animate();
            }

            ++animation;
        }
        else {
            animation = animationsInt.erase(animation);
        }
    }
}

// I forgot what this does but it is really important
void updateTmp() {
    for (auto cur = tmpAnimationUI.begin(); cur != tmpAnimationUI.end();) {
        if (!isFinished(*cur)) {
            cur++;
        }
        else {
            cur = tmpAnimationUI.erase(cur);
        }
    }
}
