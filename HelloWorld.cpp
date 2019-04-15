#include <iostream>
#include <string>
#include "Scheduler.h"
using namespace std;

 const string mystr = "data.txt";

int main()
{
    cout << "Hello, World!" << endl;
    Scheduler scheduler(mystr);
    return 0;
}
