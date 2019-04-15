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
          //std::vector<arrival> arrivals;
     public :
          Scheduler(const std::string &s);
          void ReadInput(const std::string &filename);
};
 
#endif
