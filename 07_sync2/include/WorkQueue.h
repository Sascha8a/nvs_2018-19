#include <queue>
#include <mutex>
#include <condition_variable>
#include "WorkPacket.h"

using namespace std;

class WorkQueue
{
private:
  unsigned int _size;
  queue<WorkPacket> _queue{};
  mutex _queue_lock;
  condition_variable _queue_not_empty;
  condition_variable _queue_not_full;

public:
  WorkQueue(unsigned int size) : _size(size){};
  void push(WorkPacket p);
  WorkPacket pop();
};