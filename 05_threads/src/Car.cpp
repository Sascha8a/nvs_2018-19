#include <iostream>
#include <thread>

#include "Car.hpp"

using namespace std;

Car::Car(string name)
{
    _name = name;
}

void Car::operator()()
{
    int laps{0};

    while (true)
    {
        this_thread::sleep_for(1s);
        laps++;
        cout << to_string(laps) + " " + _name + "\n";
    }
}