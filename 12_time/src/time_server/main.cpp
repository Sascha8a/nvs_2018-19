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

long get_date_time()
{
    return chrono::duration_cast<chrono::seconds>(chrono::system_clock::now().time_since_epoch()).count() + 2208988800;
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
            long time_to_epoch{2208988800};

            uint32_t output;
            spdlog::log(spdlog::level::level_enum::err, "Sending time to server!");
            auto d = std::chrono::system_clock::now().time_since_epoch();
            long timestamp = std::chrono::duration_cast<std::chrono::seconds>(d).count();
            output = timestamp + time_to_epoch;
            output = ntohl(output);
            strm.write(reinterpret_cast<char*>(&output), sizeof(output));
            strm.close();
        }
        else
        {
            spdlog::log(spdlog::level::level_enum::err, "Error establishing connection with client!");
        }
    }
}
