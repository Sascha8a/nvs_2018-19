#include <queue>
#include <mutex>
#include <iostream>
#include <condition_variable>

#include "WorkQueue.h"

void WorkQueue::push(WorkPacket p)
{
    unique_lock<mutex> lock(_queue_lock);
    _queue_not_full.wait(lock, [this] { return _queue.size() < _size; });

    _queue.push(p);
    _queue_not_empty.notify_one();
}

WorkPacket WorkQueue::pop()
{
    unique_lock<mutex> lock(_queue_lock);
    _queue_not_empty.wait(lock, [this] { return _queue.size() > 0; });

    WorkPacket ret{_queue.front()};
    _queue.pop();
    _queue_not_full.notify_one();

    return ret;
}