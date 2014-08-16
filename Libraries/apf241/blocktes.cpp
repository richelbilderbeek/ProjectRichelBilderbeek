#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include "ap.h"


using namespace std;


// Program for testing a suitable Cacheblocksize

int main (int argc, char *argv[])
{
    int t, r, n, n1, n2, m = 1;
    time_t b;

    if (argc < 2)
    {
        cerr << "USAGE: block t [b [m]]" << endl;
        return 2;
    }

    istringstream s (argv[1]);

    if (!(s >> n))
    {
        cerr << "Invalid argument t: " << argv[1] << endl;
        return 1;
    }

    n = 1 << n;

    if (argc > 2)
    {
        istringstream s (argv[2]);

        if (!(s >> r))
        {
            cerr << "Invalid argument r: " << argv[2] << endl;
            return 1;
        }

        r = 1 << r;
    }
    else
        r = Cacheblocksize;

    if (argc > 3)
    {
        istringstream s (argv[3]);

        if (!(s >> m))
        {
            cerr << "Invalid argument m: " << argv[3] << endl;
            return 1;
        }
    }

    for (n1 = 1, n2 = 0; n1 < n; n1 <<= 1, n2++);
    n1 = n2 >> 1;
    n2 -= n1;

    n1 = 1 << n1;
    n2 = 1 << n2;

    modint *d = new modint[n];

    if (!d)
    {
        cerr << "Out of memory" << endl;
        return 1;
    }

    cout << "Data size: " << n << endl;
    cout << "Matrix size: " << n1 << " x " << n2 << endl;
    cout << "Block size: " << r << endl;
    cout << "Times: " << m << endl;

    for (t = 0; t < n; t++)
        d[t] = t + 1;

    b = time (0);

    for (t = 0; t < m; t++)
        transpose (d, n1, n2);

    cout << "Seconds: " << difftime (time (0), b) / m << endl;

    delete[] d;

    return 0;
}
