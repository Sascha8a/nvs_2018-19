/**
 * Author: Alexander Lampalzer <sascha@localhost.systems>
 * Date: 04.08.2018
 * Purpose: Sieve prime numbers
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <thread>
#include <mutex>

using namespace std;

/**
 * Returns the next element, that is true in the vector.
 * @param sieve_arr Array to search through
 * @param n Starting point (inclusive)
 * @param max (inclusive)
 * @return prime if found, 0 otherwise
 */
u_int get_next_prime(vector<bool>* sieve_arr, u_int n, u_int max) {
    for (u_int i = n; i <= max; i++) {
        if (sieve_arr->at(i)) {
            return i;
        }
    }

    return 0;
}

/**
 * Remove all multiples of n in range 0 - max
 * @param sieve_arr Array to remove the multiples from
 * @param sieve_lock Array Mutex
 * @param n Removes multiples of this number
 * @param max Remove all numbers till this numer (incluseive)
 */
void sieve(vector<bool>* sieve_arr, mutex *sieve_lock, u_int n, u_int max=0) {
    for (int i = 2*n; i <= max; i+=n) {
        if (sieve_arr->at(n)) {
            sieve_lock->lock();
            (*sieve_arr)[i] = false;
            sieve_lock->unlock();
        }
    }
}

int sieve_and_print(u_long n) {
    auto sqrt_n = static_cast<u_int>(sqrt(n));
    mutex sieve_lock;
    vector<bool> sieve_arr(n, true);
    vector<thread> threads;

    u_int i{2};
    while (i) {
        sieve(&sieve_arr, &sieve_lock, i, sqrt_n);

        thread t(sieve, &sieve_arr, &sieve_lock, i, n);
        threads.push_back(move(t));

        i = get_next_prime(&sieve_arr, ++i, sqrt_n);
    }

    for (auto &t : threads) {
        t.join();
    }

    cout << "2 ";
    for (int i = 3; i < sieve_arr.size(); i += 2) {
        if (sieve_arr[i]) {
            cout << i << " ";
        }
    }
    cout << endl;

    return 0;
}