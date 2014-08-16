#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include "ap.h"


using namespace std;


// Program for testing the WFTA functions

int main (int argc, char *argv[])
{
    int t, r, n, n1, n2 = 1, i = 1, m = 0, p = 0;
    time_t b;
    modint pr;

    if (argc < 2)
    {
        cerr << "USAGE: wfta n1 [n2] [sign] [method] [print]" << endl;
        cerr << "Note: n1 <= n2" << endl;
        return 2;
    }

    istringstream s (argv[1]);

    if (!(s >> n1))
    {
        cerr << "Invalid argument n1: " << argv[1] << endl;
        return 1;
    }

    if (argc > 2)
    {
        istringstream s (argv[2]);

        if (!(s >> n2))
        {
            cerr << "Invalid argument n2: " << argv[2] << endl;
            return 1;
        }
    }

    if (argc > 3)
    {
        istringstream s (argv[3]);

        if (!(s >> i))
        {
            cerr << "Invalid argument sign: " << argv[3] << endl;
            return 1;
        }
    }

    if (argc > 4)
    {
        istringstream s (argv[4]);

        if (!(s >> m))
        {
            cerr << "Invalid argument method: " << argv[4] << endl;
            return 1;
        }
    }

    if (argc > 5)
    {
        istringstream s (argv[5]);

        if (!(s >> p))
        {
            cerr << "Invalid argument print: " << argv[5] << endl;
            return 1;
        }
    }

    n = n1 * n2;

    modint *d = new modint[n];

    if (!d)
    {
        cerr << "Out of memory" << endl;
        return 1;
    }

    setmodulus (wftamoduli[0]);
    pr = wftaprimitiveroots[0];

    /*
    setmodulus (getprime (n));

    pr = primitiveroot ();

    createpermutetables ();
    createwtables (pr, wt, iwt, w, iw);
    */

    cout << "Size: " << n << endl;
    cout << "Modulus: " << modint::modulus << endl;
    cout << "Primitive root: " << pr << endl;
    cout << "Sign: " << i << endl;
    cout << "Method: ";
    switch (m)
    {
        case 0: cout << "WFTA (wfta)" << endl;
                break;
        case 1: cout << "\"Six-step\" WFTA & inverse (sixstepwftatrans)" << endl;
                break;
    }

    for (t = 0; t < n; t++)
        d[t] = t + 1;

    b = time (0);

    switch (m)
    {
        case 0: wfta (d, (i < 0 ? iw_0 : w_0), n);
                break;
        case 1: sixstepwftatrans (d, (i < 0 ? iw_0 : w_0), pr, i, n1, n2);
                isixstepwftatrans (d, (i < 0 ? w_0 : iw_0), pr, -i, n1, n2);
                break;
    }

    cout << "Seconds: " << difftime (time (0), b) << endl;

    cout << endl;

    if (p)
        for (t = 0; t < n; t++)
        {
            cout << setw (16) << d[t];
            if ((t & 3) == 3) cout << endl;
        }

    cout << endl;

    delete[] d;

    clearmodulus ();

    return 0;
}
