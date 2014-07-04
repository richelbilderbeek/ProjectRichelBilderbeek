
#include "hfdatafu.h"

#include <fxt/aux1/shift.h>  // shift_left()
#include <fxt/sort/usearch.h>  // first_neq_idx()

#include <fxt/jjassert.h>
#include "dtparanoia.h"


int
dt_div_sh(hfdata &a, ulong u, ulong *rem)
// c = a/b, rem = a%b
// Return amount of left shift that occured
{
#ifdef  DT_PARANOIA
    jjassert( a.OK() );
#endif

    jjassert( u ); // "division by zero"

    int ret;
    if ( u <= MAX_LIMB )
    {
	ret = i_div_sh(a.dig(), a.prec(), u, (uint)hfdata::rx, rem);
    }
    else
    {
#if defined HAVE_IDIVSEMI
        ret = i_div_semi(a.dig(), a.prec(), u, (uint)hfdata::rx, rem);
#else
        jjassert( 0 ); // "not implemented: division by int>MAX_LIMB"
#endif // defined HAVE_IDIVSEMI
    }

#ifdef  DT_PARANOIA
    jjassert( a.OK() );
#endif

    return ret;
}
//============== end ====================



int
i_div_sh(LIMB *cd, ulong cn, ulong b, const uint rx, ulong *r)
// Return amount of left shift that occured
{
    jjassert( b<= MAX_LIMB );

    ulong k;
    ulong zz, rem = 0;
    for (k=0; k<cn; ++k)
    {
        zz  = cd[k];
	zz += rx * rem;
        cd[k] = (LIMB)(zz / b);
        rem   = zz % b;

        // is not faster:
        /*
        zz  =  cd[k];
	zz +=  rem * rx;
        cd[k] = (rem=(zz/b));
        rem  = zz - b*rem;
        */
    }

    ulong f = first_neq_idx(cd, cn, (LIMB)0);

    if ( f )   // normalize
    {
        shift_left(cd, cn, f);

	k = f;
	do
	{
	    zz = rx*rem;
	    cd[cn-k] = (LIMB)(zz / b);
	    rem      = zz % b;
	}
	while ( --k );
    }

    if ( r )  *r = rem;

    return  (int)f;
}
//================== end ========================



#if defined HAVE_IDIVSEMI

#undef  UINTLL
#define UINTLL unsigned long long

//#include <fxt/fxtio.h>

int
i_div_semi(LIMB *cd, ulong cn, ulong b, const uint rx, ulong *r) // =0
// Return amount of left shift that occured
{
//    {
//        ulong f = first_neq_idx(cd, cn, (LIMB)0);
//        cout << "i_div_semi(): first_neq_idx f = " << f << endl;
//        for (ulong k=0; k<cn; ++k)  cout << setw(4) << k << ": " << cd[k] << endl;
//        cout << "i_div_semi(): start... " << endl;
//    }

    UINTLL zz, rem = 0;
    for (ulong k=0; k<cn; ++k)
    {
#if 0
        zz  =  (UINTLL)cd[k];
	zz +=  rx * rem;
        cd[k] = (LIMB)(zz/b);
        rem  = zz % b;
//        cout << setw(4) << k << ":  cd[k]=" << cd[k] << "  rem=" << rem << "  zz=" << zz << endl;
#else
        zz  =  (UINTLL)cd[k];
	zz +=  rem * rx;
        cd[k] = (LIMB)(rem=(zz/b));
        rem  = zz - b * rem;
//        cout << setw(4) << k << ":  cd[k]=" << cd[k] << "  rem=" << rem << "  zz=" << zz << endl;
#endif
    }


    ulong f = first_neq_idx(cd, cn, (LIMB)0);

    if ( f )   // normalize
    {
//        for (ulong k=0; k<cn; ++k)  cout << setw(4) << k << ": " << cd[k] << endl;
//        cout << "i_div_semi(): b = " << b << endl;
//        cout << "i_div_semi(): cn = " << cn << endl;
//        cout << "i_div_semi(): left-shift by f = " << f << endl;
//        jjassert( f < cn );
        shift_left(cd, cn, f);

        ulong k = f;
	do
	{
	    zz = rx * rem;
	    cd[cn-k] = (LIMB)(zz/b);
	    rem = zz % b;
	}
	while ( --k );
    }

    if ( r )  *r = (ulong)rem;

    return  (int)f;
}
//================== end ========================

#endif // defined HAVE_IDIVSEMI

