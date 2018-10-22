#include <queue>
#include <mutex>
#include "WorkPacket.h"

using namespace std;

class WorkQueue
{
private:
  queue<WorkPacket> _queue{};
  mutex _queue_lock;

public:
  WorkQueue();
  void push(WorkPacket p);
  WorkPacket pop();
};