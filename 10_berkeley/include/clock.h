#pragma once

#include <string>
#include <chrono>
#include <tuple>

class Clock
{
  private:
    std::string _name;
    std::chrono::time_point<std::chrono::system_clock> _clock{std::chrono::system_clock::now()};

  public:
    Clock(std::string name) : _name{name} {};
    Clock(std::string name, int hours, int minutes, int seconds);
    void set_time(int hours, int minutes, int seconds);
    std::tuple<int, int, int> get_time();
    long to_time();
    void from_time(long time);
    void operator()();
};