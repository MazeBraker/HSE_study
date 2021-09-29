#include <iostream>
#include <time.h>
using namespace std;
class TimeLogger {
private:
    long int time;
public:
    TimeLogger() {
        time = Now();
    }
    ~TimeLogger() {
        cout << Now() - time << " milliseconds\n";
    }
};