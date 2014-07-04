
#include <cmath>
#include <fxt/fxtio.h>
#include <cstdlib>

#include "hfloat.h"
#include "hfverbosity.h"
#include "hfdatafu.h"  // dt_mantissa_to_double()
#include <fxt/sort/minmaxmed23.h>  // min2(), max2()
#include <fxt/bits/bit2pow.h>  // next_pow_of_2()

#include <fxt/jjassert.h>
#include "hfparanoia.h"


// for debug:
#define PR(x)
#define PRP  10

//#define IT_REDUCE_EXP  // define to reduce exponent in iteration (not needed)

int
iroot_iteration(const hfloat &dd, ulong ri, hfloat &x, ulong startprec/*=0*/)
//
//   Use
//   1/d^(1/r)== x*(1+y/r+y^2*(1+r)/(2! r^2)+y^3*(1+r)(1+2r)/(3! r^3)+...)
//   where y:=(1-d*x^r)
//
//   2nd order: x += x*(y/r)
//   3rd order: x += x*(y/r * [1+y*(1+r)/2/r])
//
//  returns the number of iterations needed
{
#ifdef  HF_PARANOIA
    jjassert( dd.OK() );
    if ( hfloat::forbid_unnormalized )  jjassert( dd.normalized() );
#endif

    startprec = 0;  // jjnote: iroot_iteration() FAILS with startprec!=0

//    jjassert( dd.data() != x.data() );

    static hfloat d(64);   // jjnote: static hfloat
    d.prec( dd.prec() );  // possible resize
    d = dd;
#define  dd  GONE

//    if ( startprec==0 )  null(x.data()->dig(), x.prec());

    static hfloat tt(64);  // jjnote: static hfloat for third order term

    if ( hfverbosity::itbegin )  cout << "\nIT_IROOT{" << ri << ":\n";

    const ulong dp0 = d.prec();

    const ulong pg = x.prec();  // precision goal
    const ulong rpg = (pg>4?pg-4:1);     // jjnote: magic: realistic precision goal

    long  r = (long)ri;

    PR( print("\n iroot: x=\n",x,64); );
    PR( cout << "startprec=" << startprec << endl; );

    int j = 0;
    if ( startprec>=rpg )  goto done;  // nothing to do

    { // computation:
        static hfloat t(pg);  // jjnote: temporary hfloat

#ifdef IT_REDUCE_EXP
        long  xe = (d.exp()/r)*r;
        PR( cout << "\n  d.exp()=" << d.exp() << "  xe=" << xe << endl; );
        d.exp( d.exp()-xe );  // remove (big) exponent for calculations
        x.exp( x.exp()+xe/r );  // exponent of result for computations

        int  s = d.sign();
        d.sign(+1);
#endif

        ulong ap;  // achieved precision
        if ( startprec!=0 )  ap = startprec;
        else
        {
            approx_invpow(d, x, -r);
            ap = 3;  // assume 3 limbs are correct
            if ( ap>=rpg )  goto done;
        }

        ulong pr;  // calculation precision
        pr = next_pow_of_2( ap );
        pr = min2(pr, pg);

        const int maxit = (int)(8+log((double)pg)/log(2.0));
        for (j=1; j<=maxit; ++j) // ------------ ITERATION ------------------
        {
            if ( 2*ap >= pr )  pr = min2(2*pr, pg);
//            ulong hp = pr/2;
            t.prec(pr);
            x.prec(pr);
            d.prec( min2(pr, dp0) );

            PR( print("\n ------  x= \n",x,PRP); );

            pow(x,r,t);

            mul(t,d,t);
            PR( print("\n  d*x^r= \n",t,PRP); );
            sub(1,t,t);
            PR( print("\n 1-d*x^r= \n",t,PRP); );
            div(t,r,t);
            PR( print("\n y/r:=(1-d*x^r)/r= \n",t,PRP); );

            ap += -t.exp();

            if ( (pr==pg) || (ap+63<=pr) )  // ===== THIRD ORDER TERM
            {
                // here:  t = y/r
                //  t += t*t*(1+r)/2 == (y/r)^2*(1+r)/2 == third order term

                if ( ap>=pr-4 )  // jjnote: magic: realistic loss of precision
                {
                    mul(t,x,t);
                    goto dort;
                }

                ulong ttp = next_pow_of_2(pr-ap);
                if ( hfverbosity::itprec )  cout << " (3rd: " << ttp << ") ";
                tt.prec( ttp );
                sqr(t, ttp, tt, ttp);

                if ( r!=1 )
                {
                    if ( (r&1)==0 )  // r even:
                    {
                        mul(tt, (1+r), tt);
                        div2(tt,tt);
                    }
                    else          // r odd:
                    {
                        mul(tt, (1+r)/2, tt);
                    }
                }

                add(t, tt, t);
                mul(t, x, t);   // jjnote: full prec mult

                ap += ttp;
            }                        // ===== end THIRD ORDER TERM
            else  // half prec mult
            {
                mul(t, t.prec()/2, x, x.prec()/2, t, t.prec());
            }
        dort:

            PR( print("\n add= \n",t,PRP); );
            add(x, t, x);

            if ( ap>pr )  ap = pr;
            if ( hfverbosity::itprec )  cout << " (" << ap << "," << pr << ")\n";

            if ( ap>=rpg )  break;
            jjassert( ap>pr/4 );
        }
        // ---------------- end of ITERATION ---------------------

        jjassert( j<=maxit ); // "iroot_iteration(): no convergence"


        if ( hfloat::check_itiroot_result )
        {
            pow(x, r, t);
            mul(t, d, t);
            sub(1, t, t);
            PR( print("\n check_result: 1-d*x^r= \n",t,PRP); );
            ap = -t.exp();
            jjassert( ap>=rpg );
        }

#ifdef IT_REDUCE_EXP
        x.exp( x.exp()-xe/r );  // exponent of result
        x.sign( s );
#endif
    }

done:
    if ( hfverbosity::itbegin )  cout << "}\n";

    return j;

#ifdef  HF_PARANOIA
    jjassert( d.OK() );
    jjassert( x.OK() );
#endif
}
// =================== end ================



