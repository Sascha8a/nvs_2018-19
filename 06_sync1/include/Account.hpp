#include <chrono>
#include <thread>
#include <mutex>

using namespace std;

class Account
{
private:
  int _balance{0};
  mutex _balance_lock;

public:
  Account(int balance);
  int get_balance();
  void deposit(int amount);
  bool withdraw(int amount);
};

class Depositer
{
private:
  Account* _acc;

public:
  Depositer(Account* a) : _acc(a){};

  void operator()()
  {
    for (int i = 0; i < 5; i++)
    {
      this_thread::sleep_for(100ms * i);
      _acc->deposit(1);
    }
  };
};