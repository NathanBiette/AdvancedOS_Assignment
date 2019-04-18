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
    ReadInput(s);
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

int Srtf::Event(string& str){
        if(!arrivals.empty() && arrivals.front().arrivalTime == time){
            readyQ.push_back(arrivals.front());
            readyQ.sort(Compare);
            arrivals.pop();
        }
        if(!readyQ.empty() && (readyQ.front().burst < executingJob.burst || executingJob.burst <= 0)){
            executingJob.lastExecutionTime = time;
            if(readyQ.front().burst < executingJob.burst){
                readyQ.push_back(executingJob);
                readyQ.sort(Srtf::Compare);
            }
            executingJob = readyQ.front();
            totalWaitingTime += time - executingJob.lastExecutionTime;
            readyQ.pop_front();
            stringstream ss;
            ss << "(" << time << ", " << executingJob.processId << ")\n";
            str = ss.str();
            return 1;
            
        }
        return 0;
}

void Srtf::Simulate(const string &filename){
    ofstream myfile;
    myfile.open(filename, ios::trunc | ios::out);
    if (myfile.is_open() && arrivals.size() > 0){
        time = 0;
        // Iterate over the time steps
        do{
            string str;
            if(Srtf::Event(str)){
                myfile << str;
            }
            Srtf::TimeStep();
        }while(!arrivals.empty() || !readyQ.empty());
    }
    else cout << "Unable to open file";
    myfile << "average waiting time " << (float)totalWaitingTime / (float)numJobs<<endl;
    myfile.close();
}

bool Srtf::Compare(const job& lhs, const job& rhs){
	return lhs.burst < rhs.burst;
}

