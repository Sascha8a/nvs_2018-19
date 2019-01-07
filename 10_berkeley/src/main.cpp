#include <thread>
#include <iostream>

#include "clock.h"
#include "timeslave.h"
#include "timemaster.h"
#include "clipp.h"

using namespace std;
using namespace clipp;

int main(int argc, char *argv[])
{
    bool monotone{false};
    bool help{false};

    bool delay{false};
    int delayS1{};
    int delayS2{};

    bool rate = false;
    int rateM{0};
    int rateS1{0};
    int rateS2{0};

    auto cli = (option("-h", "--help").set(help).doc("show this help"),
                option("-m").set(monotone).doc("monoton (kein Zurückstellen der Uhren)"),
                option("-d").set(delay).doc("Verzögerungen in ms (d.h. Latenz der Verbindung zu jeweiligen Slave)") & value("delay1", delayS1) & value("delay2", delayS2),
                option("-r").set(rate).doc("Abweichungen vom Sekundentakt in ms (der jeweiligen Uhr, d.h. Ungenauigkeit)") & value("rateM", rateM) & value("rate1", rateS1) & value("rate2", rateS2));

    if (!parse(argc, argv, cli) || help)
    {
        std::cout << make_man_page(cli, argv[0]);
        exit(0);
    }

    // Clock clock("REAL", 0, 0, 1);
    TimeMaster master{"Master", 0, 0, 5, monotone};
    TimeSlave slave1{"Slave1", 0, 0, 10, monotone};
    TimeSlave slave2{"Slave2", 0, 0, 15, monotone};

    slave1.get_channel()->set_latency(delayS1);
    slave2.get_channel()->set_latency(delayS2);

    master.set_clock_speed(rateM);
    slave1.set_clock_speed(rateS1);
    slave2.set_clock_speed(rateS2);

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