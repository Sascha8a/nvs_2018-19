#pragma once
#include <mutex>
#include <condition_variable>

class Semaphore
{
private:
  unsigned int _size;
  std::mutex _mtx;
  std::condition_variable _not_empty;

public:
  Semaphore(unsigned int _size);
  Semaphore();
  void acquire();
  void release();
  unsigned int avaliblePermits();
};
