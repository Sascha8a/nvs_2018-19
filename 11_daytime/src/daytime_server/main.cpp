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

string get_date_time()
{
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timeinfo);
    std::string str(buffer);

    return str;
}

int main(int argc, char *argv[])
{
    u_short port = 1113;
    bool help = false;

    auto cli = (option("-p").doc("port") & value("port", port),
                option("-h", "--help").doc("help").set(help));
    if (!parse(argc, argv, cli) || help)
    {
        cout << make_man_page(cli, argv[0]);
        exit(0);
    }

    asio::io_context ctx;
    tcp::endpoint ep{tcp::v4(), port};
    tcp::acceptor acceptor{ctx, ep};
    acceptor.listen();
    tcp::socket sock{ctx};

    while (true)
    {
        acceptor.accept(sock);
        tcp::iostream strm{std::move(sock)};
        if (strm)
        {
            spdlog::log(spdlog::level::level_enum::info, "Incoming connection!");
            strm << get_date_time();
            strm.close();
        }
        else
        {
            spdlog::log(spdlog::level::level_enum::err, "Error establishing connection with client!");
        }
    }
}
