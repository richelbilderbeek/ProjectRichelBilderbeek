
#include "hfloat.h"
#include "hfverbosity.h"
#include "hfdatafu.h"

#include <fxt/aux0/sign.h>  // Abs()

#include <fxt/jjassert.h>
#include "hfparanoia.h"


#define  USE_ITINV  0  // 0 (inv by iroot) or 1 (slightly faster inv, FAILS!)
//#define  CHECK_INV  // define for check (slowdown!)

#if  ( USE_ITINV != 0 )
#error 'inv_iteration fails for input with arg.prec() != result.prec()'
#warning 'FYI:  inv() uses inv_iteration '
#else
//#warning 'FYI:  inv() uses iroot_iteration'
#endif

#ifdef  CHECK_INV
#warning 'CHECK_ITINV activated =--> sloooow '
#endif


void
inv(const hfloat &d, hfloat &c)
{
#ifdef  HF_PARANOIA
    jjassert( d.OK() );
    if ( hfloat::forbid_unnormalized )  jjassert( d.normalized() );
#endif

#ifdef  CHECK_INV
    ulong tp = c.prec();  if ( tp>d.prec() )  tp = d.prec();
    hfloat t(tp);
    t = d;
#endif  // CHECK_INV

#if  ( USE_ITINV != 0 )
    inv_iteration(d,c);
#else  // USE_ITINV
    iroot_iteration(d,1,c);
#endif  // USE_ITINV

#ifdef CHECK_INV
    mul(c,t,t);
    long dl;  dl=cmp1(t);  dl = tp-dl;
    if ( dl>15 )
    {
        cout << "inv(): limb-diff=" << dl << "  of " << tp << endl;
        print("d=\n",d);
        print("1/d=\n",c);
        print("1=?=\n",t);
        jjassert( 0 );
    }
#endif  // CHECK_INV


#ifdef  HF_PARANOIA
    jjassert( c.OK() );
#endif
}
// -----------------


void
div(const hfloat &a, long i, hfloat &c, long *rem/*=0*/)
//
// c   = a / i
// rem = a % i
//
{
#ifdef  HF_PARANOIA
    jjassert( a.OK() );
#endif

    ulong u = Abs(i);
    ulong urem;
    div(a, u, c, &urem);
    if ( rem ) *rem = (long)urem;
    if ( i<0 )  c.negate();


#ifdef  HF_PARANOIA
    jjassert( c.OK() );
#endif
}
// -----------------


void
div(const hfloat &a, ulong u, hfloat &c, ulong *rem/*=0*/)
//
// c   = a / u
// rem = a % u
//
{
#ifdef  HF_PARANOIA
    jjassert( a.OK() );
#endif

    c.copy(a);
    int dx = dt_div_sh(*c.data(), u, rem);
    c.exp( c.exp() - dx );


#ifdef  HF_PARANOIA
    jjassert( c.OK() );
#endif
}
// -----------------


void
div(const hfloat &a, const hfloat &b, hfloat &c)
{
#ifdef  HF_PARANOIA
    jjassert( a.OK() );
    jjassert( b.OK() );
#endif

    if ( c.data()!=a.data() )
    {
        inv(b, c);
        mul(a, c, c);
    }
    else
    {
        hfloat t(c.prec());  // jjnote: temporary hfloat
        inv(b,t);
        mul(a,t,t);
        c = t;
    }

#ifdef  HF_PARANOIA
    jjassert( c.OK() );
#endif
}
// -----------------


void
div_by_radix_pow(const hfloat &a, int ex, hfloat &b)
{
#ifdef  HF_PARANOIA
    jjassert( a.OK() );
#endif

    b = a;
    b.exp( b.exp()-ex );

#ifdef  HF_PARANOIA
    jjassert( b.OK() );
#endif
}
// -----------------


void
fmod(const hfloat &a, const hfloat &b, hfloat &c)
//
// c := b*frac(a/b)
//
{
#ifdef  HF_PARANOIA
    jjassert( a.OK() );
    jjassert( b.OK() );
#endif

    hfloat *cp = &c;
    if ( b.data()==c.data() )
    {
        cp = new hfloat(c.prec());  // jjnote: temporary hfloat
    }

    div(a, b, *cp);
    frac(*cp, *cp);
    mul(*cp, b, *cp);  // b*frac( a/b )

    if ( cp!=&c )
    {
        c.copy(*cp);
        delete cp;
    }

#ifdef  HF_PARANOIA
    jjassert( c.OK() );
#endif
}
// -----------------


void
fmod(const hfloat &a, const hfloat &b, hfloat &c, hfloat &d)
//
// c := b*frac(a/b)
// d := floor(a/b)
//
// this relation holds: a ==  b*floor(a/b) + b*frac(a/b)
//
// note that the C function fmod uses 'round toward zero'
// instead of 'floor' used here
//
{
#ifdef  HF_PARANOIA
    jjassert( a.OK() );
    jjassert( b.OK() );
#endif

    jjassert ( c.data()!=d.data() );

    hfloat *cp = &c;
    if ( (c.data()==a.data()) || (c.data()==b.data()) )
    {
        cp = new hfloat(c.prec());  // jjnote: temporary hfloat
    }

    hfloat *dp = &d;
    if ( (d.data()==a.data()) || (d.data()==b.data()) )
    {
        dp = new hfloat(d.prec());  // jjnote: temporary hfloat
    }

    div(a, b, *cp);
    // use round0(c,d) to get an fmod like the c-function
    floor(*cp, *dp);   // floor( a/b )
    // use frac0(c,c) when using round0() above,
    // then this relation might be useful:
    //    a ==  b*round0(a/b) + b*frac0(a/b)
    frac(*cp, *cp);
    mul(*cp, b, *cp);   // b*frac( a/b )

    if ( cp!=&c )
    {
        c.copy(*cp);
        delete cp;
    }

    if ( dp!=&d )
    {
        d.copy(*dp);
        delete dp;
    }

#ifdef  HF_PARANOIA
    jjassert( c.OK() );
    jjassert( d.OK() );
#endif
}
// -----------------

