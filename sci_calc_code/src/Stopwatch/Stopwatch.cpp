#include "Stopwatch.h"

Stopwatch::Stopwatch() {
    this -> curTimeElapsed = 0;
    this -> startTime = 0;
    this -> timeBetweenIntervals = 0;
    this -> pausedTime = 0;
    this -> isPaused = false;
    this -> isTicking = false;
}

void Stopwatch::start() {
    if (this -> isPaused) {
        this -> startTime += millis() - this -> pausedTime;
    } else {
        this -> startTime = millis();
    }
    this -> isTicking = true;
    this -> isPaused = false;
}

void Stopwatch::pause() {
    this -> isTicking = false;
    this -> isPaused = true;
    this->pausedTime = millis();
}

int Stopwatch::lap() {
    int tmp = this -> timeBetweenIntervals;
    this -> timeBetweenIntervals = 0;
    return tmp;
}

std::string Stopwatch::toTime(int t) {
    int hour = t / 3600000;
    t -= 3600000 * hour;
    int min = t / 60000;
    t -= 60000 * min;
    int sec = t / 1000;
    t -= 1000 * sec;
    return numToStrRaw(hour) + ":" + numToStrRaw(min) + ":" + numToStrRaw(sec) + ":" + numToStrRaw(t);
}

int Stopwatch::getTimeElapsed() {
    return this -> curTimeElapsed;
}

void Stopwatch::reset() {
    this -> startTime = millis();
    this -> curTimeElapsed = 0;
    this -> timeBetweenIntervals = 0;
    this -> pausedTime = 0;
    this -> isTicking = false;
    this -> isPaused = false;
}

bool Stopwatch::getIsTicking() {
    return this -> isTicking;
}

void Stopwatch::update() {

    if (this -> isTicking) {
        int diff = millis() - this -> startTime - this -> curTimeElapsed;
        this -> curTimeElapsed += diff;
        this -> timeBetweenIntervals += diff;
    }
    else if(!this -> isPaused){
        this -> startTime = millis();
    }
}



