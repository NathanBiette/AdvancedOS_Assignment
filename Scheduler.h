#ifndef SCHEDULER
#define SCHEDULER

#include <string>
#include <vector>
#include <queue>

struct job {
  int processId = 0;
  int arrivalTime = 0;
  int lastExecutionTime = 0;
  int burst = 0;
  bool startedExecution = false;
};

class Scheduler
{
    protected :
        int time = 0;
        int totalWaitingTime = 0;
        job executingJob;
        int numJobs;
        std::queue<job> arrivals;
        std::queue<job> readyQ;
        virtual void TimeStep();
        virtual int Event(std::string&);
    public :
        Scheduler(const std::string&, const int);
        void ReadInput(const std::string&);
        void PrintInput();
        void Simulate(const std::string&);
};
#endif
