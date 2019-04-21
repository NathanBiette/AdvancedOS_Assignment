#ifndef SJF
#define SJF

#include <vector>
#include <string>
#include <queue>
#include <list>
#include "Scheduler.h"

class Sjf : public Scheduler {
    private:
        std::list<job> readyList;
        void TimeStep();
        int Event(std::string&);
        float alpha;
        std::vector<float> previousBurst;
    public:
        // name of input file, num of jobs, alpha, initial guess
        Sjf(const std::string&, const int, const float, const int, const int);
        bool IsReadyQEmpty(){return readyList.empty();};
};
#endif
