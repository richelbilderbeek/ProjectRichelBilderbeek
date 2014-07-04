
#include "hfdata.h"
#include <fxt/aux1/shift.h>  // shift_right(), shift_left()

#include <fxt/jjassert.h>
#include "dtparanoia.h"


int
dt_mul2(hfdata &a)
// Return whether shift happened
{
#ifdef  DT_PARANOIA
    jjassert( a.OK() );
#endif

    const uint rx = (uint)hfdata::rx;
    ulong cy;
    LIMB *ad = a.dig();


//    if ( hfdata::rx2pw )  // radix is a power of 2
//    if ( 2 == hfdata::rxbase )  // radix is a power of 2
//    {
//        const int nine = rx-1;
//	ulong t = 0;
//	for (long k=a.prec()-1; k>=0; --k)
//	{
//	    t |= (ulong)ad[k]<<1;
//	    ad[k] = (LIMB)( t & nine );
//	    t >>= (hfdata::rxbits);
//	}
//
//	cy = t;
//    }
//    else  // radix _not_ a power of 2
    {
	cy = 0;
	for (long k=a.prec()-1; k>=0; --k)
	{
	    ulong t = ((ulong)ad[k]<<1)+cy;

	    if ( t>=(ulong)rx )
	    {
		cy = 1;
		ad[k] = (LIMB)( t - rx );
	    }
	    else
	    {
		cy = 0;
		ad[k] = (LIMB)t;
	    }
	}
    }

    int ret;
    if ( cy!=0 )
    {
//        shift_right(ad, a.prec(), 1);
        shift_right1(ad, a.prec());

        ad[0] = 1;
        ret = 1;
    }
    else  ret = 0;

#ifdef  DT_PARANOIA
    jjassert( a.OK() );
#endif

    return ret;
}
//===================== end =========================



int
dt_div2(hfdata &a)
// Return whether shift happened
{
#ifdef  DT_PARANOIA
    jjassert( a.OK() );
#endif

    const uint rx = (uint)hfdata::rx;
    ulong cy;
    LIMB *ad = a.dig();


    if ( hfdata::rx2pw )  // radix is a power of 2
    {
	ulong t = 0;
	for (ulong k=0; k<a.prec(); ++k)
	{
	    t |= ad[k];
	    cy = t&1;
	    ad[k] = (LIMB)( t >> 1 );
	    t = cy << (hfdata::rxbits);
	}
    }
    else  // radix _not_ a power of 2
    {
	cy = 0;
	for (ulong k=0; k<a.prec(); ++k)
	{
	    ulong t = ad[k];

	    if ( cy!=0 )  t += rx;
	    cy = t&1;
            ad[k] = (LIMB)(t>>1);
	}
    }

    int ret;
    if ( ad[0]==0 )
    {
//        shift_left(ad, a.prec(), 1);
        shift_left1(ad, a.prec());

        ret = 1;
    }
    else  ret = 0;

#ifdef  DT_PARANOIA
    jjassert( a.OK() );
#endif

    return ret;
}
//===================== end ======================

