#include <iostream>
#include <iomanip>
#include <thread>

#include "Car.hpp"

using namespace std;

int main() {
    Car lada{"Lada Riva"};
    Car moskvich{"Moskvich 408"};

    thread t1{ref(lada)};
    thread t2{ref(moskvich)};

    t1.join();
    t2.join();

    Car winner{lada};
    Car looser{moskvich};
    if (looser.cumm_lap_time < winner.cumm_lap_time) swap(winner, looser);

    cout << "Sieger ist: " << winner._name << " mit ";
    cout << setprecision(3) << winner.cumm_lap_time << "s" << endl;
    cout << "Verlierer ist: " << looser._name << " mit ";
    cout << setprecision(3) << looser.cumm_lap_time << "s" << endl;
}
