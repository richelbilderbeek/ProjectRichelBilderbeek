#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdio>
#include <ctime>
#include "ap.h"


using namespace std;


// Program for testing the disk fnt functions

int main (int argc, char *argv[])
{
    int t, r, n, u, i = 1, m = 0, p = 0;
    time_t b;
    modint pr, q;

    if (argc < 2)
    {
        cerr << "USAGE: fnt t [sign] [method] [print]" << endl;
        return 2;
    }

    istringstream s (argv[1]);

    if (!(s >> n))
    {
        cerr << "Invalid argument t: " << argv[1] << endl;
        return 1;
    }

    if (argc > 2)
    {
        istringstream s (argv[2]);

        if (!(s >> i))
        {
            cerr << "Invalid argument sign: " << argv[2] << endl;
            return 1;
        }
    }

    if (argc > 3)
    {
        istringstream s (argv[3]);

        if (!(s >> m))
        {
            cerr << "Invalid argument method: " << argv[3] << endl;
            return 1;
        }
    }

    if (argc > 4)
    {
        istringstream s (argv[4]);

        if (!(s >> p))
        {
            cerr << "Invalid argument print: " << argv[4] << endl;
            return 1;
        }
    }

    n = 1 << n;

    setmodulus (moduli[0]);

    pr = primitiveroots[0];

    cout << "Size: " << n << endl;
    cout << "Modulus: " << modint::modulus << endl;
    cout << "Primitive root: " << pr << endl;
    cout << "Sign: " << i << endl;
    cout << "Method: ";
    switch (m)
    {
        case 0: cout << "\"Two-pass\" Table Cooley-Tukey (itabletwopass)" << endl;
                break;
        case 1: cout << "\"Two-pass\" Table Sande-Tukey (tabletwopass)" << endl;
                break;
        case 2: cout << "\"Two-pass\" Table Sande-Tukey (tabletwopasstrans) w/o transposition" << endl;
                break;
        case 3: cout << "\"Two-pass\" Table (i/tabletwopasstrans) & inverse" << endl;
                break;
    }

    b = time (0);

    fstream d (filename (fno++), ios::in | ios::out | ios::BIN | ios::trunc);

    modint *data = new modint[Maxblocksize];

    u = Maxblocksize;
    if (u > n) u = n;
    q = 0;

    for (t = 0; t < n / u; t++)
    {
        for (r = 0; r < u; r++)
            data[r] = ++q;
        d.write ((char *) data, sizeof (modint) * u);
    }

    delete[] data;

    switch (m)
    {
        case 0: itabletwopassfnt (d, pr, i, n);
                break;
        case 1: tabletwopassfnt (d, pr, i, n);
                break;
        case 2: tabletwopassfnttrans (d, pr, i, n);
                break;
        case 3: tabletwopassfnttrans (d, pr, i, n);
                itabletwopassfnttrans (d, pr, -i, n);
                break;
    }

    cout << "Seconds: " << difftime (time (0), b) << endl;

    cout << endl;

    d.seekg (0);

    if (p)
    {
        modint *data = new modint[Maxblocksize];

        u = Maxblocksize;
        if (u > n) u = n;

        for (t = 0; t < n / u; t++)
        {
            d.read ((char *) data, sizeof (modint) * u);

            for (r = 0; r < u; r++)
            {
                cout << setw (16) << data[r];
                if ((r & 3) == 3)
                    cout << endl;
            }
        }
        delete[] data;
    }

    clearmodulus ();

    d.close ();

    remove (filename (--fno));

    return 0;
}
