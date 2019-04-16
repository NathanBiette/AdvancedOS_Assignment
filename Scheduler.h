#ifndef SCHEDULER
#define SCHEDULER

#include <string>
#include <vector>
#include <queue>

struct arrival {
  int processId;
  int arrivalTime;
  int burst;
};

struct job {
  int processId;
  int remainingTime;
};

class Scheduler
{
    private :
        //std::string filename;
        //arrival* arrivals;
        int time = 0;
        job executingJob;
        int numProcesses;
        int numArrivals;
        std::queue<arrival> arrivals;
        std::queue<job> readyQ;
        void TimeStep();
        int Event(std::string&);
    public :
        Scheduler(const std::string&, const int, const int);
        void ReadInput(const std::string&);
        void PrintInput();
        void Simulate(const std::string&);
};
 
#endif
