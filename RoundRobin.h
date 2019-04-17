#ifndef ROUNDROBIN
#define ROUNDROBIN

#include <string>
#include <vector>
#include <queue>
#include "Scheduler.h"

class RoundRobin : public Scheduler {
    private:
        int Q;
        int remainingQTime;
        void TimeStep();
        int Event(std::string&);
    public:
        RoundRobin(const std::string&, const int, const int);
        void Simulate(const std::string&);
};
#endif
