
#include "hfdatafu.h"
#include <fxt/aux1/copy.h>  // copy(), null()

#include "workspace.h"

#include <fxt/jjassert.h>
#include "dtparanoia.h"

#include <fxt/aux1/copy.h>  // copy0()

#include <fxt/aux0/swap.h>  // swap2()

//#warning "FYI: i_mul() uses workspace"

#define  AD  a.dig()
#define  BD  b.dig()
#define  AP  a.prec()
#define  BP  b.prec()


int
dt_mul_sh(hfdata &a, ulong i)
//
// Returns how many right shifts happened
//
{
#ifdef  DT_PARANOIA
    jjassert( a.OK() );
#endif

    if ( i==0 )
    {
        null( a.dig(), a.prec() );
        return 0;
    }

    static hfdata b(128);  // jjnote: enough for radix 2 and 128 bit integers
    b.prec( b.size() );
    ulong bp = dt_int_to_mantissa(i, b);
    b.prec(bp);

    int ret = (int)(bp - 1 + i_mul(AD, AP, BD, BP, AD, AP, (uint)hfdata::rx));

#ifdef  DT_PARANOIA
    jjassert( a.OK() );
#endif

    return ret;
}
//================ end ======================


int
i_mul(const LIMB *ad, ulong an,
      const LIMB *bd, ulong bn,
      LIMB *cd, ulong cn,
      const uint rx)
{
    LIMB *rd;
    ulong rn = an + bn;
    workspace::get_ws(rd,rn);
    null(rd,rn);

    if ( an<bn )  // take care inner loop is on longer array
    {
        swap2(ad, bd);
        swap2(an, bn);
    }

    uint cy = 0;
    for (long j=bn-1; j>=0; --j)  // j = index for b[bn-1..0]
    {
        const uint bdj = bd[j];
        long i, k;
        for (k=an-1, i=k+j+1; k>=0 ; --k,--i)  // k = inner loop index for a[an-1..0]
        {
            uint rdi = (uint)rd[i] + ad[k] * bdj + cy;
            rd[i] = (LIMB)(rdi % rx);
            cy =    (rdi / rx);
        }

        for ( ; i>=0 && cy!=0 ; --i)
        {
            uint rdi = (uint)rd[i] + cy;
            rd[i] = (LIMB)((uint)rdi % rx);
            cy =    rdi / rx;
        }
    }

#ifdef  DT_PARANOIA
    jjassert( cy==0 );
#endif

    int ret;
    if ( rd[0]==0 )   // no overflow ?
    {
        copy0(rd+1, rn-1, cd, cn);
	ret = 0;
    }
    else
    {
        copy0(rd, rn, cd, cn);
        ret = 1;
    }

    workspace::let_ws();

    return ret;
}
//===================== end =========================

