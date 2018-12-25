#include <thread>
#include <chrono>
#include <iostream>

#include "timemaster.h"
#include "clock.h"

TimeMaster::TimeMaster(std::string name, int hours, int minutes, int seconds) : _clock{name, hours, minutes, seconds}
{
    std::thread t1{std::ref(_clock)};
    t1.detach();
}

void TimeMaster::berkeley_sync()
{
    std::cout << "Berkeley sync started: " + std::to_string(_clock.to_time()) + "\n" << std::flush;

    long slave1_time;
    long slave2_time;
    long self_time;

    _channel1->get_pipe1() << -1;
    _channel2->get_pipe1() << -1;

    self_time = _clock.to_time();
    _channel1->get_pipe2() >> slave1_time;
    _channel2->get_pipe2() >> slave2_time;

    long new_time{(self_time + slave1_time + slave2_time) / 3};
    
    _clock.from_time(new_time);
    _channel1->get_pipe1() << new_time;
    _channel2->get_pipe1() << new_time;
}

void TimeMaster::operator()()
{
    while (true)
    {
        berkeley_sync();
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }
}