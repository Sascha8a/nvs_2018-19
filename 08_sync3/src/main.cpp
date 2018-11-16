#include <mutex>
#include <thread>

#include "Philosopher.h"

using namespace std;

int main()
{
    mutex f1;
    mutex f2;

    Philosopher p1{1, &f1, &f2};
    Philosopher p2{2, &f2, &f1};

    thread t1{ref(p1)};
    thread t2{ref(p2)};

    t1.join();
    t2.join();
}