
#include "fxttypes.h"
#include "fxtmult.h"
#include "bits/bit2pow.h" // ld()
//#include "jjassert.h"


ulong
next_dfxtlen(ulong n)
{
    ulong n2 = (1UL<<ld(n));
    if ( n2<n )  n2 <<= 1;
    return n2;
}
// -------------------------

ulong
previous_dfxtlen(ulong n)
{
    return  (1UL<<ld(n));
}
// -------------------------


ulong
sum_of_digits(const double *a, ulong n,
              double nine, ulong su)
{
    double s = (double)su;

    for (ulong k=0; k<n; ++k)
    {
        s += a[k];
//        if  ( s>=nine )  s -= nine;
    }

    ulong si = (ulong)s;
    si %= (ulong)nine;

    return si;
}
// -------------------------


ulong
sum_of_digits(const LIMB *a, ulong n,
              ulong nine, ulong s)
{
//    if ( s )  jjassert( s<nine );
    for (ulong k=0; k<n; ++k)
    {
        s += a[k];
//        if  ( s>=nine )  s -= nine;
    }

    s %= nine;

    return s;
}
// -------------------------


ulong
mult_sum_of_digits(const LIMB *a, ulong an,
                   const LIMB *b, ulong bn,
                   ulong nine)
{
    ulong qsa = sum_of_digits(a, an, nine, 0);
    ulong qsb = sum_of_digits(b, bn, nine, 0);
    ulong qsm = (qsa*qsb) % nine;
    return  qsm;
}
// -------------------------


ulong
sqr_sum_of_digits(const LIMB *a, ulong an,
                  ulong nine)
{
    ulong qsa = sum_of_digits(a, an, nine, 0);
    ulong qsm = (qsa*qsa) % nine;
    return  qsm;
}
// -------------------------

