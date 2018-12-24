#include <thread>

#include "clock.h"
#include "timeslave.h"
#include "timemaster.h"

using namespace std;

int main()
{
    Clock clock("SASCHA", 0, 0, 0);
    TimeMaster master{"Master", 0, 0, 0};
    TimeSlave slave1{"Slave1", 0, 0, 0};
    TimeSlave slave2{"Slave2", 0, 0, 0};

    master.set_channel1(slave1.get_channel());
    master.set_channel2(slave2.get_channel());

    thread clock_thread{clock};
    thread master_thread{master};
    thread slave1_thread{slave1};
    thread slave2_thread{slave2};
    
    clock_thread.join();
    master_thread.join();
    slave1_thread.join();
    slave2_thread.join();

    return EXIT_SUCCESS;
}