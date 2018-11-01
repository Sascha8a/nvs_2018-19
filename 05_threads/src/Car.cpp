#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <random>

#include "Car.hpp"

using namespace std;

Car::Car(string name)
{
    _name = name;
    std::random_device _rd_device;
    _rd_gen = std::mt19937(_rd_device());
    _rd_dist = std::uniform_real_distribution<>(1, 9);
}

void Car::_print_lap(double lap_time, int lap_number)
{
    ostringstream buf;
    buf << lap_number << " " << _name << ": ";
    buf << setprecision(3) << lap_time << "s";
    buf << endl;

    cout << buf.str() << flush;
}

void Car::operator()()
{
    int laps{0};

    while (laps < 1)
    {
        double lap_duration{_rd_dist(_rd_gen)};
        const unsigned long sleep_time{static_cast<unsigned long>(lap_duration * 1000)};
        this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
        laps++;
        cumm_lap_time += lap_duration;

        _print_lap(lap_duration, laps);
    }
}