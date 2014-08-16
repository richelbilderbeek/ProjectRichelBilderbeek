#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <ctime>
#include "ap.h"


using namespace std;


// Program for testing disk I/O speed

int main (int argc, char *argv[])
{
    int t, n, u;
    time_t b;

    if (argc < 2)
    {
        cerr << "USAGE: disktest t" << endl;
        return 2;
    }

    istringstream s (argv[1]);

    if (!(s >> n))
    {
        cerr << "Invalid argument t: " << argv[1] << endl;
        return 1;
    }

    n = 1 << n;

    fstream d (filename (fno++), ios::in | ios::out | ios::BIN | ios::trunc);

    modint *data = new modint[Maxblocksize];

    u = Maxblocksize;
    if (u > n) u = n;

    cout << "Write " << sizeof (modint) * n << " bytes:" << endl;

    b = time (0);

    for (t = 0; t < n / u; t++)
        d.write ((char *) data, sizeof (modint) * u);

    cout << "Seconds: " << difftime (time (0), b) << endl;

    d.seekg (0);

    cout << "Read " << sizeof (modint) * n << " bytes:" << endl;

    b = time (0);

    for (t = 0; t < n / u; t++)
        d.read ((char *) data, sizeof (modint) * u);

    b = time (0) - b;

    cout << "Seconds: " << b / 18.20648 << endl;

    delete[] data;

    d.close ();

    remove (filename (--fno));

    return 0;
}
