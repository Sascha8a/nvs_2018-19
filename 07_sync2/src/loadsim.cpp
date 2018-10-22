#include <iostream>
#include <thread>
#include <chrono>

#include <WorkQueue.h>

using namespace std;
using namespace std::chrono;

int main() {
    int counter{0};
    WorkQueue q{};

    while(true){
        q.push(WorkPacket(counter));
        cout << "B: Submitted work packet " << counter << endl;
        counter++;

        this_thread::sleep_for(500ms);
    }
}
