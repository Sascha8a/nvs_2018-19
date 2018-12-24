#include <thread>

#include "clock.h"
#include "timeslave.h"
#include "timemaster.h"

using namespace std;

int main()
{
    thread clock{Clock("SASCHA", 0, 0, 0)};
    thread slave1{TimeSlave{"Slave1", 0, 0, 0}};
    thread slave2{TimeSlave{"Slave2", 0, 0, 0}};
    thread master{TimeMaster{"Master", 0, 0, 0}};
    
    clock.join();
    slave1.join();
    slave2.join();
    master.join();

    return EXIT_SUCCESS;
}