#include <string>
#include <chrono>
#include <random>

class Car
{
private:
  std::mt19937 _rd_gen;
  std::uniform_real_distribution<> _rd_dist;
  void _print_lap(double lap_time, int lap_number);

public:
  Car(std::string name);
  double cumm_lap_time{0};
  std::string _name;
  void operator()();
};