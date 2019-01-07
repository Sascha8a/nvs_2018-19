#include <thread>

#include "clock.h"
#include "timeslave.h"
#include "timemaster.h"

using namespace std;

bool contains(int argc, const char *argv[], string str)
{

    for (int i = 1; i < argc; i++)
    {
        auto converted = string(argv[i]);
        if (converted.find_first_of(str))
        {
            return true;
        }
    }

    return false;
}

int main(int argc, const char *argv[])
{
    bool monotone{false};

    if (contains(argc, argv, "-h") || contains(argc, argv, "--help"))
    {
        printf("Usage: berkeley [-h] [-m] [-d<delay1>,<delay2>] [-r<rateM>,<rate1>,<rate2>]\n");
        printf("Options:\n");
        printf("  -h|--help help\n");
        printf("  -m        monoton (kein Zurückstellen der Uhren)\n");
        printf("  -d        Verzögerungen in ms (d.h. Latenz der Verbindung zu jeweiligen Slave)\n");
        printf("  -r        Abweichungen vom Sekundentakt in ms (der jeweiligen Uhr,\n");
        printf("            d.h. Ungenauigkeit)\n");
        exit(EXIT_SUCCESS);
    }

    if (contains(argc, argv, "-m"))
    {
        monotone = true;
    }

    if (contains(argc, argv, "-d"))
    {
        for (int i = 1; i < argc; i++)
        {
            auto converted = string(argv[i]);
            if (converted.find_first_of("-d"))
            {
                
            }
        }
    }

    // Clock clock("REAL", 0, 0, 1);
    TimeMaster master{"Master", 0, 0, 5, monotone};
    TimeSlave slave1{"Slave1", 0, 0, 10, monotone};
    TimeSlave slave2{"Slave2", 0, 0, 15, monotone};

    slave1.get_channel()->set_latency(100);
    slave2.get_channel()->set_latency(200);

    master.set_channel1(slave1.get_channel());
    master.set_channel2(slave2.get_channel());

    thread clock_thread{std::ref(clock)};
    thread master_thread{std::ref(master)};
    thread slave1_thread{std::ref(slave1)};
    thread slave2_thread{std::ref(slave2)};

    clock_thread.join();
    master_thread.join();
    slave1_thread.join();
    slave2_thread.join();

    return EXIT_SUCCESS;
}