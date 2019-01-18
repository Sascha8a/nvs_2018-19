#include <iostream>
#include <thread>

#include <spdlog/spdlog.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wconversion"
#include "asio.hpp"
#pragma GCC diagnostic pop

using namespace std;
using namespace asio::ip;

int main()
{
    tcp::iostream strm{"localhost", "1133"};
    if (strm)
    {
        strm << endl;

        string data;
        getline(strm, data);
        cout << data << endl;
        spdlog
            strm.close();
    }
    else
    {
        spdlog::log(::level::level_enum::err, "Could not connect to server!");
    }
}
