#include <chrono>
#include <iostream>
#include <thread>

#include "clock.h"
#include "timeutils.h"

void Clock::operator()()
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        _clock += std::chrono::seconds(1);
        std::cout << _clock << std::endl;
    }
}