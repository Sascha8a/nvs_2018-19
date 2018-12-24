#pragma once

#include <string>

#include "clock.h"

class TimeMaster
{
  private:
    Clock _clock;

  public:
    TimeMaster(std::string name, int hours, int minutes, int seconds);
    void operator()();
};