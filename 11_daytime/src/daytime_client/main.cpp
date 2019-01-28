#include <iostream>
#include <thread>

#include <spdlog/spdlog.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wconversion"
#include "asio.hpp"
#include "clipp.h"
#pragma GCC diagnostic pop

using namespace std;
using namespace asio::ip;
using namespace clipp;

int main(int argc, char *argv[])
{
    string port = "1113";
    bool help = false;

    auto cli = (option("-p").doc("port") & value("port", port),
                option("-h", "--help").doc("help").set(help));
    if (!parse(argc, argv, cli) || help)
    {
        cout << make_man_page(cli, argv[0]);
        exit(0);
    }

    tcp::iostream strm{"localhost", port};
    if (strm)
    {
        strm << endl;
        spdlog::log(spdlog::level::level_enum::info, "Connected to server!");

        string data;
        getline(strm, data);
        if (strm)
        {
            cout << data << endl;
        }
        else
        {
            spdlog::log(spdlog::level::level_enum::err, strm.error().message());
        }
        strm.close();

        return 0;
    }
    else
    {
        spdlog::log(spdlog::level::level_enum::err, "Could not connect to server!");

        return 1;
    }
}
