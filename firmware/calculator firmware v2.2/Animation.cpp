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
}

/*
Animation::Animation(UIElement* targetUI, AnimationType aniType, int startX, int startY, int endX, int endY, int startWidth, int startHeight, int endWidth, int endHeight, int totalTime) {
    this -> targetUI = targetUI;
    this -> aniType = aniType;
    this -> startX = startX;
    this -> startY = startY;
    this -> endX = endX;
    this -> endY = endY;
    this -> startWidth = startWidth;
    this -> startHeight = startHeight;
    this -> endWidth = endWidth;
    this -> endHeight = endHeight;
    this -> totalTime = totalTime;
    this -> isFinished = false;
    this -> isStarted = false;
}
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
}

void Animation::init() {
    this -> prevTime = millis();
    this -> startTime = millis();
    this -> isStarted = true;
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

void Animation::updateTime() {
    this -> prevTime = millis();
}

void Animation::animateSmooth() {
    Serial.println("in animation");
    if (this -> type == 0) {
        if (getCurDuration() > 10 && !this -> isFinished) {
            int curX = this -> targetUI -> getX();
            int curY = this -> targetUI -> getY();

            float tmp = float(int(millis()) - this -> startTime) / float(totalTime);

            int nxtX = (this -> startX + int(tmp * (this -> endX - this -> startX)));
            int nxtY = (this -> startY + int(tmp * (this -> endY - this -> startY)));
            int nxtWidth = (this -> startWidth + int(tmp * (this -> endWidth - this -> startWidth)));
            int nxtHeight = (this -> startHeight + int(tmp * (this -> endHeight - this -> startHeight)));
            
            
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

            int nxtVal = (this -> startVal + int(tmp * (this -> endVal - this -> startVal)));
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

            int nxtX = (this -> startX + int(tmp * (this -> endX - this -> startX)));
            int nxtY = (this -> startY + int(tmp * (this -> endY - this -> startY)));
            int nxtWidth = (this -> startWidth + int(tmp * (this -> endWidth - this -> startWidth)));
            int nxtHeight = (this -> startHeight + int(tmp * (this -> endHeight - this -> startHeight)));
            
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

            int nxtVal = (this -> startVal + int(tmp * (this -> endVal - this -> startVal)));
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
        case SMOOTH:
            animateSmooth();
            break;
        case INDENT:
            animateIndent();
            break;
        default:
            break;
    }
}

std::list <Animation*> animations;

void insertAnimation(Animation* animation) {
    animations.push_back(animation);
}

void animateAll() {
    for (auto animation = animations.begin(); animation != animations.end();) {
        if (!((*animation) -> getIsFinished())) {
            if (!((*animation) -> getIsStarted())) {
                (*animation) -> init();
            }
            Serial.printf("Animating: will take %d seconds\n", (*animation) -> getTotDuration());
            (*animation) -> animate();
            ++animation;
        }
        else {
            animation = animations.erase(animation);
        }
    }
}