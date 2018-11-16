#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

#include "Philosopher.h"

using namespace std;

std::recursive_mutex out_mtx;

void println()
{
    std::lock_guard<std::recursive_mutex> lg{out_mtx};
    std::cout << std::endl;
}

template <typename T, typename... Rest>
void println(const T &word, const Rest &... rest)
{
    std::lock_guard<std::recursive_mutex> lg{out_mtx};
    std::cout << word << ' ';
    println(rest...);
}

void Philosopher::operator()()
{
    while (true)
    {
        println("Philosoph", to_string(_id), "is thinking...");
        this_thread::sleep_for(1s);

        println("Philosoph", to_string(_id), "attempts to get left fork");
        _left->lock();

        println("Philosoph", to_string(_id), "got left fork. Now he wants the right one...");
        _right->lock();

        println("Philosoph", to_string(_id), "got right fork. Now he is eating...");
        this_thread::sleep_for(2s);
        _left->unlock();
        println("Philosoph", to_string(_id), "released left fork");

        _right->unlock();
        println("Philosoph", to_string(_id), "released right fork");
    }
}