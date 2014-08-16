

#include "hfdata.h"

#include <fxt/aux0/sign.h>  // sign()
#include <fxt/sort/minmaxmed23.h>  // min2(), max2()


static ulong
cmp999(const LIMB *ad, const LIMB *bd, ulong n)
//
{
//    jjassert( ad[0]-bd[0] == 1 );
    LIMB nine = (LIMB)(hfdata::radix() - 1);
    ulong k = 1;
    for (  ; k<n; ++k)
    {
        if ( ad[k]!=0 )  break;
        if ( bd[k]!=nine )  break;
    }

    return  k - 1;
}
//--------------------------------


int
dt_cmp(const hfdata &a, const hfdata &b, ulong *idx/*=0*/)
//
// return:   zero if all LIMBs agree
//           else sign(a_digit-b_digit) of the first disagreeing LIMBs
//
// if one digit field is longer and has only zeros in its excess length
// then the length of the longer field is taken as index
//
// idx (if !=0) is set to the index of first differing LIMBs
//    cases like 1.00000 compared to 0.9999999 are handled correctly
//
{
    LIMB *ad = a.dig();
    LIMB *bd = b.dig();
    ulong ap = a.prec();
    ulong bp = b.prec();

    // return position of first diff digits:
    ulong pmin = min2(ap, bp);
    ulong k;
    for (k=0; k<pmin; ++k)
    {
        if ( ad[k]!=bd[k] )
        {
            ulong z = 0;
            long d = (long)ad[k]-(long)bd[k];

            if ( d==1 )  // check cases like 1.84000 vs. 1.8399999
            {
                z = cmp999(ad+k, bd+k, pmin-k);
            }
            else if ( d==-1 )  // 1.8399999 vs. 1.84000
            {
                z = cmp999(bd+k, ad+k, pmin-k);
            }

            if ( idx )  *idx = k + z;
            return  (int)sign(d);
        }
    }

    // longer number is bigger unless all excess digits are zero:
    if( ap>bp )
    {
        ulong pmax = max2(ap, bp);
        for ( ; k<pmax; ++k)
        {
            if ( ad[k] )  // digit != 0 in excess length ?
            {
                if ( idx )  *idx = k;
                return  +1;
            }
        }
    }
    else if( ap<bp )
    {
        ulong pmax = max2(ap, bp);
        for ( ; k<pmax; ++k)
        {
            if ( bd[k] )  // digit != 0 in excess length ?
            {
                if ( idx )  *idx = k;
                return  -1;
            }
        }
    }

    if ( idx )  *idx = k;
    return  0;   // perfect agreement
}
//=================== end ====================


