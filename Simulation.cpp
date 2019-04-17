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
    return 0;
}
