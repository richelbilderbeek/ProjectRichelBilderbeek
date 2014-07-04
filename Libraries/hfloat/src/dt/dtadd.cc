
#include <fxt/sort/minmaxmed23.h>  // min2(), max2(), max3()
#include <fxt/aux1/copy.h>  // copy0()
#include <fxt/aux1/shift.h>  // shift_right()

#include <fxt/jjassert.h>

#include "workspace.h"

#include "dtparanoia.h"
#include "hfdatafu.h"

//#define  USE_WORKSPACE

#include <fxt/aux1/copy.h>  // copy()

int
dt_add(const hfdata &a, const hfdata &b, ulong dx, hfdata &c, ulong cp)
// c[k] = a[k+dx]+b[k]
// Return last carry (increment for exponent)  (0 or 1)
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
        return  0;
    }

#if defined USE_WORKSPACE
#warning "FYI: dt_add() uses workspace"
    LIMB *rd;
    ulong rp = max3(ap, bp, cp);
    workspace::get_ws(rd, rp);
    copy0(ad, ap, rd, rp);
    int i = i_add_to(rd, rp, dx, bd, bp, rx);
    copy0(rd, rp, cd, cp);
    workspace::let_ws();

#else   // USE_WORKSPACE
    int   i;
    if ( ad==bd )  // a, a, c
    {
        copy0(ad, ap, cd, cp);  // c = a
        i = i_add_to(cd, cp, dx, bd, bp, rx);  // c+=b
        // ... or: c= 2*a
    }
    else // ad!=bd
    {
        if ( ad==cd )  // a, b, a
        {
            i = i_add_to(cd, cp, dx, bd, bp, rx);  // c+=b
        }
        else // ad!=cd
        {
            if ( bd!=cd )  // a, b, c
            {
                copy0(ad, ap, cd, cp);  // c=a
                i = i_add_to(cd, cp, dx, bd, bp, rx);  // c+=b
            }
            else  // a, b, b
            {
                shift_right(cd, cp, dx);
                i = i_add_to(cd, min2(cp, ap), ad, rx);
            }
        }
    }
#endif   // USE_WORKSPACE

    if ( i )
    {
//        shift_right(cd, cp, 1);
        shift_right1(cd, cp);

        cd[0] = (LIMB)i;
    }

#ifdef  DT_PARANOIA
    jjassert( c.OK() );
#endif

    return i;
}
// -------------------------



uint
i_add_to(LIMB *ad, ulong an, ulong dx, const LIMB *bd, ulong bn, const uint rx)
// c[k] = a[k+dx]+b[k]
// Return last carry (0 or 1)
{
    if ( dx>=an )  return 0;  // no overlap at all

    uint cy = i_add_to(ad+dx, min2(an-dx,bn), bd, rx);  // add overlapping region
    if ( (dx>0) && cy )  cy = i_carry(ad, dx, cy, rx);  // carry thru nonoverlapping region
    return cy;
}
// -------------------------


uint
i_carry(LIMB *d, ulong n, uint cy, const uint rx)
// d[k] += cy(k)  k = n-1...0
{
    for (long k=n-1; (k>=0) && (cy!=0) ; --k)
    {
        uint rk = d[k]+cy;

        if ( rk>=rx )
        {
	    rk -= rx;
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
// -------------------------


uint
i_add_to(LIMB *ad, ulong n, const LIMB *bd, const uint rx)
// ad[k] += bd[k]   k = n-1...0
// Return last carry (0 or 1)
{
    uint cy = 0;
    for (long k=n-1; k>=0; --k)
    {
        uint rk = ad[k]+bd[k]+cy;

        if ( rk>=rx )
        {
	    rk -= rx;
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
// -------------------------
