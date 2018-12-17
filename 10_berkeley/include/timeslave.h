#pragma once

#include <string>

#include "clock.h"

class TimeSlave
{
  private:
    Clock _clock;

  public:
    TimeSlave(std::string name, int hours, int minutes, int seconds);
    void operator()();
};