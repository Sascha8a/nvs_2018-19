#include <thread>
#include <iostream>

#include "timeslave.h"
#include "clock.h"

TimeSlave::TimeSlave(std::string name, int hours, int minutes, int seconds, bool monotone) : _clock{name, hours, minutes, seconds}, _name{name}
{
    _clock.set_time_monoton(monotone);
    std::thread t1{std::ref(_clock)};
    t1.detach();

    _channel = new Channel();
}

void TimeSlave::operator()()
{
    long new_time;

    while (_channel->get_pipe1() >> new_time)
    {
        if (new_time > 0) {
            _clock.from_time(new_time);
        } else {
            std::cout << _name + " time request: " + std::to_string(_clock.to_time()) + "\n" << std::flush;
            _channel->get_pipe2() << _clock.to_time();
        }
    }
}