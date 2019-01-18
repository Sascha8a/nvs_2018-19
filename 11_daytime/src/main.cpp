#include <iostream>
#include <thread>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wconversion"
#include "asio.hpp"
#pragma GCC diagnostic pop

using namespace std;
using namespace asio::ip;

int main() {
    tcp::iostream strm{"localhost", "1133"};
    if (strm) {
        strm << endl;

        string data;
        getline(strm, data);
        cout << data << endl;
        
        strm.close();
    } else {
        cout << "Failed to establish connection";
    }
}
