
#include "fxttypes.h"
#include "fxtmult.h"

#include "bits/bit2pow.h" // ld()
#include "workspace.h"

#include "jjassert.h"
#include "fxtio.h"


int // static
fxtmult::fxt_square(const LIMB *a, ulong an,
                    LIMB *c, ulong cn,
                    uint rx)
//
// Return whether right shift occured.
//
{
    const ulong nine = rx-1;
    ulong qsm=0, qsp=0;
    if ( checkmult )  qsm = sqr_sum_of_digits(a, an, nine);

    const ulong n = ndoubles_fxtsqr(an);
    double *f;
    workspace::get_noswap_ws(f, n);
    copy_out(a, an, f, n);

    const ulong ldn = ld(n);
    fxtwork +=  2.0 * (double)(n * ldn);
    if ( max_cache_dfxtlen() >= n ) // fits in cache
    {
        if  ( verbosity>0 )  { cout << ".";  cout.flush(); }
        sqrcnvl1(f, ldn);
    }
    else
    {
        if  ( verbosity>0 )  { cout << ":";  cout.flush(); }
        sqrcnvl2(f, ldn);
    }

//    cout << __FUNCTION__ <<":  an=" << an << "  cn=" << cn << "  n=" << n << endl;

    ulong cy = my_carry(f, n, rx);

    if( 0==cy )
    {
        copy_in(f, n, c, cn);
    }
    else
    {
        c[0] = (LIMB)cy;
        copy_in(f, n, c+1, cn-1);  // c[cn-1] is lost here
    }

//    if  ( verbosity>0 )  { cout << "]";  cout.flush(); }

    if ( checkmult )
    {
        qsp = sum_of_digits(f, n, (double)nine, cy);
        jjassert( qsm==qsp ); // "sum_of_digits test failed"
    }

    workspace::let_ws();

    return (cy!=0);
}
// -------------------------
