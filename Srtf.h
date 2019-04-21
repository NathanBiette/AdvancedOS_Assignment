#ifndef SRTF
#define SRTF

#include <string>
#include <queue>
#include <list>
#include "Scheduler.h"

class Srtf : public Scheduler {
    private:
        std::list<job> readyList;
        //bool Compare(const job&, const job&);
        void TimeStep();
        int Event(std::string&);
    public:
        Srtf(const std::string&, const int);
        bool IsReadyQEmpty(){return readyList.empty();};
};
#endif
