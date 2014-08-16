
//#include <cmath>

#include "hfloat.h"

static bool
check_const(hfloat *&h, ulong &myrx, ulong n)
//
// Check, to which precision h was computed previously.
// Check, if it was computed with the current radix.
// Return 1 if computation has to be done, else 0.
//
{
    if ( !h )  // first time ?
    {
        h = new hfloat(n); // allocate if necessary
        myrx = hfloat::radix();
        return true;
    }

    if ( n > (h->size()) ) // need more digits ?
    {
        h->prec(n);
        myrx = hfloat::radix();
        return true;
    }

    h->prec( n );

    if ( myrx != (hfloat::radix()) ) // did a radix change occur ?
    {
        myrx = hfloat::radix();
        return true;
    }

    return false;  // no need to compute
}
//============== end ==========


const hfloat &
constant_pi(ulong n)
{
    static ulong myrx = 0;
    hfloat *h = hfloat::const_pi;

    if ( check_const(h,myrx,n) )
    {
        pi_4th_order(*h, 0);
    }

    return *h;
}
//============== end ============



const hfloat &
constant_logrx(ulong n)
{
    static ulong myrx = 0;
    hfloat *h = hfloat::const_logrx;

    if ( check_const(h,myrx,n) )
    {
        pi_by_log_rx(n, *h);          // pi/log(radix)
        div( constant_pi(n), *h, *h); // log(radix)
    }

    return *h;
}
//============== end ============


const hfloat &
constant_sqrt2(ulong n)
{
    static ulong myrx = 0;
    hfloat *h = hfloat::const_sqrt2;

    if ( check_const(h,myrx,n) )
    {
        isqrt((ulong)2, *h);    // 1/sqrt(2)
        mul(*h, (ulong)2, * h); // sqrt(2)
    }

    return *h;
}
//============= end ===============


const hfloat &
constant_logsqrt2(ulong n)
{
    static ulong myrx = 0;
    hfloat *h = hfloat::const_logsqrt2;

    if ( check_const(h,myrx,n) )
    {
        *h = constant_sqrt2(n);   // sqrt(2) = 2^(1/2)
        log_agm(*h, *h);          // log(sqrt(2))
    }

    return *h;
}
//============= end ===============

