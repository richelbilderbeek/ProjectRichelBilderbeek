
#include "hfloat.h"
#include "hfdatafu.h"

#include <fxt/jjassert.h>
#include "hfparanoia.h"

void
mul2(const hfloat &x, hfloat &a)
{
#ifdef  HF_PARANOIA
    jjassert( x.OK() );
#endif

    a.copy(x);
    int t = dt_mul2( *a.data() );
    a.exp( a.exp() + t );

#ifdef  HF_PARANOIA
    jjassert( a.OK() );
#endif
}
//================= end ===================


void
div2(const hfloat &x, hfloat &a)
{
#ifdef  HF_PARANOIA
    jjassert( x.OK() );
#endif

    a.copy(x);
    int t = dt_div2( *a.data() );
    a.exp( a.exp() - t );

#ifdef  HF_PARANOIA
    jjassert( a.OK() );
#endif
}
//================= end ====================


void
mul2pow(const hfloat &x, long p, hfloat &a)
{
#ifdef  HF_PARANOIA
    jjassert( x.OK() );
#endif

    if ( p<0 )
    {
        div2pow(x, -p, a);
        return;
    }

    a.copy(x);

    if ( p==0 )  return;

    ulong n = (ulong)p;
#define  p  GONE
    ulong rb = hfdata::rxbits;
    ulong tt = n % rb;

    if ( tt!=0 )
    {
        if ( tt==1 )  mul2(a,a);
	else          mul(a, (ulong)1<<tt, a);
    }

    if ( n>=rb )
    {
        tt = n / rb;
//        if ( hfdata::rx2pw )  // radix is a power of 2
        if ( 2 == hfdata::rxbase )  // radix is a power of 2
        {
            a.exp( a.exp()+tt );
        }
        else
        {
            while( tt!=0 )  // repeated mul by the biggest pow of 2 that is <= rx
            {
                //            for (int j=0; j<rb; ++j)  mul2(a,a);
                mul(a, (ulong)1<<rb, a);  // jjnote: (1<<rb) is always > radix
                tt--;
            }
        }
    }

#ifdef  HF_PARANOIA
    jjassert( a.OK() );
#endif
}
//================= end =====================


void
div2pow(const hfloat &x, long p, hfloat &a)
{
#ifdef  HF_PARANOIA
    jjassert( x.OK() );
#endif

    if ( p<0 )
    {
        mul2pow(x, -p, a);
        return;
    }

    a.copy(x);

    if ( p==0 )  return;

    ulong n = (ulong)p;
#define  p  GONE
    ulong rb = hfdata::rxbits;
    ulong tt = n % rb;

    if ( tt!=0 )
    {
        if ( tt==1 )  div2(a, a);
	else          div(a, (ulong)1<<tt, a);
    }

    if ( n>=rb )
    {
        tt = n / rb;

        if ( hfdata::rx2pw )  // radix is a power of 2
        {
            a.exp( a.exp() - n );
        }
        else
        {
            while ( tt>0 )  // repeated div by the biggest pow of 2 that is <= rx
            {
                div(a, (ulong)1<<rb, a);  // jjnote: (1<<rb) is always > radix
                tt--;
            }
        }
    }

#ifdef  HF_PARANOIA
    jjassert( a.OK() );
#endif
}
//================= end =============


void
ldexp(const hfloat &x, long p, hfloat &a)
{
#ifdef  HF_PARANOIA
    jjassert( x.OK() );
#endif

    if ( 0==p )
    {
        a.copy(x);
        return;
    }

    if ( p>0 )
    {
        if ( 1==p )  mul2(x,a);
	else         mul2pow(x,p,a);
    }
    else
    {
        if ( -1==p )  div2(x,a);
	else          div2pow(x,-p,a);
    }

#ifdef  HF_PARANOIA
    jjassert( a.OK() );
#endif
}
//============== end ============
