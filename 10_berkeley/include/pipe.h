#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>
#include <future>

template <typename T>
class Pipe
{
  private:
    std::queue<T> _backend;
    std::mutex _mtx;
    std::condition_variable _not_empty;
    long _latency{0};
    bool _closed{false};

  public:
    Pipe &operator<<(T value)
    {
        std::future<void> fut{std::async([&] {
            if (_latency)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(_latency));
            }
            std::lock_guard<std::mutex> lock(_mtx);
            _backend.push(value);
            _not_empty.notify_one();
        })};

        fut.wait();

        return *this;
    }

    Pipe &operator>>(T &value)
    {
        if (_closed)
        {
            return *this;
        }

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

    void set_latency(long latency)
    {
        _latency = latency;
    }
};
