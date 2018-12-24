#include <thread>

#include "timemaster.h"
#include "clock.h"

TimeMaster::TimeMaster(std::string name, int hours, int minutes, int seconds) : _clock{name, hours, minutes, seconds}
{
    printf("asd");
    std::thread t1{_clock};
    t1.detach();

}

void TimeMaster::operator()()
{
}