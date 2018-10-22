#include <iostream>
#include <thread>

#include "Car.hpp"

using namespace std;

int main() {
    Car c = Car("VW Golf 5 ");
    thread c1{c};
    c1.join();
}
