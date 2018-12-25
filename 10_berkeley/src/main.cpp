#include <thread>

#include "clock.h"
#include "timeslave.h"
#include "timemaster.h"

using namespace std;

int main()
{
    // Clock clock("REAL", 0, 0, 1);
    TimeMaster master{"Master", 0, 0, 5};
    TimeSlave slave1{"Slave1", 0, 0, 10};
    TimeSlave slave2{"Slave2", 0, 0, 15};

    slave1.get_channel()->set_latency(100);
    slave2.get_channel()->set_latency(200);

    master.set_channel1(slave1.get_channel());
    master.set_channel2(slave2.get_channel());

    thread clock_thread{std::ref(clock)};
    thread master_thread{std::ref(master)};
    thread slave1_thread{std::ref(slave1)};
    thread slave2_thread{std::ref(slave2)};
    
    clock_thread.join();
    master_thread.join();
    slave1_thread.join();
    slave2_thread.join();

    return EXIT_SUCCESS;
}