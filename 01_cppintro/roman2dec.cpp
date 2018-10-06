#include <iostream>

int romanToInt(char roman) {
    int result{0};

    switch (roman) {
        case 'M':
            result = 1000;
            break;

        case 'D':
            result = 500;
            break;

        case 'C':
            result = 100;
            break;

        case 'L':
            result = 50;
            break;

        case 'X':
            result = 10;
            break;

        case 'V':
            result = 5;
            break;

        case 'I':
            result = 1;
            break;

        default:
            std::cout << "invalid roman number!" << std::endl;
            exit(EXIT_FAILURE);
    }

    return result;
}

int romanToInt(std::string roman) {
    int prev{0};
    int result{0};

    for (char c : roman) {
        int val{romanToInt(c)};

        result += (prev < val) ? val - 2 * prev : val;

        prev = val;
    }

    return result;
}

int main() {
    std::cout << romanToInt("MA") << std::endl;

    return 0;
}
