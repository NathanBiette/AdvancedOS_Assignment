#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Scheduler.h"
using namespace std;

Scheduler::Scheduler(const string &s, int numProcesses, int numArrivals): numProcesses(numProcesses), numArrivals(numArrivals){
    ReadInput(s);
}

void Scheduler::ReadInput(const string &filename){
    string line;
    ifstream myfile;
    myfile.open(filename);
    arrivals.resize(numArrivals);
    //stringstream ss;
    int found;
    if (myfile.is_open()){
        for (int i = 0; i < numArrivals; i++){
            getline(myfile,line);
            stringstream ss;
            ss << line;
            //string test;
            //ss >> test;
            //cout<<test<<endl;
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
}
