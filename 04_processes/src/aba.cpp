
#include <iostream>
#include <thread>
#include <unistd.h>
#include <chrono>
#include <csignal>
#include <cstdlib>

using namespace std;
using namespace chrono;

void parent_process(pid_t child_pid1, pid_t child_pid2)
{
    for (int i = 0; i < 6; i++)
    {
        milliseconds sleeptime{500};
        this_thread::sleep_for(sleeptime);
    }

    kill(child_pid1, SIGKILL);
    kill(child_pid2, SIGKILL);
    cout << endl;
}

void child_process(string str)
{
    execl("./charout", "./charout", str.c_str(), 0);
}

int main()
{
    const char* letter_a{getenv("ABA_LETTER_A") ? getenv("ABA_LETTER_A") : "A"};
    const char* letter_b{getenv("ABA_LETTER_B") ? getenv("ABA_LETTER_B") : "B"};

    auto pid1 = fork();

    if (pid1 == 0)
    {
        child_process(letter_a);
    }
    else
    {
        auto pid2 = fork();

        if (pid2 == 0)
        {
            child_process(letter_b);
        }

        parent_process(pid1, pid2);
    }
}
