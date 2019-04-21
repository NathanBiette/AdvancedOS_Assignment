#ifndef SRTF
#define SRTF

#include <string>
#include <queue>
#include <list>
#include "Scheduler.h"

class Srtf : public Scheduler {
    private:
        std::list<job> readyList;
        void TimeStep();
        int Event(std::string&);
        static bool Compare(const job&, const job& );
    public:
        Srtf(const std::string&, const int);
        bool IsReadyQEmpty(){return readyList.empty();};
};
#endif
