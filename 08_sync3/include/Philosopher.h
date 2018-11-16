#include <mutex>
#include <thread>

using namespace std;

class Philosopher
{
  private:
    int _id;
    mutex *_left;
    mutex *_right;

  public:
    Philosopher(int id, mutex *left, mutex *right) : _id(id), _left(left), _right(right){};
    void operator()();
};