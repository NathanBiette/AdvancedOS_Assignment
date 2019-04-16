#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include "Scheduler.h"
using namespace std;

void Scheduler::TimeStep(){
    int nextEventTime = (nextArrival < numArrivals) ?  
        min(arrivals[nextArrival].arrivalTime, time + executingJob.remainingTime) : 
        time + executingJob.remainingTime;
    executingJob.remainingTime += (time - nextEventTime);
    time = nextEventTime;
}

Scheduler::Scheduler(const string &s, int numProcesses, int numArrivals): numProcesses(numProcesses), numArrivals(numArrivals){
    ReadInput(s);
}

void Scheduler::ReadInput(const string &filename){
    string line;
    ifstream myfile;
    myfile.open(filename);
    arrivals.resize(numArrivals);
    if (myfile.is_open()){
        for (int i = 0; i < numArrivals; i++){
            getline(myfile,line);
            stringstream ss;
            ss << line;
            ss >> arrivals[i].processId;
            ss >> arrivals[i].arrivalTime;
            ss >> arrivals[i].burst;
        }
    }
    else cout << "Unable to open file"; 
    myfile.close();
    return;
}

void Scheduler::PrintInput(){
    for(int i=0; i<arrivals.size(); ++i){
        cout<<arrivals[i].processId<<" ";
        cout<<arrivals[i].arrivalTime<<" ";
        cout<<arrivals[i].burst<<endl;
    }
    return;
}

void Scheduler::Simulate(const string &filename){
    ofstream myfile;
    myfile.open(filename, ios::trunc | ios::out);
    if (myfile.is_open() && arrivals.size() > 0){

        time = 0;
        executingJob = {arrivals[0].processId, arrivals[0].burst};
        myfile << "(" << time << ", " << executingJob.processId << ")\n";
        nextArrival = 1;
        Scheduler::TimeStep();
        // Iterate over the time steps
        while(nextArrival < numArrivals || !readyQ.empty()){
            
            if(nextArrival < numArrivals){
                if(arrivals[nextArrival].arrivalTime == time){
                    job newJob = {arrivals[nextArrival].processId, arrivals[nextArrival].burst};
                    readyQ.push(newJob);
                    nextArrival++;
                }
            }
            if(executingJob.remainingTime <= 0){
                if(!readyQ.empty()){
                    executingJob = readyQ.front();
                    readyQ.pop();
                    myfile << "(" << time << ", " << executingJob.processId << ")\n";
                }
            }
            Scheduler::TimeStep();

/*
            if(arrivals[nextArrival].arrivalTime < time + executingJob.remainingTime){
                time = arrivals[nextArrival].arrivalTime;
                job newJob = {arrivals[nextArrival].processId, arrivals[nextArrival].burst};
                readyQ.push(newJob);
                nextArrival= (nextArrival < numArrivals - 1) ? nextArrival + 1 : nextArrival;
            }else{
                time += executingJob.remainingTime;
                if(!readyQ.empty()){
                    executingJob = readyQ.front();
                    readyQ.pop();
                    myfile << "(" << time << ", " << executingJob.processId << ")\n";
                }
                if(time == arrivals[nextArrival].arrivalTime){
                    job newJob = {arrivals[nextArrival].processId, arrivals[nextArrival].burst};
                    readyQ.push(newJob);
                    nextArrival= (nextArrival < numArrivals - 1) ? nextArrival + 1 : nextArrival;
                }
            }

*/
        }
    }
    else cout << "Unable to open file";
    myfile.close();
}
