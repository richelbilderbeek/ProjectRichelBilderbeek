
#include <cmath>

#include "hfloat.h"


void
sumalt( void (*termfct)(ulong, long &, ulong &), hfloat &s, ulong nn/*=0*/)
// compute \sum_{k=0}^{\infty}{termfct(k)}
// works only for alterating sums,
// i.e. termfct must be of type (-1)^k*positive(k)
// this version avoids the sqrt and pow computation
// nn (if given) overrides the number of terms to be added
// this algorithm uses proportional n short multiplications
{
    ulong p = s.prec();
    // how may terms are needed in sumalt for precision p:
    ulong n = (ulong)ceil( (double)p*log((double)hfloat::radix())/log(3.0+sqrt(8.0)) );
    if ( nn )  n = nn;
    if ( n<3 )  n = 4;

    hfloat b(p);  b = 1;
    mul2pow(b,2*n-1,b); // b = 2**(2*n-1)
    hfloat c(p);  c = b;
    hfloat t(p);
    s = 0;
    for (long k=n-1; k>=0; --k)
    {
        long num;
        ulong den;
        termfct(k, num, den);

        // t = c * (num/den):
        t = c;
        t *= num;
        t /= den;

        s += t;  // s += c * (num/den)
        b /= (2*(n+k)*(n-k));
        b *= ((2*k+1)*(k+1));
        c += b;  // c += b
    }
    s /= c;
}
//=================== end =======================

/*
EXAMPLES: with
hfloat s = hfloat(256);  // less than , say 1024 LIMBs
sumalt(gregory_term, s);  // compute pi as arctan(1)
*/


void
gregory_term(ulong k, long &num, ulong &den)
// for arctan(1) = \sum_{k=0}^{\infty}{(-1)^k*1/(2*k+1)}
{
    num = 1;
    if ( k&1 )  num = -num;
    den = (2*k+1);
}
//---------------

void
catalan_term(ulong k, long &num, ulong &den)
// for catalan = \sum_{k=0}^{\infty}{(-1)^k*1/(2*k+1)^2}
{
    num = 1;
    if ( k&1 )  num = -num;
    den = ((2*k+1)*(2*k+1));
}
//---------------

void
log2_term(ulong k, long &num, ulong &den)
// for log(2) = \sum_{k=0}^{\infty}{(-1)^k*1/(k+1)}
{
    num = 1;
    if ( k&1 )  num = -num;
    den = (k+1);
}
//---------------


void
sum_partial( void (*termfct)(ulong, long &, ulong &), hfloat *p, ulong n)
// compute partial sums and fill them into p[]
{
    long num;
    ulong den;
    termfct(0, num, den);
    p[0] = num;
    p[0] /= den;

    for (ulong k=1; k<n; ++k)
    {
        termfct(k, num, den);
        p[k] = num;
        p[k] /= den;
        p[k] += p[k-1];
    }
}
//=================== end =======================

void
sumalt_partial(hfloat *p, hfloat &s, ulong nn)
// compute the sumalt-estimate for a sum
// whose nn first partial sums are given in p[]
{
    const ulong pr = s.prec();
    // how may terms are used:
    ulong n = nn;

    hfloat b(pr);  b = 1;
    mul2pow(b,2*n-1,b); // b = 2**(2*n-1)
    hfloat t(pr);
    hfloat c(pr);  c = b;
    s = 0;
    for (long k=n-1; k>=0; --k)
    {
        // t = b * (num/den):
        t = b;
        t *= p[k];

        s += t;  // s += b * (num/den)
        b /= (2*(n+k)*(n-k));
        b *= ((2*k+1)*(k+1));

        c += b;
    }

    s /= c;
}
//=================== end =======================
