#include <thread>

#include "timeslave.h"
#include "clock.h"

TimeSlave::TimeSlave(std::string name, int hours, int minutes, int seconds) : _clock{name, hours, minutes, seconds}
{
    printf("asd");
    std::thread t1{_clock};
    t1.detach();

}

void TimeSlave::operator()()
{
}