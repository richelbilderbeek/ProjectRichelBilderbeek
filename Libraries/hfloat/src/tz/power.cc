
#include <fxt/jjassert.h>

#include "hfloat.h"


void
pow(const hfloat &z, const hfloat &x, hfloat &t)
{
    if ( z.is_zero() )
    {
        t = 0;
        return;
    }

    jjassert( z.positive() ); // " negative z in z^x ! "

    hfloat tmp(t.prec());

    // z^x == exp(x*log(z)):
    log(z,tmp);
    tmp *= x;
    exp(tmp, t);
}
//=================== end =====================
