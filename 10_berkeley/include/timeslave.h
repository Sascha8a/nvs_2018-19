#pragma once

#include <string>

#include "clock.h"
#include "channel.h"

class TimeSlave
{
private:
  Clock _clock;
  Channel *_channel;
  std::string _name;

public:
  TimeSlave(std::string name, int hours, int minutes, int seconds, bool monotone);
  void set_clock_speed(int speed)
  {
    _clock.set_clock_speed_offset(speed);
  }
  Channel *get_channel()
  {
    return _channel;
  }
  void operator()();
};