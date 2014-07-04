
#include "hfloat.h"

#include <fxt/jjassert.h>
#include "hfparanoia.h"


void
mulpow(const hfloat &a, long b, long ex, hfloat &c)
//
// c = a*(b^ex)
//
{
#ifdef  HF_PARANOIA
    jjassert( a.OK() );
#endif

    if( b==0 )  // a*0^ex = 0
    {
	c = 0;
	return;
    }

    if( ex==0 )  // a*b^0 = 1  (b!=0)
    {
	c = a;
	return;
    }

    if( b==2 )
    {
        ldexp(a,ex,c);  // a*2^ex
        return;
    }

    c = a;
    if( ex<0 )  // a*b^(-x)
    {
	ex = -ex;
	for (long i=0; i<ex; ++i )  c /= b;
    }
    else       // a*b^(+x)
    {
	for (long i=0; i<ex; ++i )  c *= b;
    }

#ifdef  HF_PARANOIA
    jjassert( c.OK() );
#endif
}
//============== end ============


