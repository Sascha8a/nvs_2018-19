#include <chrono>
#include <iostream>
#include <thread>
#include <tuple>
#include <sstream>

#include "clock.h"
#include "timeutils.h"

Clock::Clock(std::string name, int hours, int minutes, int seconds) : _name{name}
{
    set_time(hours, minutes, seconds);
}

void Clock::operator()()
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        _clock += std::chrono::seconds(1);
        std::stringstream ss;

        ss << _name << " " << _clock << std::endl;
        std::cout << ss.str();
    }
}

void Clock::set_time(int hours, int minutes, int seconds)
{
    _clock = ::set_time(ref(_clock), hours, minutes, seconds);
}

std::tuple<int, int, int> Clock::get_time()
{
    return ::get_time(_clock);
}
