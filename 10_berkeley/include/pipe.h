#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class Pipe
{
  private:
    std::queue<T> _backend;
    std::mutex _mtx;
    std::condition_variable _not_empty;
    bool _closed{false};

  public:
    Pipe &operator<<(T value)
    {
        std::lock_guard<std::mutex> lock(_mtx);

        _backend.push(value);

        _not_empty.notify_one();
        return *this;
    }

    Pipe &operator>>(T &value)
    {
        std::unique_lock<std::mutex> lock{_mtx};
        _not_empty.wait(lock, [this] { return _backend.size() > 0; });

        value = _backend.front();
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

        return !_closed;
    }
};
