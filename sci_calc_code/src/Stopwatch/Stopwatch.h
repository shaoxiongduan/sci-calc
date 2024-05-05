#ifndef STOPWATCH_H
#define STOPWATCH_H

#include "../Utils/Util.h"

//this is only for testing, the final product will be very different to this

class Stopwatch {
    public:
        Stopwatch();

        void start();

        void pause();

        void reset();

        bool getIsTicking();

        int lap();

        std::string toTime(int t);

        int getTimeElapsed();

        void update();

    private:
        int startTime;
        int curTimeElapsed;
        int timeBetweenIntervals;
        bool isTicking;
};

#endif
