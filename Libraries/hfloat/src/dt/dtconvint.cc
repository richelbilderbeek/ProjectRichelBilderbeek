
#include "hfdatafu.h"

#include <fxt/aux1/shift.h>  // shift_right()
#include <fxt/aux1/copy.h>  // null()

#include <fxt/jjassert.h>
#include "dtparanoia.h"



ulong
dt_int_to_mantissa(ulong i, hfdata &a)
// Return how many LIMBs were set
{
    LIMB *ad = a.dig();
    null(ad, a.prec());

    ulong k = 0;
    for (  ; i!=0; ++k)
    {
        jjassert( k < a.prec() ); // "overflow while converting from integer"

//        if ( k!=0 )  shift_right(ad, k+1, 1);
        if ( k!=0 )  shift_right1(ad, k+1);

        const ulong  rx = hfdata::rx;
        ad[0] = (LIMB)(i % rx);
        i     = i / rx;
    }

#ifdef  DT_PARANOIA
    jjassert( a.OK() );
#endif

   return k;
}
//=============== end =======================
