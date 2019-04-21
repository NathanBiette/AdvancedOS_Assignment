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

bool Srtf::Compare(const job& lhs, const job& rhs){
	return lhs.burst < rhs.burst;
}

int Srtf::Event(string& str){
        cout<<"size of readyList was "<<readyList.size()<<endl;
        cout<<"size of arrivals was "<<arrivals.size()<<endl;
        cout<<"current job was "<<executingJob.processId<<" arrived at "<<executingJob.arrivalTime<<" with remaining time of "<<executingJob.burst<<endl;
        if(!arrivals.empty() && arrivals.front().arrivalTime == time){
            readyList.push_back(arrivals.front());
            readyList.sort(Compare);
            arrivals.pop();
        }
        if(!readyList.empty()){
            if(readyList.front().burst < executingJob.burst || executingJob.burst <= 0){
                executingJob.lastExecutionTime = time;
                if(executingJob.burst > 0){
                    readyList.push_back(executingJob);
                    readyList.sort(Compare);
                }
                executingJob = readyList.front();
                cout<<executingJob.processId<<endl;
                totalWaitingTime += time - executingJob.lastExecutionTime;
                readyList.pop_front();
                stringstream ss;
                ss << "(" << time << ", " << executingJob.processId << ")\n";
                str = ss.str();
                return 1;
            }
        }
        cout<<"size of readyList is now "<<readyList.size()<<endl;
        cout<<"size of arrivals is now "<<arrivals.size()<<endl;
        return 0;
}

