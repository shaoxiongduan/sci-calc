#include "Stopwatch.h"

Stopwatch::Stopwatch() {
    this -> curTimeElapsed = 0;
    this -> startTime = 0;
    this -> timeBetweenIntervals = 0;
    this -> isTicking = false;
}

void Stopwatch::start() {
    this -> isTicking = true;
}

void Stopwatch::pause() {
    this -> isTicking = false;
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
    this -> isTicking = false;
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
    else {
        this -> startTime = millis();
    }
}



