#include <iostream>
#include <sstream>
#include <ctime>
#include "ap.h"


using namespace std;


int main (int argc, char *argv[])
{
    unsigned long p;
    int base = 10;
    time_t b;

    if (argc < 2)
    {
        cerr << "USAGE: mprint p [base] [perfect]" << endl;
        cerr << "       Outputs 2^p-1 in base base to stdout" << endl;
        cerr << "       If you add the third parameter, it outputs 2^(p-1)*(2^p-1)" << endl;
        return 2;
    }

    istringstream s (argv[1]);
    if (!(s >> p))
    {
        cerr << "Invalid argument p: " << argv[1] << endl;
        return 1;
    }

    if (argc > 2)
    {
        istringstream s (argv[2]);
        if (!(s >> base))
        {
            cerr << "Invalid argument base: " << argv[2] << endl;
            return 1;
        }
    }

    apbase (base);

    apfloat x = 2;

    b = time (0);

    if (argc < 4)
    {
        cout << pretty << pow (x, p) - 1 << endl;
    }
    else
    {
        x = pow (x, p - 1);

        cout << pretty << x * (x + x - 1) << endl;
    }

    cerr << "Total time " << difftime (time (0), b) << " seconds" << endl;

    return 0;
}
