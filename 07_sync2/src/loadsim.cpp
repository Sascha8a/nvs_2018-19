#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <unistd.h>

#include <WorkQueue.h>

using namespace std;
using namespace std::chrono;

void worker(int id, WorkQueue &q)
{
    while (true)
    {
        printf("W%i: Want work packet\n", id);
        WorkPacket p{q.pop()};
        printf("W%i: Got work packet %i\n", id, p.get_id());

        double duration = rand() % (10 - 1 + 1) + 1;
        usleep(duration * 1000000);

        printf("W%i: Processed work packet %i (%4.3fs)\n", id, p.get_id(), duration);
    }
}

void boss(WorkQueue &q)
{
    int counter{0};

    while (true)
    {
        printf("B: Waiting to submit work packet %i\n", counter);

        chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();

        q.push(WorkPacket{counter});
        double rd = rand() / double(RAND_MAX);
        usleep(rd * 1000000);

        chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();

        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

        printf("B: Submitted work packet %i (%4.3fs)\n", counter, duration / 1000.0);

        counter++;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        return 1;
    }

    unsigned int size = stoi(argv[1]);
    WorkQueue q{size};
    std::default_random_engine rd_engine;

    thread b1{boss, ref(q)};
    thread w1{worker, 1, ref(q)};
    thread w2{worker, 2, ref(q)};
    thread w3{worker, 2, ref(q)};

    b1.join();
    w1.join();
    w2.join();
    w3.join();

    return EXIT_SUCCESS;
}
