
#include "hfloat.h"
#include "hfverbosity.h"
#include "hfdatafu.h"

#include <fxt/aux0/sign.h>  // Abs()

#include <fxt/jjassert.h>
#include "hfparanoia.h"

#ifdef  HF_PARANOIA
#warning "++++++++++++++++++++++++++++++++++++++++"
#warning "HF_PARANOIA enabled, performance is gone"
#warning "++++++++++++++++++++++++++++++++++++++++"
#endif


void
sqr(const hfloat &a, hfloat &c)
{
    hfverbosity::say( hfverbosity::sqr );

#ifdef  HF_PARANOIA
    jjassert( a.OK() );
#endif

    if ( hfloat::forbid_unnormalized )  jjassert( a.normalized() );

    if ( a.is_zero() )
    {
        c.set_zero();
    }
    else
    {
        c.exp( a.exp() + a.exp() - 1 );

        c.sign( +1 );

        int dx = dt_sqr(*a.data(), *c.data());

        c.exp( c.exp()+dx );
    }

    if ( hfloat::forbid_unnormalized )  jjassert( c.normalized() );

#ifdef  HF_PARANOIA
    jjassert( c.OK() );
#endif
}
// -----------------

void
sqr(const hfloat &a, ulong ap, hfloat &c, ulong cp)
{
    hfverbosity::say( hfverbosity::sqr );

#ifdef  HF_PARANOIA
    jjassert( a.OK() );
#endif

    if ( hfloat::forbid_unnormalized )  jjassert( a.normalized() );

    if ( a.is_zero() )
    {
        c.set_zero();
    }
    else
    {
        c.exp( a.exp() + a.exp() - 1 );

        c.sign( +1 );

        //    if ( cp<c.prec() )  cp = c.prec();
        int dx = dt_sqr(*a.data(), ap, *c.data(), cp);

        c.exp( c.exp()+dx );
    }

    if ( hfloat::forbid_unnormalized )  jjassert( c.normalized() );

#ifdef  HF_PARANOIA
    jjassert( c.OK() );
#endif
}
// -----------------


void
mul(const hfloat &a, const hfloat &b, hfloat &c)
{
    hfverbosity::say( hfverbosity::mul );

#ifdef  HF_PARANOIA
    jjassert( a.OK() );
    jjassert( b.OK() );
#endif

    if ( hfloat::forbid_unnormalized )  jjassert( a.normalized() );
    if ( hfloat::forbid_unnormalized )  jjassert( b.normalized() );

    if ( a.is_zero() || b.is_zero() )
    {
        c.set_zero();
    }
    else
    {
        c.exp( a.exp()+b.exp()-1 );

        c.sign( a.sign()*b.sign() );

        int dx = dt_mul(*a.data(), *b.data(), *c.data());

        c.exp( c.exp()+dx );

        if ( hfloat::forbid_unnormalized )  jjassert( c.normalized() );
    }

#ifdef  HF_PARANOIA
    jjassert( c.OK() );
#endif
}
// -----------------

void
mul(const hfloat &a, ulong ap, const hfloat &b, ulong bp, hfloat &c, ulong cp)
{
    hfverbosity::say( hfverbosity::mul );

#ifdef  HF_PARANOIA
    jjassert( a.OK() );
    jjassert( b.OK() );
#endif

    if ( hfloat::forbid_unnormalized )  jjassert( a.normalized() );
    if ( hfloat::forbid_unnormalized )  jjassert( b.normalized() );

    if ( a.is_zero() || b.is_zero() )
    {
        c.set_zero();
    }
    else
    {
        c.exp( a.exp()+b.exp()-1 );

        c.sign( a.sign()*b.sign() );

        //    if ( cp<c.prec() )  cp = c.prec();
        int dx = dt_mul(*a.data(), ap, *b.data(), bp, *c.data(), cp);

        c.exp( c.exp()+dx );
    }

    if ( hfloat::forbid_unnormalized )  jjassert( c.normalized() );

#ifdef  HF_PARANOIA
    jjassert( c.OK() );
#endif
}
// -----------------


void
mul(const hfloat &a, long i, hfloat &c)
{
#ifdef  HF_PARANOIA
    jjassert( a.OK() );
#endif

    if ( a.is_zero() || (i==0) )
    {
        c.set_zero();
        return;
    }

    if ( i==-1 )
    {
        c.copy(a);
        c.sign( -c.sign() );
        return;
    }

    mul(a, (ulong)Abs(i), c);
    if ( i<0 )  c.negate();

#ifdef  HF_PARANOIA
    jjassert( c.OK() );
#endif
}
// -----------------

void
mul(const hfloat &a, ulong u, hfloat &c)
{
#ifdef  HF_PARANOIA
    jjassert( a.OK() );
#endif

    if ( a.is_zero() || (u==0) )
    {
        c.set_zero();
        return;
    }

    c.copy(a);
    if ( u==1 )  return;

    int dx = dt_mul_sh(*c.data(), u);
    c.exp( c.exp() + dx );

#ifdef  HF_PARANOIA
    jjassert( c.OK() );
#endif
}
// -----------------


void
mul_by_radix_pow(const hfloat &a, long ex, hfloat &b)
{
    b = a;
    b.exp( b.exp() + ex );
}
// -----------------

