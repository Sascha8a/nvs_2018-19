#include <condition_variable>
#include <mutex>

#include "Semaphore.h"
#include "Utils.h"

Semaphore::Semaphore() : _size(1)
{
}

Semaphore::Semaphore(unsigned int size) : _size(size)
{
}

void Semaphore::acquire()
{
  std::unique_lock<std::mutex> lock{_mtx};
  _not_empty.wait(lock, [this] { return _size > 0; });

  --_size;

  Utils::println("Currently ", std::to_string(_size), " left forks available");
}

void Semaphore::release()
{
  std::unique_lock<std::mutex> lock(_mtx);

  ++_size;

  Utils::println("Currently ", std::to_string(_size), " left forks available");
  _not_empty.notify_one();
}

unsigned int Semaphore::avaliblePermits()
{
  return _size;
}