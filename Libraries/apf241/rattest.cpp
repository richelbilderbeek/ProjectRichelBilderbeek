#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <ctime>
#include "ap.h"
#include "aprat.h"


using namespace std;


// Calculates pi using the binsplit algorithm
// Code is essentially taken from the book "Pi: Algorithmen, Computer, Arithmetik"
// by Jörg Arndt & Christoph Haenel, Springer-Verlag 1998

aprational a (long k, long j, apint x)
{
    if (j < 0)
    {
        if (k & 1)
            return aprational (-1, (2 * k + 1) * pow (x, 2 * k + 1));
        else
            return aprational (1, (2 * k + 1) * pow (x, 2 * k + 1));
    }
    else
    {
        if ((k - j) & 1)
            return aprational (-2 * j - 1, (2 * k + 1) * pow (x, 2 * (k - j)));
        else
            return aprational (2 * j + 1, (2 * k + 1) * pow (x, 2 * (k - j)));
    }
}

aprational r (long m, long n, apint x)
{
    aprational v;
    long p = (m + n) >> 1;

    if (m == n)
        v = a (m, m - 1, x);
    else
        v = r (m, p, x) + a (p, m - 1, x) * r (p + 1, n, x);

    // cerr << "r (" << m << ", " << n << ") = " << v << endl;

    return v;
}

int main (int argc, char *argv[])
{
    size_t prec;
    int m = 0, base = 10;
    apfloat p;
    time_t tt;
    clock_t tc;

    if (argc < 2)
    {
        cerr << "USAGE: rattest digits [method] [base]" << endl;
        cerr << "    method: 0 = 16*arctan(1/5) - 4*arctan(1/239)" << endl;
        cerr << "            1 = 32*arctan(1/10) - 4*arctan(1/239) - 16*arctan(1/515)" << endl;
        cerr << "            2 = 48*arctan(1/18) + 32*arctan(1/57) - 20*arctan(1/239)" << endl;
        cerr << "            3 = 176*arctan(1/57) + 28*arctan(1/239) - 48*arctan(1/682) + 96*arctan(1/12943)" << endl;
        cerr << "    base must be 2...36" << endl;
        return 2;
    }

    istringstream s (argv[1]);
    if (!(s >> prec) || !prec)
    {
        cerr << "Invalid argument digits: " << argv[1] << endl;
        return 1;
    }

    if (argc > 2)
    {
        istringstream s (argv[2]);
        if (!(s >> m))
        {
            cerr << "Method must be 0...3" << endl;
            return 1;
        }
    }

    if (argc > 3)
    {
        istringstream s (argv[3]);
        if (!(s >> base))
        {
            cerr << "Invalid argument base: " << argv[3] << endl;
            return 1;
        }
    }

    apbase (base);

    aprational::autoreduce = false;

    if (m == 0)
    {
        size_t a5d, a239d;

        a5d = (size_t) (prec * log ((double) base) / (2 * log (5.0)));
        a239d = (size_t) (prec * log ((double) base) / (2 * log (239.0)));

        tt = time (0);
        tc = clock ();

        aprational a5 = r (0, a5d, 5), a239 =  r (0, a239d, 239);

        p = 16 * a5.approx (prec) - 4 * a239.approx (prec);
    }
    else if (m == 1)
    {
        size_t a10d, a239d, a515d;

        a10d = (size_t) (prec * log ((double) base) / (2 * log (10.0)));
        a239d = (size_t) (prec * log ((double) base) / (2 * log (239.0)));
        a515d = (size_t) (prec * log ((double) base) / (2 * log (515.0)));

        tt = time (0);
        tc = clock ();

        aprational a10 = r (0, a10d, 10), a239 =  r (0, a239d, 239), a515 = r (0, a515d, 515);

        p = 32 * a10.approx (prec) - 4 * a239.approx (prec) - 16 * a515.approx (prec);
    }
    else if (m == 2)
    {
        size_t a18d, a57d, a239d;

        a18d = (size_t) (prec * log ((double) base) / (2 * log (18.0)));
        a57d = (size_t) (prec * log ((double) base) / (2 * log (57.0)));
        a239d = (size_t) (prec * log ((double) base) / (2 * log (239.0)));

        tt = time (0);
        tc = clock ();

        aprational a18 = r (0, a18d, 18), a57 = r (0, a57d, 57), a239 =  r (0, a239d, 239);

        p = 48 * a18.approx (prec) + 32 * a57.approx (prec) - 20 * a239.approx (prec);
    }
    else // (m == 3)
    {
        size_t a57d, a239d, a682d, a12943d;

        a57d = (size_t) (prec * log ((double) base) / (2 * log (57.0)));
        a239d = (size_t) (prec * log ((double) base) / (2 * log (239.0)));
        a682d = (size_t) (prec * log ((double) base) / (2 * log (682.0)));
        a12943d = (size_t) (prec * log ((double) base) / (2 * log (12943.0)));

        tt = time (0);
        tc = clock ();

        aprational a57 = r (0, a57d, 57), a239 =  r (0, a239d, 239),
                   a682 =  r (0, a682d, 682), a12943 =  r (0, a12943d, 12943);

        p = 176 * a57.approx (prec) + 28 * a239.approx (prec) -
            48 * a682.approx (prec) + 96 * a12943.approx (prec);
    }

    cerr.setf (ios::fixed, ios::floatfield);
    cerr << "Total CPU time " << setprecision (3) << (clock () - tc) / (double) CLOCKS_PER_SEC << " seconds, total elapsed time " << setprecision (0) << difftime (time (0), tt) << " seconds" << endl;

    cout << pretty << p << endl;

    return 0;
}
