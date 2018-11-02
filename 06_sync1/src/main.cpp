#include <iostream>
#include <iomanip>
#include <thread>

#include "Account.hpp"

using namespace std;

int main() {
  Account a{0};

  // Punkt 1
  // a.deposit(10);
  // a.withdraw(10);
  // cout << a.get_balance() << endl;

  // Punkt 2  
  // thread t1{[&](){a.withdraw(1);}};
  // thread t2{[&](){a.withdraw(1);}};

  // t1.join();
  // t2.join();

  // Punkt 3
  Depositer d1{&a};
  Depositer d2{&a};

  thread t1{d1};
  thread t2{d2};

  t1.join();
  t2.join();

  cout << a.get_balance() << endl;
}
