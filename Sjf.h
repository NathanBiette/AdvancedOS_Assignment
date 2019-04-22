#ifndef SJF
#define SJF

#include <vector>
#include <string>
#include <queue>
#include <list>
#include "Scheduler.h"

struct previousJobLength{
    float predictedValue;
    float actualValue;
};

struct job2 {
  int processId = 0;
  int arrivalTime = 0;
  int lastExecutionTime = 0;
  int burst = 0;
  bool startedExecution = false;
  float predictedValue;
};

class Sjf : public Scheduler {
    private:
        job2 executingJob;
        std::list<job2> readyList;
        void TimeStep();
        int Event(std::string&);
        float alpha;
        std::vector<previousJobLength> previousBurst;
        static bool Compare(const job2&, const job2&);
    public:
        // name of input file, num of jobs, alpha, initial guess
        Sjf(const std::string&, const int, const float, const int, const int);
        bool IsReadyQEmpty(){return readyList.empty();};
};
#endif
