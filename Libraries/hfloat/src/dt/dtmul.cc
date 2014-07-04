
#include "hfdatafu.h"

#include "fxtmult.h"

#include <fxt/jjassert.h>
#include "dtparanoia.h"

#ifdef  DT_PARANOIA
#warning "++++++++++++++++++++++++++++++++++++++++"
#warning "DT_PARANOIA enabled, performance is gone"
#warning "++++++++++++++++++++++++++++++++++++++++"
#endif

#define  AD  a.dig()
#define  BD  b.dig()
#define  CD  c.dig()
#define  AP  a.prec()
#define  BP  b.prec()
#define  CP  c.prec()
#define  RX  ((uint)hfdata::rx)


#define  FXT_MUL_THRES  32  // default = 32

int
dt_mul(const hfdata &a, const hfdata &b, hfdata &c)
// Return how many right shifts happened (0 or 1)
{
#ifdef  DT_PARANOIA
    jjassert( a.OK() );
    jjassert( b.OK() );
#endif

    int i;
    if ( (AP<=FXT_MUL_THRES) || (BP<=FXT_MUL_THRES) )  // jjnote: improve condition
    {
        i = i_mul(AD, AP, BD, BP, CD, CP, RX);
    }
    else
    {
        i = fxtmult::multiply(AD, AP, BD, BP, CD, CP, RX);
    }

#ifdef  DT_PARANOIA
    jjassert( c.OK() );
#endif

    return i;
}
//======================== end =======================

//#include <fxt/fxtio.h>

int
dt_mul(const hfdata &a, ulong ap, const hfdata &b, ulong bp, hfdata &c, ulong cp)
// Return how many right shifts happened (0 or 1)
{
#ifdef  DT_PARANOIA
    jjassert( a.OK() );
    jjassert( b.OK() );
#endif

    if ( ap>a.size() )  ap = a.size();
    if ( bp>b.size() )  bp = b.size();
    if ( cp>c.size() )  cp = c.size();

    int i;
    if ( (AP<=FXT_MUL_THRES) || (BP<=FXT_MUL_THRES) )  // jjnote: improve condition
    {
        i = i_mul(AD, ap, BD, bp, CD, cp, RX);
    }
    else
    {
        i = fxtmult::multiply(AD, ap, BD, bp, CD, cp, RX);
    }

//    cout << "DT_MUL():"
//         <<  "  ap=" << ap
//         <<  "  bp=" << bp
//         <<  "  cp=" << cp
//         <<  "  i=" << i
//         << endl;

#ifdef  DT_PARANOIA
    jjassert( c.OK() );
#endif

    return i;
}
//======================== end =======================


int
dt_sqr(const hfdata &a, hfdata &c)
// Return how many right shifts happened (0 or 1)
{
#ifdef  DT_PARANOIA
    jjassert( a.OK() );
#endif

    int i;
    if ( AP<=FXT_MUL_THRES )
    {
        i = i_mul(AD, AP, AD, AP, CD, CP, RX);
    }
    else
    {
        i = fxtmult::square(AD, AP, CD, CP, RX);
    }

#ifdef  DT_PARANOIA
    jjassert( c.OK() );
#endif

    return i;
}
//============================= end =======================



int
dt_sqr(const hfdata &a, ulong ap, hfdata &c, ulong cp)
// Return how many right shifts happened (0 or 1)
{
#ifdef  DT_PARANOIA
    jjassert( a.OK() );
#endif

    if ( ap>a.size() )  ap = a.size();
    if ( cp>c.size() )  cp = c.size();

    int i;
    if ( AP<=FXT_MUL_THRES )
    {
        i = i_mul(AD, ap, AD, ap, CD, cp, RX);
    }
    else
    {
        i = fxtmult::square(AD, ap, CD, cp, RX);
    }

#ifdef  DT_PARANOIA
    jjassert( c.OK() );
#endif

    return i;
}
//============================= end =======================

