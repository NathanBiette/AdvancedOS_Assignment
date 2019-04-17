#include <iostream>
#include <string>
#include "Scheduler.h"
using namespace std;

 const string mystr = "data.txt";

int main()
{
    Scheduler scheduler(mystr, 5);
    scheduler.PrintInput();
    scheduler.Simulate("test.txt");
    RoundRobin roundRobin(mystr, 5, 5);
    roundRobin.PrintInput();
    roundRobin.Simulate("test2.txt");
    return 0;
}
