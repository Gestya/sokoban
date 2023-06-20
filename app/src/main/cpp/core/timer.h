#ifndef SOKOBAN_TIMER_H
#define SOKOBAN_TIMER_H

#include <time.h>

class Timer {
public:

    inline Timer () {
        clock_gettime(CLOCK_REALTIME, &start);
    }

    inline double getTime() const {
        struct timespec now;
        clock_gettime(CLOCK_REALTIME, &now);
        return
            (now.tv_sec - start.tv_sec) +
            (now.tv_nsec - start.tv_nsec) * 1e-9;
    }

private:
    struct timespec start;
};


#endif //SOKOBAN_TIMER_H
