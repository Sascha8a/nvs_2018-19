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
        std::stringstream ss;
        ss << _name << " " << _clock << std::endl;
        std::cout << ss.str();

        std::this_thread::sleep_for(std::chrono::seconds(1) + std::chrono::milliseconds(_monoton_offset) + std::chrono::milliseconds(_offset));
        this->_clock += std::chrono::seconds(1);
    }
}

void Clock::set_time(int hours, int minutes, int seconds)
{
    _clock = ::set_time(ref(_clock), hours, minutes, seconds);
}

void Clock::set_time_monoton(bool val)
{
    _monoton = val;
}

void Clock::set_clock_speed_offset(long ms)
{
    _offset = ms;
}

std::tuple<int, int, int> Clock::get_time()
{
    return ::get_time(_clock);
}

long Clock::to_time()
{
    return std::chrono::system_clock::to_time_t(_clock);
}

void Clock::from_time(long new_time)
{
    std::cout << _name + " time update: " + std::to_string(new_time) + "\n"
              << std::flush;

    if (_monoton && (to_time() > new_time))
    {
        _monoton_offset = 100;
    } else {
        _clock = std::chrono::system_clock::from_time_t(new_time);
    }
}