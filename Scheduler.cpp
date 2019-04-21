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

int Scheduler::Event(string& str){
        if(!arrivals.empty() && arrivals.front().arrivalTime == time){
            readyQ.push(arrivals.front());
            arrivals.pop();
        }
        if(!readyQ.empty() && executingJob.burst <= 0){
            executingJob.lastExecutionTime = time;
            executingJob = readyQ.front();
            if(!executingJob.startedExecution){
                totalWaitingTime += time - executingJob.lastExecutionTime;
            }
            readyQ.pop();
            stringstream ss;
            ss << "(" << time << ", " << executingJob.processId << ")\n";
            str = ss.str();
            return 1;
        }
        return 0;
}

Scheduler::Scheduler(const string& s, int numJobs): numJobs(numJobs){
    ReadInput(s);
}

void Scheduler::ReadInput(const string& filename){
    string line;
    ifstream myfile;
    myfile.open(filename);
    if (myfile.is_open()){
        for (int i = 0; i < numJobs; i++){
            getline(myfile,line);
            stringstream ss;
            ss << line;
            job newArrival = {0, 0, 0, 0, false};
            ss >> newArrival.processId;
            ss >> newArrival.arrivalTime;
            ss >> newArrival.burst;
            newArrival.lastExecutionTime = newArrival.arrivalTime;
            arrivals.push(newArrival);
        }
    }
    else cout << "Unable to open file"; 
    myfile.close();
    return;
}

void Scheduler::PrintInput(){
    cout<<"input data :"<<endl;
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
        // Iterate over the time steps
        cout<<"starting simulation"<<endl;
        int iterCount = 0;
        do{
            cout<<"-- new iteration: "<<iterCount<<" --"<<endl;
            if(iterCount > 200){
                cout<<"Too many iteration ! Process probably stuck"<<endl;
                return;
            }
            string str;
            if(this->Event(str)){
                myfile << str;
            }
            this->TimeStep();
            iterCount++;
        }while(!arrivals.empty() || !this->IsReadyQEmpty());
    }
    else cout << "Unable to open file";
    myfile << "average waiting time " << (float)totalWaitingTime / (float)numJobs<<endl;
    myfile.close();
}


