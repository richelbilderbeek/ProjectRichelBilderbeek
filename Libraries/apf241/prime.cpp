#include <cmath>
#include "ap.h"


// Factor a prime using a table of smaller primes
size_t factor (rawtype f[], rawtype n)
{
    size_t t = 0, i = 0;
    rawtype p, r, d;

    r = (rawtype) sqrt ((double) n);

    do
    {
        p = primetable[t++];
        while (bigdiv (&d, &n, p, 1) == 0)
        {
            n = d;
            f[i++] = p;
            r = (rawtype) sqrt ((double) n);
        }
    } while (p < r);

    if (n != 1) f[i++] = n;

    return i;
}

// Test for primality
bool isprime (rawtype n)
{
    size_t t = 0;
    rawtype p, r, d;

    r = (rawtype) sqrt ((double) n);

    while ((p = primetable[t++]) <= r)
        if (bigdiv (&d, &n, p, 1) == 0)
            return false;

    return true;
}

// Finds next (small) prime >= n
rawtype nextprime (rawtype n)
{
    while (!isprime (n)) n += 1;

    return n;
}

// Finds a prime less than u of the form k * n + 1 for transform length n
rawtype getprime (rawtype n, rawtype u)
{
    rawtype k = 2;

    bigsub (&u, &k, 1);
    bigdiv (&k, &u, n, 1);

    while (k != 0 && !isprime (k * n + 1)) k -= 1;

    if (k == 0) return 0;

    return k * n + 1;
}

// Primitive root of modint::modulus
modint primitiveroot (void)
{
    size_t t, s, p = 0, i;
    rawtype m, f[RAWBITS];
    modint r;

    m = modint::modulus - 1;

    i = factor (f, m);

    for (t = 0, s = 0; t < i; t++)
        if (f[s] != f[t]) f[++s] = f[t];

    i = s + 1;

    do
    {
        r = primetable[p++];
        for (t = 0; t < i; t++)
            if (pow (r, m / f[t]) == modint (1)) break;
    } while (t < i);

    return r;
}

// Finds the three different primes of k*n+1
void initmoduli (rawtype n)
{
    moduli[0] = getprime (n);
    moduli[1] = getprime (n, moduli[0]);
    moduli[2] = getprime (n, moduli[1]);
}

// Sets the base
void apbase (int digit)
{
    int basedigits = 0, i, t, s;
    rawtype basedigit = (rawtype) digit, m, base = 1, f[RAWBITS];

    while (bigmul (&m, &base, basedigit, 1) == 0 && m < moduli[2])
    {
        base = m;
        basedigits++;
    }

    Base = base;
    Basedigit = basedigit;
    Basedigits = basedigits;

    i = factor (f, basedigit);

    for (t = 0, s = 0; t < i; t++)
        if (f[s] != f[t]) f[++s] = f[t];

    i = s + 1;

    NBasefactors = i;

    for (t = 0; t < i; t++)
        Basefactors[t] = f[t];
}
