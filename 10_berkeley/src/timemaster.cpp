#include <thread>
#include <chrono>

#include "timemaster.h"
#include "clock.h"

TimeMaster::TimeMaster(std::string name, int hours, int minutes, int seconds) : _clock{name, hours, minutes, seconds}
{
    std::thread t1{_clock};
    t1.detach();

}

void TimeMaster::operator()()
{
    _channel1->get_pipe1() << 1.0;
    _channel1->get_pipe1() << 2.0;
    _channel1->get_pipe1() << 3.0;

    _channel2->get_pipe1() << 1.0;
    _channel2->get_pipe1() << 2.0;
    _channel2->get_pipe1() << 3.0;

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    _channel1->get_pipe1().close();
    _channel2->get_pipe1().close();
}