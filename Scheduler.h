#ifndef SCHEDULER
#define SCHEDULER

#include <string>
#include <vector>
#include <queue>

struct job {
  int processId;
  int arrivalTime;
  int burst;
  bool startedExecution = false;
};

class Scheduler
{
    private :
        int time = 0;
        int totalWaitingTime = 0;
        job executingJob;
        int numJobs;
        std::queue<job> arrivals;
        std::queue<job> readyQ;
        void TimeStep();
        int Event(std::string&);
    public :
        Scheduler(const std::string&, const int);
        void ReadInput(const std::string&);
        void PrintInput();
        void Simulate(const std::string&);
};
 
#endif
