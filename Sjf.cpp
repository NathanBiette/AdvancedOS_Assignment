#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <list>
#include <algorithm>
#include "Sjf.h"
using namespace std;

Sjf::Sjf(const string& s, const int numJobs, const float alpha, const int initialGuess, const int numProcesses): Scheduler(s, numJobs), alpha(alpha), previousBurst(numJobs, previousJobLength {(float)initialGuess, (float)initialGuess}){
    cout<<"test "<<endl;
    cout<<previousBurst[0].predictedValue<<endl;
    cout<<previousBurst[0].actualValue<<endl;
}

void Sjf::TimeStep(){
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

bool Sjf::Compare(const job2& lhs, const job2& rhs){
	return lhs.predictedValue < rhs.predictedValue;
}

int Sjf::Event(string& str){
        cout<<"size of readyList was "<<readyList.size()<<endl;
        cout<<"size of arrivals was "<<arrivals.size()<<endl;
        cout<<"current job was "<<executingJob.processId<<" arrived at "<<executingJob.arrivalTime<<" with remaining time of "<<executingJob.burst<<endl;
        if(!arrivals.empty() && arrivals.front().arrivalTime == time){

            //previousJobLength prevJob = previousBurst[arrivals.front().processId];
            previousBurst[arrivals.front().processId].predictedValue = (1.0f - alpha) * previousBurst[arrivals.front().processId].predictedValue + alpha * previousBurst[arrivals.front().processId].actualValue;
            cout<<"Value predicted for job "<<arrivals.front().processId<<" = "<<previousBurst[arrivals.front().processId].predictedValue<<endl;
            previousBurst[arrivals.front().processId].actualValue = arrivals.front().burst;

            //arrivals.front().predictedValue = prevJob.predictedValue;

            readyList.push_back(job2{
                arrivals.front().processId,
                arrivals.front().arrivalTime,
                arrivals.front().lastExecutionTime,
                arrivals.front().burst,
                false,
                previousBurst[arrivals.front().processId].predictedValue});
            readyList.sort(Compare);
            arrivals.pop();
        }
        if(!readyList.empty()){
            if(executingJob.burst <= 0){
                executingJob.lastExecutionTime = time;
                executingJob = readyList.front();
                cout<<"new job executing = "<<executingJob.processId<<endl;
                totalWaitingTime += time - executingJob.lastExecutionTime;
                readyList.pop_front();
                stringstream ss;
                ss << "(" << time << ", " << executingJob.processId << ")\n";
                str = ss.str();
                return 1;
            }
        }
        return 0;
}
