

#include <fxt/fxtio.h>

#include "hfloat.h"
#include <fxt/sort/minmaxmed23.h>  // min2(), max2()

#include <fxt/bits/bit2pow.h>  // ld()
#include <fxt/jjassert.h>

#include <cmath>
#include <cstdlib>


void approx_exp(const hfloat &d, hfloat &c);


// for debug:
#define  PR(x)
#define  SHRT  10

// whether to check that the last step in iteration really
// produced the full precision (expensive!):
const int check_last_step = 0;


static void expm1(const hfloat &x, ulong deg, hfloat &p, hfloat &tmp)
// Set p = x + x^2/2! + x^3/3! + ... + x^deg/deg!
// p = x*(1 + x/2*(1 + x/3*(1 + ... x/(deg-1)*(1 + x/deg))))
{
    tmp = x;
    p = x;
    for (ulong k=2; k<=deg; ++k)
    {
        tmp *= x;
        tmp /= k;
        p += tmp;
    }
}
// -------------------------


int
exp_iteration(const hfloat &di, hfloat &x, ulong startprec/*=0*/)
//
// Use the iteration for exp(d):
//
//   x <- x*(1+y+y^2/2!+y^3/3!+...) where y := d-log(x)
// equivalently:
//   x += x*(  y+y^2/2!+y^3/3!+...)
//
{
    PR( cout << __PRETTY_FUNCTION__ << endl; );
    PR( print("\n arg d=",di,SHRT); );

    if ( di.is_zero() )
    {
        x = 1;
        return 0;
    }

    hfloat d(di);  // jjnote: ugly: only needed when di.data()==x.data()

    hfloat tmp(di.prec());  // needed for expm1()
    hfloat tmp2(di.prec());  // needed for expm1()

    static const int order = 20;  // jjnote: fixme for 32 bit! (20! > 2^32)
//    static const ulong deg = order+1;
//    static long num[deg+1];
//    static long den[deg+1];
//
//    // setup ratpoly for exp()-1:
//    num[0] = 0;
//    den[0] = 1;
//    for (ulong k=1; k<=deg; ++k)
//    {
//        num[k] = 1;
//        den[k] = den[k-1] * k;  // k!
//    }

    ulong pg = x.prec();  // precision goal
    const ulong rpg = (pg>=6?pg-6:1); // jjnote: magic: realistic precision goal

    hfloat t(pg);
    const int max_rec = (int)(8+log((double)pg)/log((double)order));

    int  xs = d.sign();
    d.sign( +1 );

    startprec = 0;  // jjnote: unused  (avoid compiler warning)
    ulong ap;
    if ( startprec!=0 )
    {
        ap = startprec;
    }
    else
    {
        approx_exp(d,x);        PR( print("\n ==  x0=",x,SHRT); );
        ap = 3;  // assume 3 limbs are correct
    }

    ulong cp;  // calculation precision
    cp = next_pow_of_2( ap );
    cp = min2(cp, pg);

    int j;
    for(j=0; j<max_rec; ++j)  // ---------------- ITERATION --------------
    {
        if ( ap > cp/order )
        {
            cp *= order;
            cp = min2(cp, pg);
        }

        t.prec(cp);
        x.prec(cp);
        d.prec(cp);

        log(x,t);     PR( print("\n log(x)=",t,SHRT); );

        sub(d,t,t);    PR( print("\n y:= d-log(x)=",t,SHRT); );

        jjassert( t.exp()<=0 );
        ap = -t.exp(); PR( cout << "\n ap=" << ap << endl; );
//        cout << "\n j=" << j << "  ap=" << ap << endl;

//        ratpoly(t, order+1, num, den, t);  PR( print("\n  poly=",t,SHRT); );
        expm1(t, order+1, tmp2, tmp);
        t = tmp2;
        PR( print("\n  poly=",t,SHRT); );

        mul(x,t,t);   PR( print("\n  x*poly=",t,SHRT); );

        add(x,t,x);   PR( print("\n x+x*poly=",x,SHRT); );


        if ( ap>=rpg )  break;
        if ( !check_last_step && (x.prec()>=pg) )  break;
    }
    // ---------------- end of ITERATION ---------------------

    jjassert( j<=max_rec ); // "No convergence"


    if ( xs==-1 )
    {
        inv(x,t);
        x = t;
    }

    return j;
}
//========================= end ==========================



//#define  SIMPLE_EXP  0  // define to use simple algorithm (fails for large d)

void
approx_exp(const hfloat &d, hfloat &c)
//
// Compute  c = exp(d)
//
// To avoid overflow for big arguments d
// set c := M*R^X (Mantissa, Radix, eXponent)
// then  d = log(M) + X * log(R)
// we use
//    X = floor( d/log(R) )
//    M = exp( d - X*log(R) )
//
// jjnote: hfloat d must fit into double
{
#ifdef  SIMPLE_EXP
#warning 'FYI: SIMPLE_EXP==1 in approx_exp()'
    double dd;
    hfloat2d(d,dd);
    dd = exp(dd);
    d2hfloat(dd,c);
#else

    double dd;
    hfloat2d(d,dd);
    double lr = log( (double)hfloat::radix() );
    double X = floor( dd/lr );
    double M = exp( dd-X*lr );
    d2hfloat(M,c);
    c.exp( c.exp()+(long)X );

#endif // SIMPLE_EXP
}
//=================== end ========================

