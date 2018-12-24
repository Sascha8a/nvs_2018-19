#pragma once

#include <string>

#include "clock.h"
#include "channel.h"

class TimeMaster
{
private:
  Clock _clock;
  Channel *_channel1;
  Channel *_channel2;

public:
  TimeMaster(std::string name, int hours, int minutes, int seconds);
  void set_channel1(Channel *c)
  {
    _channel1 = c;
  }
  void set_channel2(Channel *c)
  {
    _channel2 = c;
  }
  void operator()();
};