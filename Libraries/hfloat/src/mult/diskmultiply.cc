
#include "bits/bit2pow.h" // ld()
#include "fxttypes.h"
#include "aux1/copy.h"
#include "aux1/shift.h"  // shift_right()
#include "jjassert.h"

#include "diskaux.h"
#include "fxtmult.h"
#include "workspace.h"

#include "fxtio.h"

#include "diskconvolution.h"  // disk_weighted_complex_auto_convolution()


int // static
fxtmult::disk_multiply(const LIMB *a, ulong an,
                       const LIMB *b, ulong bn,
                       LIMB *c, ulong cn,
                       uint rx,
                       ulong fn, ulong al)
{
    if  ( verbosity>0 )  { cout << "[K:" << al;  cout.flush(); }

    double *f;
    workspace::get_noswap_ws(f, fn);

    const ulong nine = rx-1;
    ulong qsm = 0;
    if ( checkmult )  qsm = mult_sum_of_digits(a, an, b, bn, nine);

    int fd1, fd2;
    open_or_die(filename1, &fd1);
    open_or_die(filename2, &fd2);

    limb2disk(a, an, f, fn, al/2, fd1);
    limb2disk(b, bn, f, fn, al/2, fd2);

    ulong dn = fn * al;  // total # of doubles
    fxtwork += (double)(dn * ld(dn));

    // simple (complex) auto-convolution:
    double w = 0.0;  // weight
    double nx = 0.5;
    int zq = 1;  // 1 =--> discard real part of result
    disk_weighted_complex_auto_convolution(fd1, fd2, f, fn, al, w, nx, 0, zq);


    ulong cy = 0;
    ulong qsp = 0;
    disk_carry_thru_2limb(f, fn, al/2, fd2, rx, cy, c, cn, 0,     qsp);
    qsp += cy;
    if ( qsp>=nine )  qsp -= nine;

    close_or_die(fd1);
    close_or_die(fd2);

    if ( cy )
    {
//        shift_right(c, cn, 1);  // c[cn-1] is lost here
        shift_right1(c, cn);  // c[cn-1] is lost here

        c[0] = (LIMB)cy;
    }

    if  ( verbosity>0 )  { cout << "]";  cout.flush(); }

    if ( checkmult )
    {
//        cout << "\n" << __FUNCTION__ << ": ";
        if ( qsm!=qsp )  cout << "\n  **M**  qsm=" << qsm << " =!=  qsp=" << qsp << endl;
//        else             cout << "\n  ++M++  qsm=" << qsm << " ===  qsp=" << qsp << endl;
        jjassert( qsm==qsp ); // "sum_of_digits test failed"
    }

    workspace::let_ws();

    return (cy!=0);
}
// -------------------------

