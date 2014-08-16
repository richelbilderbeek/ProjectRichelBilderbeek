
#include "diskconvolution.h"  // disk_weighted_complex_auto_convolution()
#include "diskaux.h"
#include "fxtmult.h"
#include "fxttypes.h"

#include "workspace.h"
#include "aux1/copy.h"
#include "aux1/shift.h"  // shift_right()
#include "jjassert.h"

#include "bits/bit2pow.h" // ld()

#include "fxtio.h"

int // static
fxtmult::disk_square(const LIMB *a, ulong an,
                     LIMB *c, ulong cn,
                     uint rx,
                     ulong fn, ulong al)
{
    if  ( verbosity>0 )  { cout << "[k:" << al;  cout.flush(); }

    const ulong nine = rx-1;
    ulong qsm = 0;
    if ( checkmult )  qsm = sqr_sum_of_digits(a, an, nine);

    int fd1, fd2;
    open_or_die(filename1, &fd1);
    open_or_die(filename2, &fd2);

    double *f;
    workspace::get_noswap_ws(f, fn);

    limb2disk(a, an, f, fn, al/2, fd1);

    ulong dn = fn * al;  // total # of doubles
    fxtwork += (double)(dn * ld(dn));

    // right-angle convolution:
    double w = +0.25;  // weight
    double nx = 0.0;
    int zq = 1;  // 1 =--> imag part of input is zero
    if ( zq==0 )  zeros2disk(f, fn, al/2, fd2);  // note: wasteful
    disk_weighted_complex_auto_convolution(fd1, fd2, f, fn, al, w, nx, zq, 0);


    ulong qsp = 0;
    ulong cy = 0;
    disk_carry_thru_2limb(f, fn, al/2, fd2, rx, cy, c, cn, al*fn, qsp);
    disk_carry_thru_2limb(f, fn, al/2, fd1, rx, cy, c, cn, 0,     qsp);
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
        if ( qsm!=qsp )  cout << "\n  **S**  qsm=" << qsm << " =!=  qsp=" << qsp << endl;
//        else             cout << "\n  ++S++  qsm=" << qsm << " ===  qsp=" << qsp << endl;
        jjassert( qsm==qsp ); // "sumofdigits test failed"
    }


    workspace::let_ws();

    return (cy!=0);
}
// -------------------------

