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
    bool predictionAvailable;
};

struct job {
  int processId = 0;
  int arrivalTime = 0;
  int lastExecutionTime = 0;
  int burst = 0;
  bool startedExecution = false;
  float predictedValue;
  float actualValue;
  bool predictionAvailable;
};

class Sjf : public Scheduler {
    private:
        std::list<job> readyList;
        void TimeStep();
        int Event(std::string&);
        float alpha;
        std::vector<previousJobLength> previousBurst;
        static bool Compare(const job&, const job&);
    public:
        // name of input file, num of jobs, alpha, initial guess
        Sjf(const std::string&, const int, const float, const int, const int);
        bool IsReadyQEmpty(){return readyList.empty();};
};
#endif
