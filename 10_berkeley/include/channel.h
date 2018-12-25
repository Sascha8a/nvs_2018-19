#pragma once

#include "pipe.h"

class Channel
{
private:
  Pipe<long> _pipe1;
  Pipe<long> _pipe2;

public:
  Channel() {}

  Pipe<long> &get_pipe1()
  {
    return _pipe1;
  }

  Pipe<long> &get_pipe2()
  {
    return _pipe2;
  }

  void set_latency(long latency)
  {
    _pipe1.set_latency(latency);
    _pipe2.set_latency(latency);
  }
};