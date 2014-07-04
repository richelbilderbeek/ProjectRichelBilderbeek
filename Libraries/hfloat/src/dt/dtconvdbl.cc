
#include "hfdata.h"
#include <fxt/aux1/copy.h>  // null(), fill()

#include <fxt/jjassert.h>
#include "dtparanoia.h"


#define SMALL_DBL (1.0e-23)  // jjnote: magic: sensible value
#define LARGE_DBL (1.0e+23)  // jjnote: magic: sensible value



ulong
dt_mantissa_to_double(const hfdata &a, double &d)
// resulting double is <= 1.0 (in theory strictly < 1)
// returns how many LIMBs were read -1
{
#ifdef  DT_PARANOIA
    jjassert( a.OK() );
#endif

    LIMB *ad = a.dig();
    const double drx1 = 1.0/(double)hfdata::rx;

    d = 0.0;
    double f = 1.0;
    ulong k = 0;
    while( k<a.prec() )  // add up the LIMBs
    {
        f *= drx1;
        if ( f<SMALL_DBL )  break;
        d +=  ad[k]*f;
        ++k;
    }

//    jjassert( d<=1.0 );  // can by larger due to excess precision

    return k;
}
//=============== end ==================


//#include <fxt/fxtio.h>

ulong
dt_double_to_mantissa(double d, hfdata &a)
// double d must be <= 1.0
// returns how many LIMBs were made -1
{
    LIMB *ad = a.dig();
    const ulong ap = a.prec();

    ulong ret;
    if ( d==1.0 )
    {
        fill(ad,ap, (LIMB)(hfdata::rx-1));  // jjnote: 1 --> 0.99999
        ret = ap;
    }
    else
    {
        jjassert( d<1.0 );

        const double drx = (double)hfdata::rx;
        const double drx1 = 1.0/(double)hfdata::rx;

        null(ad,ap);

        double  f = 1.0;
        ulong  k;
//        cerr.precision(23);
//        cerr << "f= " << f << endl;
//        cerr << "d= " << d << endl;
//        cerr << endl;
        for (k=0; k<ap; ++k)
        {
            f *= drx1;
            if ( f<SMALL_DBL )  break;
            d *= drx;

            LIMB z = (LIMB)d;

            if ( z >= hfdata::rx )  --z;
            ad[k] = z;

//            cerr.precision(23);
//            cerr << "f= " << f << endl;
//            cerr << "d= " << d << endl;
//            cerr << "ad[" << k << "]= " << ad[k] << endl;
//            cerr << endl;

            d -= ad[k];
        }

        ret = k;
    }

#ifdef  DT_PARANOIA
    jjassert( a.OK() );
#endif

    return ret;
}
//===================== end =======================
