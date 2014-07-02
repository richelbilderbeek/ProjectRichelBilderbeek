#include "ap.h"


// Returns in r the solution of x == r[k] (mod m[k]), k = 0, ..., n-1
void crt (rawtype *r, rawtype *m, size_t n)
{
    size_t t, k;
    rawtype *mm = new rawtype[n], *x = new rawtype[n], *s = new rawtype[n];
    modint y;
    rawtype o;

    o = modint::modulus;

    mm[0] = m[0];
    for (t = 1; t < n; t++)
        mm[t] = bigmul (mm, mm, m[t], t);

    for (t = 0; t < n; t++)
        s[t] = 0;

    for (k = 0; k < n; k++)
    {
        setmodulus (m[k]);

        y = 1;
        for (t = 0; t < n; t++)
            if (t != k) y *= m[t];

        y = r[k] / y;

        bigdiv (x, mm, m[k], n);
        x[n - 1] = bigmul (x, x, y, n - 1);

        if (bigadd (s, x, n) || bigcmp (s, mm, n) > 0)
            bigsub (s, mm, n);
    }

    moveraw (r, s, n);

    setmodulus (o);

    delete[] mm;
    delete[] x;
    delete[] s;
}
