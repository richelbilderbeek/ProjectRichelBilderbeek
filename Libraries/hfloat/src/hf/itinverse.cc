
#include "hfloat.h"
#include "hfverbosity.h"
#include <fxt/sort/minmaxmed23.h>  // min2(), max2()
#include <fxt/aux1/copy.h>  // null()
#include <fxt/bits/bit2pow.h>    // next_pow_of_2()

#include <fxt/jjassert.h>
#include "hfparanoia.h"

#include <cmath>
#include <fxt/fxtio.h>

// for debug:
#define PR(x)
#define PRP    0


// jjnote: EXPERIMENTAL: fails in some cases !

int
inv_iteration(const hfloat &dd, hfloat &x, ulong startprec/*=0*/)
//
// 1/d == x*(1+y+y^2+y^3+...)  where y:=(1-d*x)
// computing the second order iteration
// x += x*(1-d*x)  as  x += x-d*x*x
// is slightly better than the special case r=1 of the
// general inverse-root iteration in itiroot.cc
//
{
#ifdef  HF_PARANOIA
    jjassert( dd.OK() );
#endif

    PR( set_pretty_print(false); );

    jjassert( !dd.is_zero() );

    hfloat d(64);  // jjnote: static hfloat
    d.prec( dd.prec() );   // possible resize
    d.copy(dd);
#define  dd  GONE

    static hfloat tt(64);  // jjnote: static hfloat for third order term

    PR( cout << __PRETTY_FUNCTION__ << endl; );
    if ( hfverbosity::itbegin )  cout << "\nIT_INV{:\n";

    long  xe = d.exp();
    d.exp( 0 );    // remove exponent for calculations
    x.exp( 0 );

    const ulong pg = x.prec();         // precision goal
    const ulong rpg = (pg>=4?pg-4:1);  // jjnote: magic: realistic precision goal
    ulong pr = min2((ulong)64, pg);

    PR( print("\n inv: d=\n",d,64); );
    PR( cout << "startprec=" << startprec << endl; );

    int j = 0;
    if ( startprec>=rpg )  goto done;  // nothing to do

    { // computation:
        ulong ap;  // achieved precision
        if ( startprec!=0 )  ap = startprec;
        else
        {
            approx_invpow(d,x,-1);
            ap = 3;  // assume 3 limbs are correct
            if ( ap>=rpg )  goto done;
        }

        static hfloat t(pg);  // jjnote: temporary hfloat

        ulong mp = 16;
        if ( ap<mp )
        {
            t.prec(2*mp);
            tt.prec(mp);
            mul(x, mp, d, mp, tt, 2*mp);   // d*x
            sub(1,tt,tt);                  // y = 1-d*x
            t = tt;
            sqr(tt,tt);
            add(tt,t,t);                   // y + y^2
            mul(tt, mp, t, mp, tt, 2*mp);  // y^2*(y+y^2) = y^3 + y^4
            add(tt,t,t);                   // y + y^2 + y^3 + y^4
            add(t,(ulong)1,t);             // 1 + y + y^2 + y^3 + y^4
            mul(t, mp, x, mp, x, 2*mp);    // x*(1 + y + y^2 + y^3 + y^4)
            ap = 7;
        }

        pr = next_pow_of_2( ap );
        pr = min2(pr, pg);
        PR( hfloat z(pg); long tap; );

        PR( mul(x,d,z);  z-=1;   print("x0_PREC=",z,4); );

        ulong i3 = 16;  // prec of third order term
        const int maxit = (int)(8+log((double)pg)/log(2.0));
        pr = 16;
        for (j=1; j<maxit; ++j)
        {
            PR( cout << " ------  j=" << j << "  pr=" << pr << "  ap=" << ap << endl; );
            if ( 2*ap >= pr )  pr = min2(2*pr, pg);
//            if ( pr<16 )  pr = 16;
            PR( cout << " ------  j=" << j << "  pr=" << pr << "  ap=" << ap << endl; );
            ulong hp = pr/2;
            x.prec(pr);
            t.prec(pr);

            // second order term:
            PR( print("\n ------  x= \n",x,PRP); );
            null(x.data()->dig()+hp, hp); // jjnote: STATEMENT MUST BE HERE
            sqr(x, hp, t, pr);                     // x*x    half prec square
            PR( print("\n  x^2= ",t,PRP); );
            mul(t, pr, d, pr, t, pr);              // x*x*d  full prec mult
            PR( print("\n  d*x^2= ",t,PRP); );
            sub(x, t, t);                          // x-x*x*d = x*(1-x*d)
            PR( print("\nx-d*x^2= ",t,PRP); );
            PR( cout << "-t.exp()=" << -t.exp() << endl; );
            add(x, t, x);                          // x + x*(1-x*d)
            PR( print("\n new x = ",x,PRP); );
            PR( mul(x,d,z);  z-=1;   print("x2_PREC=",z,4);  tap=-z.exp(); );

            // third order term:
            null(t.data()->dig()+i3, t.size()-i3);
            t.prec(2*i3);
            sqr(t, i3, t, 2*i3);           // (x-x*x*d)^2
            mul(t, i3, d, i3, t, 2*i3);    // d*(x-x*x*d)^2 = x*(1-x*d)^2
            PR( print("\n  3rd.= ",t,PRP); );
            add(x, t, x);                  // x + x*(1-x*d) + x*(1-x*d)^2

            ap = 2 * -t.exp() - 1;
            PR( mul(x,d,z);  z-=1;   print("***** x3_PREC=",z,4);  tap=-z.exp(); );
            PR( cout << "    tap=" << tap << "  ap=" << ap << "  diff=" << (long)tap-(long)ap << endl; );
            if ( ap>pr )  ap = pr;
            if ( hfverbosity::itprec )  cout << " (" << ap << "," << pr << ")\n";

            if ( ap>=rpg )  break;
            if ( pr>16 )  jjassert( ap>pr/3 );
        }
        jjassert( j!=maxit ); // "inv_iteration(): no convergence"

        x.exp( x.exp()-xe );  // exponent of result
    }

 done:
    if ( hfverbosity::itbegin )  cout << "}\n";

#ifdef  HF_PARANOIA
    jjassert( d.OK() );
    jjassert( x.OK() );
#endif

    return j;
}
// =================== end ================
