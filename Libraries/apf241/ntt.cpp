#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include "ap.h"


using namespace std;


// Program for testing the direct ntt

void ntt (modint x[], modint pr, int isign, int nn)
{
    int k, j;
    modint w, wj, wk = 1;

    modint *xx = new modint[nn];

    if (isign < 0)
        w = pow (pr, (modint::modulus - 1) / nn);
    else
        w = pow (pr, modint::modulus - 1 - (modint::modulus - 1) / nn);

    for (k = 0; k < nn; k++)
    {
        xx[k] = 0;
        wj = 1;

        for (j = 0; j < nn; j++)
        {
            xx[k] += wj * x[j];
            wj *= wk;
        }

        wk *= w;
    }

    for (k = 0; k < nn; k++)
        x[k] = xx[k];

    delete[] xx;
}

int main (int argc, char *argv[])
{
    int t, r, n;
    time_t b;
    modint pr;

    if (argc != 2)
    {
        cerr << "USAGE: ntt n" << endl;
        return 2;
    }

    istringstream s (argv[1]);

    if (!(s >> n))
    {
        cerr << "Invalid argument n: " << argv[1] << endl;
        return 1;
    }

    modint *d = new modint[n];

    if (!d)
    {
        cerr << "Out of memory" << endl;
        return 1;
    }

    setmodulus (getprime (n));

    pr = primitiveroot ();

    cout << "Size: " << n << endl;

    b = time (0);

    for (t = 0; t < n; t++)
        d[t] = t + 1;

    ntt (d, pr, 1, n);

    cout << "Seconds: " << difftime (time (0), b) << endl;

    for (t = 0; t < n; t++)
    {
        cout << setw (16) << d[t];
        if ((t & 3) == 3) cout << endl;
    }

    cout << endl;

    ntt (d, pr, -1, n);

    for (t = 0; t < n; t++)
        d[t] /= n;

    for (t = 0; t < n; t++)
    {
        cout << setw (16) << d[t];
        if ((t & 3) == 3) cout << endl;
    }

    cout << endl;

    /*
    ntt (d, pr, -1, n);

    for (t = 0; t < n; t++)
    {
        cout << setw (16) << d[t];
        if ((t & 3) == 3) cout << endl;
    }
    */

    delete[] d;

    return 0;
}
