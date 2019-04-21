#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
#include "Scheduler.h"
#include "RoundRobin.h"
#include "Srtf.h"
#include "Sjf.h"
using namespace std;

 const string mystr = "input.txt";

void CountLines(const string& filename, int& count, int& numProc){
    count = 0;
    numProc = 0;
    string line;
    ifstream myfile;
    myfile.open(filename);
    cout << "Reading input file of simulation :" << '\n';
    if (myfile.is_open()){
        while ( getline (myfile,line) ){
            stringstream ss;
            ss << line;
            int procId;
            ss >> procId;
            numProc = max(procId, numProc);
            cout << line << '\n';
            count++;
        }
            myfile.close();
    }
    else cout << "Unable to open file"; 
    numProc++;
    return;
}

int main()
{
    int numLines;
    int numProc;
    CountLines(mystr, numLines, numProc);
    cout<<"Number of jobs = "<<numLines<<endl;
    cout<<"Number of processes = "<<numProc<<endl;

    cout<< ">>>>>>>>>>Simulating FCFS no premption<<<<<<<<<<<"<<endl;
    Scheduler * scheduler = new Scheduler(mystr, numLines);
    scheduler->PrintInput();
    scheduler->Simulate("test.txt");
    cout<< ">>>>>>>>>>Simulating RoundRobin<<<<<<<<<<<<<<<<<<"<<endl;
    Scheduler * roundRobin = new RoundRobin(mystr, numLines, 5);
    roundRobin->PrintInput();
    roundRobin->Simulate("test2.txt");
    cout<< ">>>>>>>>>>Simulating SRTF with premption<<<<<<<<<"<<endl;
    Scheduler * srtf = new Srtf(mystr, numLines);
    srtf->PrintInput();
    srtf->Simulate("test3.txt");
    cout<< ">>>>>>>>>>Simulating SJF with premption<<<<<<<<<"<<endl;
    Scheduler * sjf = new Sjf(mystr, numLines, 0.5f, 5, numProc);
    return 0;
}
