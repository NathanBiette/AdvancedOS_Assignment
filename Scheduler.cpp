#include <iostream>
#include "Scheduler.h"
using namespace std;

Scheduler::Scheduler(const std::string &s){
    ReadInput(s);
}

void ReadInput(const std::string &filename){
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
