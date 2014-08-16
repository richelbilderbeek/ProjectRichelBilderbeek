
#include "hfdatafu.h"
#include <fxt/aux1/copy.h>  // copy()
#include <fxt/aux1/shift.h>  // shift_right()
#include <fxt/sort/minmaxmed23.h>  // min2(), max2(), max3()

#include "workspace.h"

#include <fxt/jjassert.h>
#include "dtparanoia.h"


//#define  USE_WORKSPACE

#include <fxt/aux1/copy.h>  // copy0()


int
dt_sub(const hfdata &a, const hfdata &b, ulong dx, hfdata &c, ulong cp)
// c[k] = a[k+dx]-b[k]
// return ==-1 indicates sign change (else ==+1)
{
#ifdef  DT_PARANOIA
    jjassert( a.OK() );
    jjassert( b.OK() );
#endif

    const uint rx = (uint)hfdata::rx;
    const LIMB * const ad = a.dig();
    const LIMB * const bd = b.dig();
    LIMB * const cd = c.dig();
    const ulong ap = a.prec();
    const ulong bp = b.prec();
//    const ulong cp = c.prec();

    if ( dx>=cp )
    {
        copy0(ad, ap, cd, cp);
        return 1;
    }

#if defined USE_WORKSPACE
#warning "FYI: dt_sub() uses workspace"
    LIMB *rd;
    ulong rp = max3(ap, bp, cp);
    workspace::get_ws(rd, rp);
    copy0(ad, ap, rd, rp);
    int i = i_sub_from(rd, rp, dx, bd, bp, rx);
    copy0(rd, rp, cd, cp);
    workspace::let_ws();

#else   // USE_WORKSPACE
    int   i;
    if ( ad==bd )  // a, a, c
    {
        null(cd, cp);  // c=0
        i = 0;
    }
    else // ad!=bd
    {
        if ( ad==cd )  // a, b, a
        {
            i = i_sub_from(cd, cp, dx, bd, bp, rx);  // c-=b
        }
        else // ad!=cd
        {
            if ( bd!=cd )  // a, b, c
            {
                copy0(ad, ap, cd, cp);  // c=a
                i = i_sub_from(cd, cp, dx, bd, bp, rx);  // c+=b
            }
            else  // a, b, b
            {
                shift_right(cd, bp, dx);
                if ( bp>ap )  i = i_negate(cd+ap, bp-ap, rx);
                else          i = 0;
                i = i_sub_from2(cd, min2(ap,bp), ad, rx, i);
            }
        }
    }
#endif   // USE_WORKSPACE

    if ( 0==i )  i = 1;  // last borrow == 0
    else  // last borrow == 1  ==> sign change
    {
        i_negate(cd, cp, rx);
        i = -1;
    }

#ifdef  DT_PARANOIA
    jjassert( c.OK() );
#endif

    return i;
}
//===================== end =====================



int
i_sub_from(LIMB *ad, ulong an, ulong dx, const LIMB *bd, ulong bn, const uint rx)
// ad[k] = ad[k+dx]-bd[k]
// returns last borrow (0 or 1)
{
    if ( dx>=an )  return 0;  // no overlap at all

    int cy = i_sub_from(ad+dx, min2(an-dx,bn), bd, rx);  // subtract overlapping region
    if ( (dx>0) && cy )  cy = i_borrow(ad, dx, cy, rx);  // borrow thru nonoverlapping region
    return cy;
}
//====================== end =====================


int
i_sub_from2(LIMB *ad, ulong n, const LIMB *bd, const uint rx, int cy)
// bd[k] -= ad[k]   k = n-1...0
// returns last borrow (0 or 1)
{
    for (long k=n-1; k>=0; --k)  // sub
    {
        int rk = bd[k]-ad[k]-cy;

        if ( rk<0 ) // borrow one
        {
	    rk += rx;
            cy = 1;
        }
        else
        {
            cy = 0;
        }

	ad[k] = (LIMB)rk;
    }

    return cy;
}
//===================== end =====================


int
i_borrow(LIMB *d, ulong n, int cy, const uint rx)
// d[k] -= cy(k)  k = n-1...0
// returns last borrow (0 or 1)
{
    for(long k=n-1 ; (k>=0) && (cy!=0) ; --k)
    {
        int rk = d[k]-cy;

        if( rk<0 ) // borrow one
        {
	    rk += rx;
            cy = 1;
        }
        else
        {
            cy = 0;
        }

	d[k] = (LIMB)rk;
    }

    return cy;
}
//===================== end =====================

int
i_sub_from(LIMB *ad, ulong n, const LIMB *bd, const uint rx)
// ad[k] -= bd[k]   k = n-1...0
// returns last borrow (0 or 1)
{
    int cy = 0;
    for (long k=n-1; k>=0; --k)  // sub
    {
        int rk = ad[k]-bd[k]-cy;

        if ( rk<0 ) // borrow one
        {
	    rk += rx;
            cy = 1;
        }
        else
        {
            cy = 0;
        }

	ad[k] = (LIMB)rk;
    }

    return cy;
}
//===================== end =====================


int
i_negate(LIMB *ad, ulong ap, const uint rx)
//
// ad[k] = 0-ad[k]-cy(k)
// return index of the first LIMB != 0
//
{
    long k;
    int cy = 0;
    for (k=ap-1; k>=0; --k)  // sub
    {
        int rk = 0-ad[k]-cy;

        if ( rk<0 ) // borrow one
        {
	    rk += rx;
            cy = 1;
        }
        else
        {
            cy = 0;
        }

	ad[k] = (LIMB)rk;
    }

    return cy;
}
//====================== end  =====================
