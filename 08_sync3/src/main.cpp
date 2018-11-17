#include <iostream>
#include <mutex>
#include <thread>

#include "Philosopher.h"
#include "Semaphore.h"

using namespace std;

void usage(string msg = "")
{
  if (msg != "")
  {
    cout << "Error: unrecognized command line option '" << msg << "'" << endl;
  }
  cout << "Usage: dining [OPTION]..." << endl;
  cout << "Options:" << endl;
  cout << "  --nodeadlock   enable deadlock prevention" << endl;
  cout << "  --livelock     enable deadlock prevention" << endl;
  cout << "  --help         display this help and exit" << endl;
}

void check_args(int *argc, const char *argv[])
{
  if (*argc > 2)
  {
    usage();
    exit(EXIT_FAILURE);
  }

  if (string(argv[1]) == "--help")
  {
    usage();
    exit(EXIT_FAILURE);
  }

  if (string(argv[1]) != "--livelock" && string(argv[1]) != "--nodeadlock")
  {
    usage(argv[1]);
    exit(EXIT_FAILURE);
  }
}

bool has_arg(string arg, int *argc, const char *argv[])
{
  if (*argc == 1)
  {
    return false;
  }

  return argv[1] == arg;
}

int main(int argc, const char *argv[])
{
  check_args(&argc, argv);

  bool no_deadlock{has_arg("--nodeadlock", &argc, argv)};
  bool livelock{has_arg("--livelock", &argc, argv)};

  timed_mutex f1;
  timed_mutex f2;
  timed_mutex f3;
  timed_mutex f4;

  Semaphore *smph;
  u_int timeout;

  if (no_deadlock)
  {
    smph = new Semaphore{3};
  }
  else
  {
    smph = nullptr;
  }

  if (livelock)
  {
    timeout = 3;
  }
  else
  {
    timeout = 0;
  }

  Philosopher p1{1, &f1, &f2, smph, timeout};
  Philosopher p2{2, &f2, &f3, smph, timeout};
  Philosopher p3{3, &f3, &f4, smph, timeout};
  Philosopher p4{4, &f4, &f1, smph, timeout};

  thread t1{ref(p1)};
  thread t2{ref(p2)};
  thread t3{ref(p3)};
  thread t4{ref(p4)};

  t1.join();
  t2.join();
  t3.join();
  t4.join();
}