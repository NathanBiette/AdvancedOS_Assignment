#ifndef SRTF
#define SRTF

#include <string>
#include <queue>
#include <list>
#include "Scheduler.h"

class Srtf : public Scheduler {
    private:
        std::list<job> readyQ;
        //bool Compare(const job&, const job&);
        void TimeStep();
        int Event(std::string&);
    public:
        Srtf(const std::string&, const int);
        void Simulate(const std::string&);
};
#endif
