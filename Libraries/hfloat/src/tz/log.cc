
#include "hfloat.h"
#include "hfverbosity.h"
#include <fxt/jjassert.h>

#include <cmath>


void
log(const hfloat &a, const hfloat &b, hfloat &c)
{
    hfloat t( c.prec() );  // jjnote: temporary hfloat
    log(b,t);
    log(a,c);
    c /= t;
}
// -----------------

// debug:
#define  PR(x)

// whether to force arg of log_agm() to be in [0.5, 1.5]:
#define  PUSH_TO_ONE  1  // 1 (default) or 0

void
log(const hfloat &a, hfloat &b)
//
// 1) split off radix power:
// log(m*r^x) = log(m) + x*log(r)
//  = x*(log(m)/x + log(r))  // avoids temporary
//
// 2) avoid values outside [0.5, 1.5]:
// log(m) = log(m*s^f/s^f) = log(m*s^f) - f*log(s)
// where s = sqrt(2)
// and m*s^f is inside [0.5, 1.5]
//
{
    jjassert( a.positive() ); //  "negative arg for log()"

    b = a;
    PR( print("\n log(): arg=\n",a,10); );

    long x = a.exp() - 0;
    b.exp( 0 );

    double bd;
    hfloat2d(b,bd);
    PR( cout << "log(): bd=" << bd << endl; );

#if  ( PUSH_TO_ONE==1 )
    ulong n = b.prec();
    long  f = (long)floor( log(1.0/bd)/log(sqrt(2.0)) );
    PR( cout << "  log(): f=" << f << endl; );
    if ( f!=0 )  // z = b * sqrt(2)^f
    {
        if ( f&1 )  b *= constant_sqrt2( n );
        mul2pow(b, f/2, b);
        PR( print("\n log(): z = b*sqrt(2)^f=\n",b,10); );
    }
#else
#warning 'log(): PUSH_TO_ONE NOT SET !'
#endif

    log_agm(b,b);     // log(z) = log(b*sqrt(2)^f)
    PR( print("\n log(): log(b**sqrt(2)^f)=\n",b,10); );

#if  ( PUSH_TO_ONE==1 )
    if ( f!=0 )
    {
        b /= f;    // log(z)/f
        b -= constant_logsqrt2(n);  // log(z)/f - log(sqrt(2))
        b *= f;   // f*(log(z)/f - log(sqrt(2))) = log(b)
        PR( print("\n log(): log(b)=\n",b,10); );
    }
#endif

    // --- exponent:
    if ( x!=0 )
    {
        b /= x;
        PR( print("\n log(): b +=\n",constant_logrx( b.prec() ),10); );
        b += constant_logrx( b.prec() );  // ok, does not call log()
        b *= x;
    }
    PR( print("\n log(): log(b)=\n",b,10); );
}
// ================ end ==================


int
log_agm(const hfloat &a, hfloat &z)
//
// z = log(a)
// cf. Borwein^2 p.220
// abs(log(a)-pi/K'(rx^-n)+pi/K'(a*rx^-n)) <= n/(rx^(2*(n-1)))
//   for  abs(a-1) < 1/2,  n >= 3
//
{
    PR( cout << "\n\n start LOG_AGM() "; );
    PR( hfverbosity::pinums = 1; );
    PR( hfverbosity::meannums = 1; );
    PR( print(" arg=\n",a,12); );

#if  ( PUSH_TO_ONE==1 )
//    print("log_agm():",a,11);
    jjassert( a < 1.5001 ); // "log_agm(): out of range"
    jjassert( a > 0.4999 ); // "log_agm(): out of range"
#endif

    long  p = z.prec();
    long  n = (long)( p + 2 );
    PR( cout << "\n n=" << n; );

    hfloat b(p), x(p);
    const hfloat &pi = constant_pi(n);

    b = 1;
    mul_by_radix_pow(b, -n, b);  // rx^-n
    PR( print("\n log_agm(): (1)b=\n",b,10); );

    agm1(b,x);
    inv(x,x);
    mul(x,pi,x);
    x /= 2;  // K'(rx^-n)

    PR( print("\n log_agm(): sum1=\n",x,10); );

    b = a;
    mul_by_radix_pow(b,-n,b);  // a*rx^-n
    PR( print("\n log_agm(): (2)b=\n",b,10); );

    agm1(b,b);
    inv(b,b);
    mul(b,pi,b);
    b /= 2;  // K'(a*rx^-n)

    PR( print("\n log_agm(): sum2=\n",b,10); );

    sub(x,b,z);
    PR( print("\n log_agm(): sum1-sum2=\n",z,10); );

    return 0;
}
// ================ end ==================



