#include <iostream>
#include <thread>
#include <asio.hpp>

#include "clipp.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#pragma GCC diagnostic pop

using namespace std;
using namespace asio::ip;
using namespace clipp;

uint32_t get_date_time()
{
    auto duration{chrono::system_clock::now().time_since_epoch()};
    auto seconds{chrono::duration_cast<chrono::duration<uint32_t>>(duration).count()};
    seconds += 2208988800;
    return ntohl(seconds);
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
            spdlog::log(spdlog::level::level_enum::info, "Sending time to client!");

            uint32_t date{get_date_time()};
            strm.write(reinterpret_cast<char *>(&date), sizeof(date));
            strm.close();
        }
        else
        {
            spdlog::log(spdlog::level::level_enum::err, "Error establishing connection with client!");
        }
    }
}
