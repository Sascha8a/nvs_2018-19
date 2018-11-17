#include <mutex>
#include <thread>

#include "Semaphore.h"

using namespace std;

class Philosopher
{
private:
  u_int _id;
  timed_mutex *_left;
  timed_mutex *_right;
  Semaphore *_semph;
  u_int _timeout;

  bool attempt_get_right_fork();

public:
  Philosopher(u_int id, timed_mutex *left, timed_mutex *right, Semaphore *semph = nullptr, u_int timeout = 0) : _id{id}, _left{left}, _right{right}, _semph{semph}, _timeout{timeout} {};
  void operator()();
};