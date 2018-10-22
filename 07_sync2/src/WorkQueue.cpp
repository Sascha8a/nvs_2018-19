#include <queue>
#include <mutex>
#include "WorkQueue.h"

WorkQueue::WorkQueue()
{
}

void WorkQueue::push(WorkPacket p)
{
    lock_guard<mutex> lock(_queue_lock);

    _queue.push(p);
}

WorkPacket WorkQueue::pop()
{
    lock_guard<mutex> lock(_queue_lock);

    WorkPacket tmp = _queue.front();
    _queue.pop();

    return tmp;
}