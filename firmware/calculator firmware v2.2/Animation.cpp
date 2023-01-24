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
    this -> targetUI = targetUI;
    this -> aniType = aniType;
    this -> startX = targetUI -> getX();
    this -> startY = targetUI -> getY();
    this -> endX = endX;
    this -> endY = endY;
    this -> startWidth = targetUI -> getWidth();
    this -> startHeight = targetUI -> getHeight();
    this -> endWidth = endWidth;
    this -> endHeight = endHeight;
    this -> targetUI -> setTargetWidth(endWidth);
    this -> targetUI -> setTargetHeight(endHeight);
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

void Animation::animateIndent() {
    if (getCurDuration() > 10 && !this -> isFinished) {
        int curX = this -> targetUI -> getX();
        int curY = this -> targetUI -> getY();

        int nxtX = (this -> startX + (millis() - this -> startTime) * (this -> endX - this -> startX) / totalTime);
        int nxtY = (this -> startY + (millis() - this -> startTime) * (this -> endY - this -> startY) / totalTime);
        Serial.printf("nxtX, nxtY: %d, %d\n", nxtX, nxtY);

        this -> targetUI -> setX(nxtX);
        this -> targetUI -> setY(nxtY);
        
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