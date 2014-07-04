
#include <cmath>

#include "hfloat.h"
#include "hfdata.h"

#include <fxt/jjassert.h>
#include "hfparanoia.h"


int
integerq(const hfloat &a)
//
//  return: (opposite to other funcs here)
//   1 if input was an integer
//   0 else
//
{
#ifdef  HF_PARANOIA
    jjassert( a.OK() );
#endif

    if ( a.is_zero() )  return 1;

    // number of LIMBs containing the fractional part:
    long  n = (long)a.prec() - a.exp();

    if ( n<=0 )
    {
        // note a (possibly noninteger) number of the form
        // 0.314159265*10^16 is considered integer here
        return 1;
    }
    else
    {
        // test if all fractional LIMBs are zero:
        LIMB *d = a.data()->dig();
        long f = 0;
        // cf.:   i_first(d,n) in auxid.cc
        while ( (f<n) && (d[f]==0) )  f++;

        if ( f<n )  return 0;  // there is a LIMB!=0 after integral part
        else        return 1;
    }
}
//====================== end ==========================



int
round(const hfloat &x, hfloat &a)
//
//  return:
//   0 if input was an integer
//   1 else
//
{
#ifdef  HF_PARANOIA
    jjassert( x.OK() );
#endif

    a = x;

    if ( integerq(a) )  return 0;

    // funny way of adding 0.5 with minimal error:
    mul2(a,a);   // 2*a
    a += 1;      // 2*a+1
    a /= 2;      // a+0.5
    floor(a,a);

#ifdef  HF_PARANOIA
    jjassert( a.OK() );
#endif

    return 1;
}
//====================== end ==========================




// for floor0() and frac0() this relation holds:
// x == floor0(x) + frac0(x)

int
round0(const hfloat &x, hfloat &a)
//
//  set a to 'x rounded towards zero'
//
//  return:
//   0 if input was an integer
//   1 else
//
{
#ifdef  HF_PARANOIA
    jjassert( x.OK() );
#endif

    a = x;
    if ( integerq(a) )  return 0;

    int sg = a.sign();
    a.sign( +1 );
    floor(a,a);
    a.sign( sg );

#ifdef  HF_PARANOIA
    jjassert( a.OK() );
#endif

    return 1;
}
//====================== end ==========================
