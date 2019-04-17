#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include "RoundRobin.h"
using namespace std;


RoundRobin::RoundRobin(const string& s, int numJobs, int Q): Scheduler(s, numJobs), Q(Q){
}

void RoundRobin::TimeStep(){
    int nextEventTime = 0;
    if(!arrivals.empty()){
        if(executingJob.burst > 0){
            nextEventTime = min(min(time + executingJob.burst, arrivals.front().arrivalTime), time + remainingQTime);
        }else{
            nextEventTime = min(arrivals.front().arrivalTime, time + remainingQTime);
        }
    }else{
        if(executingJob.burst > 0){
            nextEventTime = min(time + executingJob.burst, time + remainingQTime);
        }else{
            cout<< "error shouldn't be steping time here !"<<endl;
        }
    }
    executingJob.burst += (time - nextEventTime);
    remainingQTime += (time - nextEventTime);
    time = nextEventTime;
    cout<<"time is now "<<time<<endl;
}

int RoundRobin::Event(string& str){
        if(!arrivals.empty() && arrivals.front().arrivalTime == time){
            readyQ.push(arrivals.front());
            arrivals.pop();
        }
        if(!readyQ.empty() && remainingQTime <= 0 && executingJob.burst > 0){
            executingJob.lastExecutionTime = time;
            readyQ.push(executingJob);
            executingJob = readyQ.front();
            if(!executingJob.startedExecution){
                totalWaitingTime += time - executingJob.lastExecutionTime;
            }
            readyQ.pop();
            remainingQTime = Q;
            stringstream ss;
            ss << "(" << time << ", " << executingJob.processId << ")\n";
            str = ss.str();
            return 1;
        }
        if(!readyQ.empty() && executingJob.burst <= 0){
            executingJob = readyQ.front();
            if(!executingJob.startedExecution){
                totalWaitingTime += time - executingJob.lastExecutionTime;
            }
            readyQ.pop();
            remainingQTime = Q;
            stringstream ss;
            ss << "(" << time << ", " << executingJob.processId << ")\n";
            str = ss.str();
            return 1;
        }
        if(readyQ.empty() && executingJob.burst > 0){
            remainingQTime = Q;
        }
        return 0;
}

void RoundRobin::Simulate(const string &filename){
    ofstream myfile;
    myfile.open(filename, ios::trunc | ios::out);
    if (myfile.is_open() && arrivals.size() > 0){
        time = 0;
        // Iterate over the time steps
        do{
            string str;
            if(RoundRobin::Event(str)){
                myfile << str;
            }
            RoundRobin::TimeStep();
        }while(!arrivals.empty() || !readyQ.empty());
    }
    else cout << "Unable to open file";
    myfile << "average waiting time " << (float)totalWaitingTime / (float)numJobs<<endl;
    myfile.close();
}

