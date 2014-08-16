#include <iostream>
#include <iomanip>
#include "ap.h"


using namespace std;


// Program for testing the CRT
// Won't work with the 64-bit versions for now

int main (void)
{
    int n = 4, t;
    rawtype *r = new rawtype[n], *m = new rawtype[n], *b = new rawtype[n + 1];

    if (!r || !m)
    {
        cerr << "Not enough memory" << endl;
        return 1;
    }

    r[0] = 1;
    r[1] = 2;
    r[2] = 3;
    r[3] = 4;

    m[0] = getprime (n);
    setmodulus (m[0]);

    for (t = 1; t < n; t++)
        m[t] = getprime (n, m[t - 1]);

    cout << "Moduli:   ";

    for (t = 0; t < n; t++)
        cout << setw (12) << m[t];

    cout << endl;

    cout << "Residues: ";

    for (t = 0; t < n; t++)
        cout << setw (12) << r[t];

    cout << endl;

    crt (r, m, n);

    cout << "Solution: ";

    for (t = 0; t <= n; t++)
        b[t] = bigdiv (r, r, 1000000000, n);

    for (t = 0; t <= n && !b[n - t]; t++);

    cout << b[n - t];

    for (++t; t <= n; t++)
        cout << setw (9) << setfill ('0') << b[n - t];

    cout << endl;

    delete[] b;
    delete[] m;
    delete[] r;

    return 0;
}
