#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <list>
#include <algorithm>
#include "Sjf.h"
using namespace std;

Sjf::Sjf(const string& s, const int numJobs, const float alpha, const int initialGuess, const int numProcesses): Scheduler(s, numJobs), alpha(alpha), previousBurst(numJobs, previousJobLength {(float)initialGuess, 0.0f, false}){
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

bool Sjf::Compare(const job& lhs, const job& rhs){
    previousJobLength lPrevJob = previousBurst[lhs.processId];
    previousJobLength rPrevJob = previousBurst[rhs.processId];

    float lhsPrediction = lPrevJob.predictionAvailable ? (1.0f - alpha) * lPrevJob.predictedValue + alpha * lPrevJob.ActualValue: lPrevJob.predictedValue;
    float rhsPrediction = rPrevJob.predictionAvailable ? (1.0f - alpha) * rPrevJob.predictedValue + alpha * rPrevJob.ActualValue: rPrevJob.predictedValue;

	return lPrevJob.predictedValue < rPrevJob.predictedValue;
}

int Sjf::Event(string& str){
        cout<<"size of readyList was "<<readyList.size()<<endl;
        cout<<"size of arrivals was "<<arrivals.size()<<endl;
        cout<<"current job was "<<executingJob.processId<<" arrived at "<<executingJob.arrivalTime<<" with remaining time of "<<executingJob.burst<<endl;
        if(!arrivals.empty() && arrivals.front().arrivalTime == time){
            readyList.push_back(arrivals.front());

            previousJobLength prevJob = previousBurst[arrivals.front().processId];
            prevJob.predictedValue = prevJob.predictionAvailable ? (1.0f - alpha) * prevJob.predictedValue + alpha * prevJob.ActualValue: prevJob.predictedValue
            prevJob.actualValue = arrivals.front().burst;
            prevJob.predictionAvailable = true;
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
        cout<<"size of readyList is now "<<readyList.size()<<endl;
        cout<<"size of arrivals is now "<<arrivals.size()<<endl;
        return 0;
}
