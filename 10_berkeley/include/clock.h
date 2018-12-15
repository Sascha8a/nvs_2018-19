#pragma once

#include <string>
#include <chrono>

class Clock
{
  private:
    std::string _name;
    std::chrono::time_point<std::chrono::system_clock> _clock{std::chrono::system_clock::now()};

  public:
    Clock(std::string name) : _name{name} {};
    void operator()();
};