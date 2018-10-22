#include <string>

class Car
{
private:
  std::string _name;

public:
  Car(std::string name);
  void operator()();
};