
#include "hfloat.h"
#include "hfdatafu.h"

#include <fxt/jjassert.h>


static hfloat addsub_tmp(hfloat::longlimbs);  // jjnote: static hfloat
#define  tmp  addsub_tmp

class hfloatoid  // jjnote: semi ugly hack (to avoid a discard const)
{
public:
    hfdata *data;
    double exp;
    int sign;

    void link(const hfloat &g)
    {
        data = g.data();
        exp  = (double)g.exp();
        sign = g.sign();
    }
};

static hfloatoid big;
static hfloatoid sml;


int addsub(const hfloat &a, const hfloat &b, hfloat &c, int subq, ulong cp/*=0*/)
//
// 1.) any of a,b,c can be identical
// 2.) different exponents cause an offset in add/sub
// 3.) action is determined by the signs (of a and b) and subq
// 4.) any combination of precisions can occur
//
// subq determines the action:
//    0: c = a+b
//   +1: c = a-b
//
{

#ifdef  HF_PARANOIA
    jjassert( a.OK() );
    jjassert( b.OK() );
#endif

    jjassert( (subq==0) || (subq==+1) );

    if ( hfloat::forbid_unnormalized )  jjassert( a.normalized() );
    if ( hfloat::forbid_unnormalized )  jjassert( b.normalized() );


    if ( a.is_zero() )  // a==0
    {
        if ( b.is_zero() )  // && b==0
        {
            c.set_zero();
        }
        else
        {
            c.copy(b);
            if ( subq==+1 )  c.negate();
        }

        return 0;
    }

    if ( b.is_zero() )  // b==0
    {
        c.copy(a);  // copy a!=0
        return 0;
    }


    // -------- a!=0 and b!=0:
    if ( cp==0 )  cp = c.prec();

    int chsg=0;
    int  sq;  // whether to subtract mantissas

    int  ds = ( a.sign()!=b.sign() );
    if ( ds )  sq = (!subq);
    else       sq = subq;

    long dx = (long)(a.exp()-b.exp());
    if ( dx>0 )  // a>b
    {
        big.link(a);
	sml.link(b);
    }
    else         // b>a
    {
        if( subq && (ds^sq) )  chsg=1;

        big.link(b);
	sml.link(a);

        dx = -dx;
    }

    int i;
    if ( sq )    // SUBTRACT:
    {
        i = dt_sub( *big.data, *sml.data, dx, *c.data(), cp);

        c.sign( i * big.sign );
        c.exp( (long)big.exp );
    }
    else      // ADD:
    {
        i = dt_add( *big.data, *sml.data, dx, *c.data(), cp);

        c.sign( big.sign );
        c.exp( (long)big.exp );

        c.exp( c.exp()+i );
    }

    if ( chsg )  c.negate();

    c.normalize();

    if ( hfloat::forbid_unnormalized )  jjassert( c.normalized() );

#ifdef  HF_PARANOIA
    jjassert( c.OK() );
#endif

    return 0;
}
//=========================== end ==========================


void
add(const hfloat &a, const hfloat &b, hfloat &c, ulong cp/*=0*/)
{
#ifdef  HF_PARANOIA
    jjassert( a.OK() );
    jjassert( b.OK() );
#endif

    addsub(a, b, c, 0, cp);

#ifdef  HF_PARANOIA
    jjassert( c.OK() );
#endif
}
//===============================================


void
add(const hfloat &a, long i, hfloat &c)
{
#ifdef  HF_PARANOIA
    jjassert( a.OK() );
#endif

    i2hfloat_prec_adj(i, tmp);
    addsub(a, tmp, c, 0);

#ifdef  HF_PARANOIA
    jjassert( c.OK() );
#endif
}
//===============================================

void
add(const hfloat &a, ulong i, hfloat &c)
{
#ifdef  HF_PARANOIA
    jjassert( a.OK() );
#endif

    u2hfloat_prec_adj(i, tmp);
    addsub(a, tmp, c, 0);

#ifdef  HF_PARANOIA
    jjassert( c.OK() );
#endif
}
//===============================================


void
sub(const hfloat &a, const hfloat &b, hfloat &c, ulong cp/*=0*/)
{
#ifdef  HF_PARANOIA
    jjassert( a.OK() );
    jjassert( b.OK() );
#endif

    addsub(a, b, c, 1, cp);

#ifdef  HF_PARANOIA
    jjassert( c.OK() );
#endif
}
//===============================================


void
sub(const hfloat &a, long i, hfloat &c)
{
#ifdef  HF_PARANOIA
    jjassert( a.OK() );
#endif

    i2hfloat_prec_adj(i, tmp);
    addsub(a, tmp, c, 1);

#ifdef  HF_PARANOIA
    jjassert( c.OK() );
#endif
}
//===============================================

void
sub(const hfloat &a, ulong i, hfloat &c)
{
#ifdef  HF_PARANOIA
    jjassert( a.OK() );
#endif

    u2hfloat_prec_adj(i, tmp);
    addsub(a, tmp, c, 1);

#ifdef  HF_PARANOIA
    jjassert( c.OK() );
#endif
}
//===============================================


void
sub(long i, const hfloat &b, hfloat &c)
{
#ifdef  HF_PARANOIA
    jjassert( b.OK() );
#endif

    i2hfloat_prec_adj(i, tmp);
    addsub(tmp, b, c, 1);

#ifdef  HF_PARANOIA
    jjassert( c.OK() );
#endif
}
//===============================================

void
sub(ulong i, const hfloat &b, hfloat &c)
{
#ifdef  HF_PARANOIA
    jjassert( a.OK() );
#endif

    u2hfloat_prec_adj(i, tmp);
    addsub(tmp, b, c, 1);

#ifdef  HF_PARANOIA
    jjassert( c.OK() );
#endif
}
//===============================================

