#ifndef SRTF
#define SRTF

#include <string>
#include <queue>
#include <list>
#include "Scheduler.h"

class SRTF : public Scheduler {
    private:
        std::list<job> readyQ;
        void TimeStep();
        int Event(std::string&);
        bool Compare(const job& lhs, const job& rhs)
    public:
        SRTF(const std::string&, const int);
        void Simulate(const std::string&);
};
#endif
