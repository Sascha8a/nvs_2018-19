#include <iostream>
#include <cmath>
#include "sieve.cpp"

using namespace std;

bool isprime(u_long n)
{
    // Remove all even numbers besides 2
    if (!(n % 2)) {
        return false;
    }

    u_long max = sqrt(n);
    for (u_long i{3}; i <= max; i+=2) {
        if (!(n % i)) {
            return false;
        }
    }

    return true;
}

void verify_arguments(int argc, char* argv[]) {
    if (argc != 3) {
        throw "Please provide a command!";
    }

    string command{argv[1]};

    if (command != "test" && command != "sieve") {
        throw "Please provide a correct command!";
    }

    size_t idx;
    string number{argv[2]};

    try {
        stoul(number, &idx);
    } catch (...) {
        throw "Please provide a natural number (2 <= number <= 2.000.000.000)";
    }

    if (number.size() != idx) {
        throw "Please provide a natural number (2 <= number <= 2.000.000.000)";
    }
}

void check_arguments(int argc, char* argv[]) {
    bool error{false};

    try {
        verify_arguments(argc, argv);
    } catch (char const* e) {
        cout << e << endl;

        error = true;
    }

    if (error) {
        cout << "usage: primes <command> <number>" << endl;
        cout << endl;
        cout << "Commands:" << endl;
        cout << "  test ... test if the given number is prime" << endl;
        cout << "  sieve ... lists all prime numbers up to the given number" << endl;
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char* argv[])
{
    check_arguments(argc, argv);

    string command{argv[1]};
    u_long number{stoul(string(argv[2]))};

    if (command == "test") {
        bool is_prime{isprime(number)};

        if (is_prime) {
            cout << number << " is a prime number" << endl;
        } else {
            cout << number << " is NOT a prime number" << endl;
        }
    } else if (command == "sieve") {
        sieve_and_print(number);
    }

    return 0;
}