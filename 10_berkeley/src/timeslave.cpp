#include <thread>
#include <iostream>

#include "timeslave.h"
#include "clock.h"

TimeSlave::TimeSlave(std::string name, int hours, int minutes, int seconds) : _clock{name, hours, minutes, seconds}, _name{name}
{
    std::thread t1{_clock};
    t1.detach();

    _channel = new Channel();
}

void TimeSlave::operator()()
{
    while (_channel->get_pipe1())
    {
        long value;
        _channel->get_pipe1() >> value;
        std::cout << _name + " received: " + std::to_string(value) + "\n" << std::flush;
    }
}