#include <iostream>
#include <fstream>
#include "Scheduler.h"
using namespace std;

Scheduler::Scheduler(const string &s, int numProcesses, int numArrivals): numProcesses(numProcesses), numArrivals(numArrivals){
    ReadInput(s);
}

void Scheduler::ReadInput(const string &filename){
    string line;
    ifstream myfile;
    myfile.open(filename);
    if (myfile.is_open()){
        while ( getline (myfile,line) ){
            cout << line << '\n';
        }
    }
    else cout << "Unable to open file"; 
    myfile.close();
    return;
}
