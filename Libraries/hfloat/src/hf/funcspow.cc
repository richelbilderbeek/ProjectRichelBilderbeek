
#include "hfloat.h"
#include "hfverbosity.h"

#include <fxt/jjassert.h>
#include <fxt/fxtio.h>
#include <fxt/aux0/sign.h>  // Abs()
#include <fxt/bits/bit2pow.h>  // is_pow_of_2()

#define HFPOW_USE_L2R  // whether to use left-to-right exponentiation
#ifdef HFPOW_USE_L2R
#include <bits/bithigh.h>  // highest_one()
#endif


void
pow(const hfloat &a, long e, hfloat &c)
{
#ifdef  HF_PARANOIA
    jjassert( a.OK() );
#endif

    ulong x = Abs(e);

    const char *v = hfverbosity::powbegin;
    if ( x!=1 )
    {
        hfverbosity::say( v );
        if ( v )  cout << e << ':';
    }

    if ( x<2 )
    {
        switch ( x )
        {
        case 1:  c.copy(a);  break;
        case 0:  u2hfloat(1, c);  break;
        }
    }
    else // ( x>=2 )
    {
        if ( is_pow_of_2(x) )  // special case x==2^n
        {
            sqr(a, c);  // c = a*a
            while ( x>2 )  { sqr(c, c);  x /= 2; }
        }
        else  // ( x>=3 )
        {
            pow_geq_3(a, x, c);
        }
    }

    if ( e<0 )  inv(c, c);

    if ( x!=1 )  hfverbosity::say( hfverbosity::powend );

#ifdef  HF_PARANOIA
    jjassert( c.OK() );
#endif
}
//======================= end POW =============================


void
pow_geq_3(const hfloat &a, ulong x, hfloat &c)
//
// c=a^x
// exponent >= +3
//
{
#ifdef  HF_PARANOIA
    jjassert( a.OK() );
    jjassert( x>=3 );
#endif

#ifdef HFPOW_USE_L2R
//    if ( 0==x )  return 1;
    hfloat s( c.prec() );  // jjnote: temporary hfloat
    s = a;
    ulong b = highest_one(x);
    while ( b>1 )
    {
        b >>= 1;
        sqr(s, s);  // s *= s;
        if ( x & b )  mul(s, a, s);  // s *= a;
    }
//    return s;
    c = s;

#else // def HFPOW_USE_L2R
    hfloat at(c.prec());  // jjnote: temporary hfloat
    at = a;
    int firstq = 1;
    while ( 1 )
    {
        if ( x&1 )  // odd
        {
            // avoid multiplication by 1:
            if ( firstq )  { c = at;  firstq = 0; }
            else           mul(c, at, c);

            if ( x==1 )  break;
        }

        sqr(at, at);
        x /= 2;
    }
#endif // def HFPOW_USE_L2R

#ifdef  HF_PARANOIA
    jjassert( c.OK() );
#endif
}
// ========================== end POWER_GEQ_3 ==============================
