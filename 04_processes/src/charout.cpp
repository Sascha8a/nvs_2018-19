
#include <iostream>
#include <thread>
#include <unistd.h>
#include <chrono>
#include <csignal>

using namespace std;
using namespace chrono;

int main(int argc, char *argv[])
{
  if (argc != 2) {
    return EXIT_FAILURE;
  }

  while (true)
  {
    cout << argv[1] << flush;

    milliseconds sleeptime{500};
    this_thread::sleep_for(sleeptime);
  }
}
