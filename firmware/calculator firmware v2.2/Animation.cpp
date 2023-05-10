#include "Animation.h"


/*
Animation::Animation(UIElement* targetUI, AnimationType aniType, int startX, int startY, int endX, int endY, int totalTime) {
    this -> targetUI = targetUI;
    this -> aniType = aniType;
    this -> startX = startX;
    this -> startY = startY;
    this -> endX = endX;
    this -> endY = endY;
    this -> startWidth = targetUI -> getWidth();
    this -> startHeight = targetUI -> getHeight();
    this -> endWidth = targetUI -> getWidth();
    this -> endHeight = targetUI -> getHeight();
    this -> totalTime = totalTime;
    this -> isFinished = false;
    this -> isStarted = false;
}
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


void Animation::init() {
    this -> createTime = millis();
    this -> isStarted = true;
}

bool Animation::checkTime() {
    return (millis() - this -> createTime >= this -> delayTime);
}

void Animation::initAni() {
    this -> prevTime = millis();
    this -> startTime = millis();
    this -> isAnimating = true;
}

UIElement* Animation::getTargetElement() {
    return this -> targetUI;
}

int* Animation::getTargetVal() {
    return this -> targetVal;
}

int Animation::getCurDuration() {
    int curTime = millis();
    return curTime - this -> prevTime;
}

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

void Animation::animateLinear() { //Linear animation
    Serial.println("in animation");
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
            
            
            Serial.printf("nxtX, nxtY, nxtWidth, nxtHeight: %d, %d, %d, %d\n", nxtX, nxtY, nxtWidth, nxtHeight);

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
        Serial.println("in int animation");
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
            Serial.printf("tmp: %f, easingval: %f\n", tmp, easingVal);
            
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
            Serial.printf("tmp: %f, easingval: %f\n", tmp, easingVal);
            
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
            Serial.printf("tmp: %f, easingval: %f\n", tmp, easingVal);
            
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

std::map <UIElement*, Animation*> animationsUI;
std::map <int*, Animation*> animationsInt;
std::list <UIElement*> tmpAnimationUI;
int durationWhole = 0;

void insertAnimation(Animation* animation) {
    if (animation -> getTargetElement() != nullptr) {
        animationsUI[animation -> getTargetElement()] = animation;
    }
    else {
        animationsInt[animation -> getTargetVal()] = animation;
    }
    
}

bool isFinished(int* targetInt) {
    return animationsInt.find(targetInt) == animationsInt.end();
}

bool isFinished(UIElement* targetUI) {
    return animationsUI.find(targetUI) == animationsUI.end();
}


void insertTmpAnimationPointer(UIElement* tmpUI) {
    tmpAnimationUI.push_back(tmpUI);
}

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
                Serial.printf("Animating: will take %d seconds\n", animation -> second -> getTotDuration());
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
                Serial.printf("Animating: will take %d seconds\n", animation -> second -> getTotDuration());
                animation -> second -> animate();
            }

            
            ++animation;
        }
        else {
            animation = animationsInt.erase(animation);
        }
    }
}

void updateTmp() {
    for (auto cur = tmpAnimationUI.begin(); cur != tmpAnimationUI.end();) {
        if (!isFinished(*cur)) {
            // (*cur) -> draw();
            //Serial.println("ghjerogjfowerjgiotofjwqjwdfipjwoijdfiogwio");
            cur++;
        }
        else {
            cur = tmpAnimationUI.erase(cur);
        }
    }
}

bool isFinishedTmp() {

}