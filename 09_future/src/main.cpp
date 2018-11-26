#include <iostream>
#include "InfInt.h"

using namespace std;

void usage()
{
    cout << "Usage: factoring [OPTION]... [NUMBER]..." << endl;
    cout << "Options:" << endl;
    cout << "  --help       display this help and exit" << endl;

    exit(EXIT_SUCCESS);
}

void check_arguments(int *argc, const char *argv[])
{

    for (int i = 1; i < *argc; i++)
    {
        if (string(argv[i]) == "--help")
        {
            usage();
            exit(EXIT_FAILURE);
        } else if (string(argv[i]) != InfInt(argv[i]).toString()) {
            cout << argv[i] << " is not a number!" << endl;
            usage();
            exit(EXIT_FAILURE);
        }
    }
}

int main(int argc, const char *argv[])
{
    check_arguments(&argc, argv);
    
}