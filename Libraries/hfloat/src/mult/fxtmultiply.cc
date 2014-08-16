
#include "fxttypes.h"
#include "fxtmult.h"
#include "workspace.h"
#include "bits/bit2pow.h" // ld()

#include "jjassert.h"
#include "fxtio.h"


int // static
fxtmult::fxt_multiply(const LIMB *a, ulong an,
                      const LIMB *b, ulong bn,
                      LIMB *c, ulong cn,
                      uint rx)
//
// Return whether right shift occured.
//
{
    const ulong nine = rx-1;
    ulong qsm=0, qsp=0;
    if ( checkmult )  qsm = mult_sum_of_digits(a, an, b, bn, nine);

    const ulong n2 = ndoubles_fxtmul(an, bn);
    double *f;
    workspace::get_noswap_ws(f, n2);
    const ulong n = n2 / 2;
    double *g = f + n; // + workspace::extra_doubles_;
    copy_out(a, an, f, n);
    copy_out(b, bn, g, n);

    const ulong ldn = ld(n);
    fxtwork +=  3.0 * (double)(n * ldn);
    if ( max_cache_dfxtlen() >= n ) // fits in cache
    {
        if  ( verbosity > 0 )  { cout << ".";  cout.flush(); }
        mulcnvl1(f, g, ldn);
    }
    else
    {
        if  ( verbosity > 0 )  { cout << ":";  cout.flush(); }
        mulcnvl2(f, g, ldn);
    }

    //    cout << __FUNCTION__ <<":  an=" << an << "  bn=" << bn
    //         << "  cn=" << cn << "  n=" << n << endl;

    ulong cy = my_carry(g, n, rx);
    if( 0==cy )
    {
        copy_in(g, n, c, cn);
    }
    else
    {
        c[0] = (LIMB)cy;
        copy_in(g, n, c+1, cn-1);  // c[cn-1] is lost here
    }

    //    if  ( verbosity > 0 )  { cout << "]";  cout.flush(); }

    if ( checkmult )
    {
        qsp = sum_of_digits(g, n, (double)nine, cy );
        jjassert( qsm==qsp ); // "sum_of_digits test failed"
    }

    workspace::let_ws();

    return (cy!=0);
}
// -------------------------
