#ifndef SCHEDULER
#define SCHEDULER

#include <string>
#include <vector>

struct arrival {
  int processId;
  int arrivalTime;
  int burst;
} ;

class Scheduler
{
     private :
          //std::string filename;
          //arrival* arrivals;
          int numProcesses;
          int numArrivals;
          std::vector<arrival> arrivals;
     public :
          Scheduler(const std::string&, const int, const int);
          void ReadInput(const std::string&);
          void PrintInput();
};
 
#endif
