#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

#include "Philosopher.h"
#include "Utils.h"

using namespace std;

bool Philosopher::attempt_get_right_fork()
{
  if (_timeout)
  {
    if (!_right->try_lock_for(chrono::seconds(_timeout)))
    {
      this_thread::sleep_for(100ms);
      _left->unlock();
      Utils::println("Philosoph", to_string(_id), "released left fork due to timeout getting the right one!");
      this_thread::sleep_for(3s);

      return false;
    }
  }
  else
  {
    _right->lock();
  }

  Utils::println("Philosoph", to_string(_id), "got right fork. Now he is eating...");

  return true;
}

void Philosopher::operator()()
{
  while (true)
  {
    Utils::println("Philosoph", to_string(_id), "is thinking...");
    this_thread::sleep_for(1s);

    if (_semph)
    {
      _semph->acquire();
    }

    do
    {
      Utils::println("Philosoph", to_string(_id), "attempts to get left fork");
      _left->lock();
      Utils::println("Philosoph", to_string(_id), "got left fork. Now he wants the right one...");
    } while (!attempt_get_right_fork());

    this_thread::sleep_for(2s);
    _left->unlock();
    Utils::println("Philosoph", to_string(_id), "released left fork");

    if (_semph)
    {
      _semph->release();
    }

    _right->unlock();
    Utils::println("Philosoph", to_string(_id), "released right fork");
  }
}