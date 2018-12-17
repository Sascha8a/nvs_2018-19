#include <thread>

#include "clock.h"
#include "timeslave.h"

using namespace std;

int main()
{
    thread clock{Clock("SASCHA", 10, 10, 10)};
    thread slave1{TimeSlave{"Slave1", 0, 0, 0}};
    thread slave2{TimeSlave{"Slave2", 0, 0, 0}};

    clock.join();
    slave1.join();
    slave2.join();

    return EXIT_SUCCESS;
}