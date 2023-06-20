#ifndef SOKOBAN_TASK_H
#define SOKOBAN_TASK_H


#include "timer.h"
#include <cassert>
//#include "glm/ext.hpp"


namespace curves {
    inline double Linear(const double& now, const double& duration) {
        return now / duration;
    }

    inline double Exponential(const double& now, const double& duration) {
        //return sin(glm::pi<double>() / 4.0 * now / duration);
        double d = now / duration;
        return exp( 2 * log(d));
    }

    inline double Logarithmic(const double& now, const double& duration) {
        //return sin(glm::pi<double>() / 4.0 * now / duration);
        double d = now / duration;
        return exp( 0.5 * log(d));
    }
} // namespace curves


class Task {
    friend class TaskManager;
public:
    using Updater = std::function<void(const double&, const double&)>;
    using Shaper = std::function<double(const double&, const double&)>;

    inline Task(const double& duration,
                const Updater& updater,
                const Shaper& shaper)
            : duration(duration) ,
              updater(updater),
              shaper(shaper) {
        assert(duration != 0);
    }

    ~Task() {

    }

private:
    bool update() {
        double now = timer.getTime();
        if (duration < 0) {
            // Endless task
            updater(-1.0, now);
            return false;
        } else if (now < duration) {
            // Task in progress
            double value = shaper(now, duration);
            updater(value, now);
            return false;
        } else {
            // Completed task
            updater(1.0, now);
            return true;
        }
    }

    double duration;
    Updater updater;
    Shaper shaper;
    Timer timer;
};


#endif //SOKOBAN_TASK_H
