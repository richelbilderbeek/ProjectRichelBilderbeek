
#include <cmath>

#include "hfloat.h"
#include "hfdata.h"
#include <fxt/aux1/copy.h>  // null()
#include <fxt/aux1/shift.h>  // shift_left()

#include <fxt/jjassert.h>
#include "hfparanoia.h"


// for floor() and frac() this relation holds:
// x == floor(x) + frac(x)

int
floor(const hfloat &x, hfloat &a)
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

    long  di = a.exp();  // number of LIMBS containing integral part
    if ( di<(long)a.prec() )
    {
        LIMB *d = a.data() -> dig();
        null(d+di, a.prec()-di);
    }
    a.normalize();
#ifdef  HF_PARANOIA
    jjassert( a.OK() );
#endif

    return 1;
}
//====================== end ==========================


int
frac(const hfloat &x, hfloat &a)
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
    if ( integerq(a) )     // no fractional part
    {
        a.set_zero();
        return 0;
    }

    long  di = a.exp();  // number of LIMBS containing integral part
    shift_left(a.data()->dig(), a.prec(), di);
    a.exp(0);
    a.normalize();

#ifdef  HF_PARANOIA
    jjassert( a.OK() );
#endif

    return 1;
}
//====================== end ==========================



int
frac0(const hfloat &x, hfloat &a)
//
//  a = x - round0(x)
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
    if ( integerq(a) )
    {
        a.set_zero();
        return 0;
    }

    int sg = a.sign();
    a.sign( +1 );
    frac(a,a);
    a.sign( sg );

#ifdef  HF_PARANOIA
    jjassert( a.OK() );
#endif

    return 1;
}
//====================== end ==========================
