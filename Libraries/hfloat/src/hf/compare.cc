
#include "hfloat.h"
#include "hfdatafu.h"
#include <fxt/aux0/sign.h>  // abs(), sign()
#include <fxt/sort/minmaxmed23.h>  // min2(), max2(), max3()

#include <cmath>
#include <fxt/fxtio.h>


int
cmp(const hfloat &a, const hfloat &b)
//
// return  0 if a=b
//        +1 if a>b
//        -1 if a<b
//
{
//    cout << "cmp(): " << endl;
//    print("a=",a,6);
//    print("b=",b,6);

    if ( a.sign() != b.sign() )  return sign( a.sign() - b.sign() );
    if ( a.is_zero() && b.is_zero() )  return 0;
    if ( a.exp() > b.exp() )  return +1;
    if ( a.exp() < b.exp() )  return -1;

    int sgn = dt_cmp(*a.data(), *b.data());
//    cout << "cmp(): dt_cmp: sgn=" << sgn
////         << "  idx=" << idx
//         << endl;

    return  a.sign() * sgn;
}
//================= end =================


int
cmp(const hfloat &a, const hfloat &b, ulong &idx)
//
// return  0 if a=b
//        +1 if a>b
//        -1 if a<b
//
// sets idx to the index of the first different LIMBs
{
    idx = 0;
    if ( a.sign() != b.sign() )  return sign( a.sign() - b.sign() );
    if ( a.is_zero() && b.is_zero() )  return 0;
    if ( a.exp() > b.exp() )  return +1;
    if ( a.exp() < b.exp() )  return -1;

    int sgn = dt_cmp(*a.data(), *b.data(), &idx);

    return  a.sign() * sgn;
}
//================= end =================


int
cmp(const hfloat &a, long b)
//
// return  0 if a=b
//        +1 if a>b
//        -1 if a<b
//
{
    if ( 0==b )
    {
        if ( a.is_zero() )   return 0;
        if ( a.positive() )  return +1;
        else                 return -1;
    }
    else
    {
        static hfloat x(hfloat::longlimbs);  // jjnote: static hfloat
        i2hfloat_prec_adj(b,x);
        return cmp(a,x);
    }
}
//================= end =================

int
cmp(const hfloat &a, ulong b)
//
// return  0 if a=b
//        +1 if a>b
//        -1 if a<b
//
{
    if ( 0==b )
    {
        if ( a.is_zero() )   return 0;
        else                 return +1;
    }
    else
    {
        static hfloat x(hfloat::longlimbs);  // jjnote: static hfloat
        u2hfloat_prec_adj(b,x);
        return cmp(a,x);
    }
}
//================= end =================


int
cmp(const hfloat &a, double b)
//
// return  0 if a=b
//        +1 if a>b
//        -1 if a<b
//
{
    if ( 0==b )
    {
        if ( a.is_zero() )   return 0;
        if ( a.positive() )  return +1;
        else                 return -1;
    }
    else
    {
        static hfloat x(hfloat::longlimbs);  // jjnote: static hfloat
        ulong p = d2hfloat(b,x);
        x.prec(p);
        return cmp(a,x);
    }
}
//================= end =================


long
cmp1(const hfloat &a)
//
// returns the (unsigned) index of the first disagreeing LIMB:
// -1 is returned if signs or exponents disagree
//
{
    // sign ok ?:
    if ( a.sign()!=+1 )  return -1;

    const LIMB *ad = a.data()->dig();
    const long  ap = (long)a.prec();

    long k;
    switch ( (long)a.exp() )
    {
    case 0:  // ? number= .99999999*RADIX^0:
        {
            const uint nine = (uint)hfdata::rx-1;
            for (k=0; k<ap; ++k)  if ( ad[k]!=nine )  break;
            break;
        }

    case 1:  // ? number= .10000000*RADIX^1:
        {
            if ( ad[0]!=1 )  k = 0;
            else
            {
                for (k=1; k<ap; ++k)  if ( ad[k]!=0 )  break;
            }
            break;
        }

    default:
        k = -1;
    }

    return k;
}
//====================== end ==========================



ulong
agree_prec(const hfloat &a, const hfloat &b, hfloat &x)
//
// returns 0 if exponent(a-b) >= 0
// else returns -exponent(a-b) (which is > 0)
//
// useful for means
{
    sub(a, b, x);
    if ( x.is_zero() )  return x.prec();

    if ( x.exp() >=0 )  return 0;
    else                return (ulong) - x.exp();
}
//=============== end ====================


int
approximate(const hfloat &a, double d, double relerr/*=1.0e-12*/)
//
// whether a==d within relative error relerr
// useful for checks
//
{
    double t;
    hfloat2d(a, t);

    if ( t==0 )  return (d==0);

    if ( sign(t)!=sign(d) )  return 0;

    t = fabs(t);
    d = fabs(d);

    double mi = min2(t, d);
    double ma = max2(t, d);
    double re = ((ma-mi)/ma);

    return  ( re < relerr );
}
//=================== end ========================
