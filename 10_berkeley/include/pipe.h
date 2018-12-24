#ifndef PIPE_H
#define PIPE_H

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class Pipe
{
    std::queue<T> _backend;
    std::mutex _mtx;
    std::condition_variable _not_empty;
    bool _closed{false};

  public:
    Pipe &operator<<(T value)
    {
        std::lock_guard<std::mutex> lock(_mtx);

        _backend.push(value)

        return *this;
    }

    Pipe &operator>>(T &value)
    {
        std::lock_guard<std::mutex> lock(_mtx);

        T value = _backend.front();
        _backend.pop();

        return *this;
    }

    void close()
    {
        std::lock_guard<std::mutex> lock(_mtx);
        
        _closed = true;
    }

    explicit operator bool()
    {
        std::lock_guard<std::mutex> lock(_mtx);
        
        return _backend.size() > 0;
    }
};
#endif
