#ifndef CALC_FACTORS_H
#define CALC_FACTORS_H

// ko
// adapted from M. Gallant  1/98

#include <vector>

#include "InfInt.h"

inline std::vector<InfInt> get_factors(InfInt number) { // number should be positive
    std::vector<InfInt> factors;
    while (number % 2 == InfInt::zero) {
        number = number / 2;
        factors.push_back(InfInt::two);
    }
    InfInt limit = number.intSqrt() + InfInt::one;
    
 factor:
    for (InfInt i=3; i <= limit; i = i + InfInt::two) {
        while (number % i == 0) {
            number = number / i;
            factors.push_back(i);
            if (number == InfInt::one)
                goto factor;
            limit = number.intSqrt() + InfInt::one;
        }
    }

    if (number != InfInt::zero || factors.size() == 0)
        factors.push_back(number);
    return factors;
}
#endif
