
#include "hfloat.h"
#include "hfverbosity.h"

#include <fxt/jjassert.h>
#include "hfparanoia.h"

#define  USE_ITSQRT  1  // 0 (sqrt by iroot) or 1 (sqrt by fast sqrt)

//#if  ( USE_ITSQRT != 0 )  // tune.h
//#warning '  FYI:  sqrt uses  sqrt_iteration '
//#else  // USE_ITSQRT
//#warning '  FYI:  sqrt uses  iroot_iteration and final multiply '
//#endif  // USE_ITSQRT


void
sqrt(const hfloat &d, hfloat &c)
{
#ifdef  HF_PARANOIA
    jjassert( d.OK() );
#endif

    if ( d.is_zero() )
    {
        c.set_zero();
        return;
    }

    jjassert( !d.negative() ); // "negative arg in sqrt"

    hfloat *cp = &c;
    if ( c.data()==d.data() )
    {
        cp = new hfloat(c.prec());  // jjnote: temporary hfloat
    }

#if  ( USE_ITSQRT != 0 )

    if ( c.prec()>=512 )  sqrt_iteration(d,(*cp));
    else
    {
        iroot_iteration(d, 2, (*cp));
        mul(d, (*cp), (*cp));
    }
#else  // USE_ITSQRT

    iroot_iteration(d, 2, (*cp));
    mul(d, (*cp), (*cp));

#endif  // USE_ITSQRT


    if ( cp != &c )
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
sqrt(long i, hfloat &c)
{
    if ( i==0 )
    {
        c.set_zero();
        return;
    }

    jjassert( i >= 0 ); // "negative arg in sqrt"

    static hfloat x(hfloat::longlimbs);  // jjnote: static hfloat
    i2hfloat_prec_adj(i,x);

    iroot_iteration(x,2,c);
    c *= x;

#ifdef  HF_PARANOIA
    jjassert( c.OK() );
#endif
}
// -----------------


void
root(const hfloat &a, long e, hfloat &c)
{
#ifdef  HF_PARANOIA
    jjassert( a.OK() );
#endif

    if ( a.is_zero() )
    {
        jjassert( e>=0 ); // "zero arg for inverse root"
        if ( e>=1 )  c.set_zero();
        if ( e==0 )  i2hfloat(1,c);
        return;
    }

    if ( e>=0 )
    {
        if ( !(e&1) )  jjassert( a.positive() ); // "radicand negative with even root"
        if ( e>3 )   rootn(a,e,c);
        if ( e==3 )  cbrt(a,c);
	if ( e==2 )  sqrt(a,c);
        if ( e==1 )  c.copy(a);
        if ( e==0 )  i2hfloat(1,c);
    }
    else  // --- negative => inverse root
    {
	if ( e==-1 )  inv(a,c);
	if ( e==-2 )  isqrt(a,c);
        if ( e<=-3 )  iroot(a,-e,c);
    }

#ifdef  HF_PARANOIA
    jjassert( c.OK() );
#endif
}
// -----------------


void
root(long i, long r, hfloat &c)
{
    static hfloat x(hfloat::longlimbs);  // jjnote: static hfloat
    i2hfloat_prec_adj(i,x);
    root(x,r,c);

#ifdef  HF_PARANOIA
    jjassert( c.OK() );
#endif
}
// -----------------


void
isqrt(const hfloat &d, hfloat &c)
//
// startprec here for the inv sqrt
// (which has to be in c)
//
{
#ifdef  HF_PARANOIA
    jjassert( d.OK() );
#endif

    jjassert( d.positive() ); // "negative arg in isqrt"
    iroot_iteration(d,2,c);

#ifdef  HF_PARANOIA
    jjassert( c.OK() );
#endif
}
// -----------------


void
isqrt(long i, hfloat &c)
{
    jjassert( i > 0 );  // "arg<=0 in isqrt"
    static hfloat x(hfloat::longlimbs);  // jjnote: static hfloat
    i2hfloat_prec_adj(i,x);
    isqrt(x,c);

#ifdef  HF_PARANOIA
    jjassert( c.OK() );
#endif
}
// -----------------


void
iroot(const hfloat &d, ulong r, hfloat &c)
{
#ifdef  HF_PARANOIA
    jjassert( d.OK() );
#endif

    if ( r!=1 )  jjassert( d.positive() ); // "negative arg for inverse root"
    iroot_iteration(d,r,c);

#ifdef  HF_PARANOIA
    jjassert( c.OK() );
#endif
}
// -----------------


void
iroot(long i, ulong r, hfloat &c)
{
    static hfloat x(hfloat::longlimbs);  // jjnote: static hfloat
    i2hfloat_prec_adj(i,x);
    iroot(x,r,c);

#ifdef  HF_PARANOIA
    jjassert( c.OK() );
#endif
}
// -----------------


void
rootn(const hfloat &d, long r, hfloat &c)
//
// startprec here for the inv root !
// (which has to be in c)
//
// for any r that factors nontrivial the inversion can be avoided
// e.g.: root(d,6)==invroot(invroot(d,2),3)
// i.e.: d^(1/6)==(d^(-(1/2))^(-1/3)
//
//
{
#ifdef  HF_PARANOIA
    jjassert( d.OK() );
#endif

    if ( d.is_zero() )
    {
        c.set_zero();
        return;
    }

    jjassert( d.positive() ); // "negative arg for iroot (in rootn)"
    iroot_iteration(d,r,c);
    inv(c,c);

#ifdef  HF_PARANOIA
    jjassert( c.OK() );
#endif
}
// -----------------


void
cbrt(const hfloat &d, hfloat &c)
//
// d^((r-1)/r) is computed then a
// final multiplication with d gives d^(1/r)
//
{
#ifdef  HF_PARANOIA
    jjassert( d.OK() );
#endif

     if ( d.is_zero() )
    {
        c.set_zero();
        return;
    }

    hfloat *cp = &c;
    if ( c.data()==d.data() )
    {
        cp = new hfloat(c.prec());  // jjnote: temporary hfloat
    }

    sqr(d,*cp);
    iroot_iteration(*cp,3,*cp,0);
    mul(*cp,d,*cp);

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
cbrt(long i, hfloat &c)
{
    static hfloat x(hfloat::longlimbs);  // jjnote: static hfloat
    i2hfloat_prec_adj(i,x);
    cbrt(x,c);

#ifdef  HF_PARANOIA
    jjassert( c.OK() );
#endif
}
// -----------------


void
root_x(const hfloat &d, ulong r, hfloat &c)
//
// alternative n-th root routine:
// may be good if
// one wants the hi prec root of a few-digits number
// or generally for the third root (see above)
//
// d^((r-1)/r) is computed then a
// final multiplication with d gives d^(1/r)
//
{
#ifdef  HF_PARANOIA
    jjassert( d.OK() );
#endif

    hfloat *cp = &c;
    if ( c.data()==d.data() )
    {
        cp = new hfloat(c.prec());  // jjnote: temporary hfloat
    }

    pow(d,r-1,*cp);
    iroot_iteration(*cp,r,*cp,0);
    mul(*cp,d,*cp);

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
root_x(long i, ulong r, hfloat &c)
{
    static hfloat x(hfloat::longlimbs);  // jjnote: static hfloat
    i2hfloat_prec_adj(i,x);
    root_x(x,r,c);

#ifdef  HF_PARANOIA
    jjassert( c.OK() );
#endif
}
// -----------------
