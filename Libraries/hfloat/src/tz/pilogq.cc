
#include <cmath>

#include "hfloat.h"


void
theta3_invrx4(hfloat &th3)
//
// return theta3(1/q)  where q = 1/radix^4
//
// th3(q) := \sum_{n=-\infty}^{\infty}{q^{n^2}}
//  = 1 + 2*\sum_{n=1}^{\infty}{q^{n^2}}
//  = 2*(1 + \sum_{n=1}^{\infty}{q^{n^2}}) - 1
//
// note q is the inverse of q in the code
{
    th3 = 1;

    ulong k = 1;
    while ( 1 )
    {
        ulong s = (k*k) * 4;
        if ( s>=th3.prec() )  break;
        th3.set_limb(s,1);
        k++;
    }

    th3 *= 2;
    th3 -= 1;
}
// -------------------------


void
theta2_invrx4(hfloat &th2)
//
// return theta2(1/q)  where q = 1/radix^4
//
// th2(q) := \sum_{n=-\infty}^{\infty}{q^{(n+1/2)^2}}
// exponents: {... -1.5, -0.5, +0.5, +1.5, ...}
// sqr: 2* {0.5, 1.5, ...}
//  = 0 + 2*\sum_{n=0}^{\infty}{q^{(n+1/2)^2}}
//  ( if q==b^4 )
//  = 2*\sum_{n=0}^{\infty}{b^{4n^2+4n+1}}
//  = b*2*\sum_{n=0}^{\infty}{q^{n^2+n}}
//  = (1+\sum_{n=1}^{\infty}{q^{n^2+n}}) * 2 * b
//
// note q and b are the inverses of those in the code
{
    th2 = 1;

    ulong  k = 1;
    while ( 1 )
    {
        ulong s = (k*k+k) * 4;
        if ( s>=th2.prec() )  break;
        th2.set_limb(s,1);
        k++;
    }

    th2 *= 2;
    th2.exp( th2.exp()-1 );  // divide by radix
}
// -------------------------



void
pi_by_log_rx(ulong n, hfloat &x)
//
// return pi/log(1/q)  where  q=1/radix
//
// pi/log(1/q) = AGM(th3(q)^2, th2(q)^2)
// th3(q) := \sum_{n=-\infty}^{\infty}{q^{n^2}}
// th2(q) := \sum_{n=-\infty}^{\infty}{q^{(n+1/2)^2}}
// cf. Borwein^2 p.225
//
{
#if 1  // optimization:
    // These save about 3 full precision mults with 10^6 decimal digits.

    hfloat th3(n);
    theta3_invrx4(th3);

    hfloat th2;
    theta2_invrx4(th2);

#if 1
    // This version avoids possible cancellation:
    add(th2, th3, x);       // th2 + th3
    th2 *= th3;  th2 *= 2;  // 2*th2*th3
    sqr(x, th3);            // (th2 + th3)^2
    th3 -= th2;             // (th2 + th3)^2 - 2*th2*th3 = th2^2 + th3^2

    agm(th3, th2, x);
    x *= 2;

#else
    x = th3;  x -= th2;    // th3 - th2
    sqr(x, x);             // (th3 - th2)^2
    th3 += th2;            // th3 + th2
    sqr(th3, th3);         // (th3 + th2)^2
    th2 = th3;  th2 -= x;  // (th3 + th2)^2 - (th3 - th2)^2 = 4*th2*th3
    th3 += x;              // (th3 + th2)^2 + (th3 - th2)^2 = 2*(th3^2 + th2^2)

    agm(th3, th2, x);

#endif


#else

    hfloat th3(n);
    theta3_invrx4(th3);
    sqr(th3, th3);

    hfloat &th2 = x;  // note x is a reference to th2
    theta2_invrx4(th2);
    sqr(th2, th2);

    agm(th3, th2, x);
    x *= 4;

#endif
}
// -------------------------


// Cf. Gospers formula:
//
// pi/log(1/q) = AGM( 2*th2(q^2)^2, th2(q)^4/(2*th2(q^2)^2) )
//
// note that both args of AGM() have simple series in q
// (which is not evident for the 2nd arg)