//#define  SIMPLE_POW  // define to use simple algorithm (fails for large d)

void
approx_invpow(const hfloat &d, hfloat &c, long a)
//
// Compute  c = d^(1/a)
//
// To avoid overflow for big arguments d
// set d := M*R^X (Mantissa, Radix, eXponent)
// then c = M^(1/a) * R^(1/a*X)
//  == M^(1/a) * R^(mod(X,a)/a) * R^(div(X,a))
//  =: M^(1/a) * R^(Y/a) * R^(Z)
//
{

#ifdef  HF_PARANOIA
    jjassert( d.OK() );
#endif

#ifdef  SIMPLE_POW
#warning 'FYI: SIMPLE_POW==1 in approx_invpow()'
    double dd;
    hfloat2d(d, dd);
    dd = pow(dd, a);
    d2hfloat(dd, c);
#else
    double dd;
    dt_mantissa_to_double(*(d.data()), dd);
    dd = pow(dd, 1.0/(double)a);  // M^(1/a)

    long  Z = d.exp() / a;    // Z = X / a
    long  Y = d.exp() - a*Z;  // Y = X % a

    double tt = pow( (double)d.radix(), (double)Y/(double)a );  // R^(Y/a)
    dd *= tt;         // M^(1/a) * R^(Y/a)

    d2hfloat(dd, c);  // c =  M^(1/a) * R^(Y/a)
    c.exp( c.exp()+Z );   // c *= R^(Z)

#endif

#ifdef  HF_PARANOIA
    jjassert( c.OK() );
#endif
}
//=================== end ======================
