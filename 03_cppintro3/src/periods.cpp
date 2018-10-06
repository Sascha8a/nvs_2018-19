
#include <iostream>
#include <thread>
#include <vector>

using namespace std;

bool array_elements_equal(vector<string>* arr) {
    string testee{(*arr)[0]};

    for (string &elem : *arr) {
        if (elem != testee) {
            return false;
        }
    }

    return true;
}

bool is_period(size_t segment_size, string* input) {
    int segment_number = input->size() / segment_size;
    vector<string> split_input(segment_number);
    string substr;

    for (int i = 0; i < segment_number; i++) {
        substr = input->substr(i * segment_size, segment_size);
        split_input[i] = substr;
    }

    return array_elements_equal(&split_input);
}

void print_period(string input) {
    const size_t input_size{input.size()};
    size_t divisor{input_size};

    while (divisor != 0) {
        if (input_size % divisor != 0) {
            divisor--;
            continue;
        }

        if (is_period(input_size / divisor, &input)) {
            cout << input_size / divisor << " " << input.substr(0, input_size / divisor) << endl;
            break;
        } else {
            divisor--;
        }
    }
}

int main(int argc, char* args[]) {
    for (int i = 1; i < argc; i++) {
        print_period(string(args[i]));
    }

    return 0;
}
