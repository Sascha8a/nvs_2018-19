#include <thread>

#include "clock.h"

using namespace std;

int main()
{
    thread clock{Clock("testClock")};
    clock.join();

    return EXIT_SUCCESS;
}