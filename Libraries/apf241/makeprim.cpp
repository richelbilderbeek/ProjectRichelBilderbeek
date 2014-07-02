#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>


using namespace std;


// Program to make the primetab file using Erasthothenes' sieve

// CEXT should be defined in the makefile
#ifndef CEXT
#define CEXT ".cpp"
#endif

int isprime (unsigned d[], unsigned n)
{
    if (n == 2) return 1;
    if (!(n & 1)) return 0;

    return d[n / (2 * 8 * sizeof (unsigned))] & (1 << ((n >> 1) & (8 * sizeof (unsigned) - 1)));
}

unsigned nextprime (unsigned d[], unsigned n)
{
    if (n < 2) return 2;
    if (!(n & 1)) n--;
    while (!isprime (d, n += 2));

    return n;
}

void setcomposite (unsigned d[], int n)
{
    d[n / (2 * 8 * sizeof (unsigned))] &= ~(1 << ((n >> 1) & (8 * sizeof (unsigned) - 1)));
}

unsigned *initprimetable (unsigned n)
{
    unsigned l, t, i, r;

    l = (n + 2 * 8 * sizeof (unsigned) - 1) / 2 / (8 * sizeof (unsigned));

    unsigned *d = new unsigned[l];

    if (!d)
    {
        cerr << "Out of memory" << endl;
        return 0;
    }

    for (t = 0; t < l; t++)
        d[t] = (unsigned) -1;

    r = (unsigned) sqrt ((double) n);

    t = 3;
    d[0] -= 1;

    while (t <= r)
    {
        for (i = 3 * t; i <= n; i += 2 * t)
            setcomposite (d, i);

        t = nextprime (d, t);
    }

    return d;
}

unsigned factor (unsigned d[], unsigned f[], unsigned n)
{
    unsigned t = 2, r, i = 0;

    r = (unsigned) sqrt ((double) n);

    while (t <= r)
    {
        while (!(n % t))
        {
            n /= t;
            f[i++] = t;
            r = (unsigned) sqrt ((double) n);
        }
        t = nextprime (d, t);
    }

    if (n != 1) f[i++] = n;

    return i;
}

int main (int argc, char *argv[])
{
    unsigned n, t, *d, i;

    if (argc != 2)
    {
        cerr << "USAGE: makeprim n" << endl;
        return 2;
    }

    istringstream s (argv[1]);

    if (!(s >> n))
    {
        cerr << "Invalid argument n: " << argv[1] << endl;
        return 1;
    }

    d = initprimetable (n);

    ofstream o ("primetab"CEXT);

    if (o.fail ())
    {
        cerr << "Unable to open file primetab"CEXT << endl;
        return 1;
    }

    o << "#include \"ap.h\"" << endl << endl;
    o << "rawtype primetable[] =" << endl << "{" << endl;

    o << "\t2";

    for (t = 3, i = 1; t <= n; t = nextprime (d, t))
        if (isprime (d, t))
        {
            o << ",";
            if (i++ % 9) o << "\t";
            else o << endl << "\t";
            o << t;
        }

    o << endl << "};" << endl;

    delete[] d;

    return 0;
}
