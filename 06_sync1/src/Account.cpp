#include <Account.hpp>
#include <thread>

using namespace std;

Account::Account(int init_balance)
{
  _balance_lock.lock();
  _balance = init_balance;
  _balance_lock.unlock();
}

int Account::get_balance()
{
  return _balance;
}

void Account::deposit(int amount)
{
  unique_lock<mutex> lock(_balance_lock);

  _balance += amount;
}

bool Account::withdraw(int amount)
{
  lock_guard<mutex> lock(_balance_lock);

  int new_balance{_balance - amount};

  if (new_balance < 0)
  {
    return false;
  }
  else
  {
    this_thread::yield();
    _balance = new_balance;

    return true;
  }
}
