#include <iostream>
#include <fstream>
#include <string>
#include "Scheduler.h"
#include "RoundRobin.h"
#include "Srtf.h"
using namespace std;

 const string mystr = "input.txt";

int CountLines(const string& filename){
    int count = 0;
    string line;
    ifstream myfile;
    myfile.open(filename);
    cout << "Reading input file of simulation :" << '\n';
    if (myfile.is_open()){
        while ( getline (myfile,line) ){
            cout << line << '\n';
            count++;
        }
            myfile.close();
    }
    else cout << "Unable to open file"; 
    return count;
}

int main()
{
    int numLines = CountLines(mystr);
    cout<<"Number of jobs = "<<numLines<<endl;
    
    cout<< ">>>>>>>>>>Simulating FCFS no premption<<<<<<<<<<<"<<endl;
    Scheduler * scheduler = new Scheduler(mystr, numLines);
    //Scheduler scheduler(mystr, numLines);
    scheduler->PrintInput();
    scheduler->Simulate("test.txt");
    cout<< ">>>>>>>>>>Simulating RoundRobin<<<<<<<<<<<<<<<<<<"<<endl;
    Scheduler * roundRobin = new RoundRobin(mystr, numLines, 5);
    //RoundRobin roundRobin(mystr, numLines, 5);
    roundRobin->PrintInput();
    roundRobin->Simulate("test2.txt");
    cout<< ">>>>>>>>>>Simulating SRTF with premption<<<<<<<<<"<<endl;
    Scheduler * srtf = new Srtf(mystr, numLines);
    //Srtf srtf(mystr, numLines);
    srtf->PrintInput();
    srtf->Simulate("test3.txt");
    return 0;
}
