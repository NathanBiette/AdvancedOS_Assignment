#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <list>
#include <algorithm>
#include "Srtf.h"
using namespace std;

Srtf::Srtf(const string& s, int numJobs): Scheduler(s, numJobs){
}

void Srtf::TimeStep(){
    int nextEventTime = 0;
    if(!arrivals.empty()){
        if(executingJob.burst > 0){
            nextEventTime = min(time + executingJob.burst, arrivals.front().arrivalTime);
        }else{
            nextEventTime = arrivals.front().arrivalTime;
        }
    }else{
        if(executingJob.burst > 0){
            nextEventTime = time + executingJob.burst;
        }else{
            cout<< "error shouldn't be steping time here !"<<endl;
        }
    }
    executingJob.burst += (time - nextEventTime);
    time = nextEventTime;
    cout<<"time is now "<<time<<endl;
}

bool Compare(const job& lhs, const job& rhs){
	return lhs.burst < rhs.burst;
}

int Srtf::Event(string& str){
        cout<<"size of readyQ "<<readyQ.size()<<endl;
        cout<<"size of arrivals "<<arrivals.size()<<endl;
        if(!arrivals.empty() && arrivals.front().arrivalTime == time){
            readyQ.push_back(arrivals.front());
            readyQ.sort(Compare);
            arrivals.pop();
        }
        if(!readyQ.empty()){
            if(readyQ.front().burst < executingJob.burst || executingJob.burst <= 0){
                executingJob.lastExecutionTime = time;
                if(executingJob.burst > 0){
                    readyQ.push_back(executingJob);
                    readyQ.sort(Compare);
                }
                executingJob = readyQ.front();
                cout<<executingJob.processId<<endl;
                totalWaitingTime += time - executingJob.lastExecutionTime;
                readyQ.pop_front();
                stringstream ss;
                ss << "(" << time << ", " << executingJob.processId << ")\n";
                str = ss.str();
                return 1;
            }
        }
        return 0;
}

