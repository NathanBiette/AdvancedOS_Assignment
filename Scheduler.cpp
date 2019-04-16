#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include "Scheduler.h"
using namespace std;

void Scheduler::TimeStep(){
    int nextEventTime = 0;
    if(!arrivals.empty()){
        if(executingJob.remainingTime > 0){
            nextEventTime = min(time + executingJob.remainingTime, arrivals.front().arrivalTime);
            cout<<"a"<<endl;
        }else{
            nextEventTime = arrivals.front().arrivalTime;
            cout<<"b"<<endl;
        }
    }else{
        if(executingJob.remainingTime > 0){
            nextEventTime = time + executingJob.remainingTime;
            cout<<"c"<<endl;
        }else{
            cout<< "error shouldn't be steping time here !"<<endl;
            cout<<"d"<<endl;
        }
    }
    executingJob.remainingTime += (time - nextEventTime);
    time = nextEventTime;
    cout<<"time is now "<<time<<endl;
}

Scheduler::Scheduler(const string &s, int numProcesses, int numArrivals): numProcesses(numProcesses), numArrivals(numArrivals){
    ReadInput(s);
}

void Scheduler::ReadInput(const string &filename){
    string line;
    ifstream myfile;
    myfile.open(filename);
    if (myfile.is_open()){
        for (int i = 0; i < numArrivals; i++){
            getline(myfile,line);
            stringstream ss;
            ss << line;
            arrival newArrival = {0, 0, 0};
            ss >> newArrival.processId;
            ss >> newArrival.arrivalTime;
            ss >> newArrival.burst;
            arrivals.push(newArrival);
            cout<<"reading arrival"<<endl;
        }
    }
    else cout << "Unable to open file"; 
    myfile.close();
    return;
}

void Scheduler::PrintInput(){
    cout<<"number of arrivals: "<<arrivals.size()<<endl;
    for(int i=0; i<arrivals.size();i++){
        cout<<arrivals.front().processId<<" ";
        cout<<arrivals.front().arrivalTime<<" ";
        cout<<arrivals.front().burst<<endl;
        arrivals.push(arrivals.front());
        arrivals.pop();
    }
    return;
}

void Scheduler::Simulate(const string &filename){
    ofstream myfile;
    myfile.open(filename, ios::trunc | ios::out);
    if (myfile.is_open() && arrivals.size() > 0){

        time = 0;
        cout<<"time is now "<<time<<endl;
        executingJob = {arrivals.front().processId, arrivals.front().burst};
        arrivals.pop();
        myfile << "(" << time << ", " << executingJob.processId << ")\n";
        Scheduler::TimeStep();
        // Iterate over the time steps
        while(!arrivals.empty() || !readyQ.empty()){
            
            if(!arrivals.empty() && arrivals.front().arrivalTime == time){
                job newJob = {arrivals.front().processId, arrivals.front().burst};
                readyQ.push(newJob);
                arrivals.pop();
            }
            if(!readyQ.empty() && executingJob.remainingTime <= 0){
                executingJob = readyQ.front();
                readyQ.pop();
                myfile << "(" << time << ", " << executingJob.processId << ")\n";
            }
            Scheduler::TimeStep();
        }
    }
    else cout << "Unable to open file";
    myfile.close();
}
