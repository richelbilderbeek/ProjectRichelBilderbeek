
#include "fxttypes.h"
#include "fxtmult.h"

#include "jjassert.h"  // jjnote: asserts used in code: checksum errors

#include <cmath> // floor(), modf()


// define for a few asserts outside loops that trap many errors:
#define  CARRYCHECK  // default is #defined

//#define PARANOIA  // define to enable for this file
#ifdef PARANOIA
#warning  'PARANOIA tests enabled in carry.cc'
//
#undef CARRYCHECK
#define CARRYCHECK
#endif // PARANOIA


static inline void
divmod(double &a, double &cy, double drx, double d1rx)
// With drx==(double)R (radix),  d1rx==1/drx,  cy==carry (in)
//   set cy=(a-a%R)/R (carry out)  and  a=a%R
{
    //  a += cy;  cy = a / rx;  a %= rx;
    a = floor( drx * modf( (a+cy+0.5)*(d1rx), &cy) );
}
// -------------------------

void
carry_thru(double *a, ulong n, uint rx, double &cy)
// Carry through region a[n-1,...,0]
{
    const double drx  = (double)rx;
    const double d1rx = 1.0/drx;

    while ( n-- )
    {
//        jjassert( fabs(a[n]-floor(0.5+a[n])) < 0.25 );
        divmod(a[n], cy, drx, d1rx);
//        jjassert( a[n]>=0 );
//        jjassert( cy>=0 );
    }
}
// -------------------------


ulong
carry(double *a, ulong n, uint rx)
// Carry operation for fft-multiplication.
// Return zero if no overflow happened
// else the new most significant digit.
{
#ifdef  CARRYCHECK
    double ns = (double)rx-1;  ns *= ns;
    jjassert( ns >= floor(0.5+a[0]) );
    if ( n>=2 )  jjassert( ns >= floor(0.5+a[n-2]) );
    if ( n>=1 )  jjassert( 0  == floor(0.5+a[n-1]) );
#endif // CARRYCHECK

    double cy = 0.0;
    carry_thru(a, n, rx, cy);

    if ( cy==0 )  return 0;
    else
    {
        cy = floor(0.5+cy);
#ifdef  CARRYCHECK
        jjassert( cy >= 0 );
        jjassert( cy < rx );
#endif  // CARRYCHECK
        return (ulong)cy;
    }
}
// -------------------------





#include "mod/mtypes.h"

static inline void
divmod(umod_t &a, umod_t &cy, umod_t rx)
{
    a += cy;
    cy = a / rx;
    a %= rx;
}
// -------------------------

void
carry_thru(umod_t *a, ulong n, uint rx, umod_t &cy)
// Carry through region a[n-1,...,0]
{
    const umod_t drx  = (umod_t)rx;
    while ( n-- )
    {
        divmod(a[n], cy, drx);
    }
}
// -------------------------


ulong
carry(umod_t *a, ulong n, uint rx)
// Carry operation for fft-multiplication.
// Return zero if no overflow happened
// else the new most significant digit.
{
#ifdef  CARRYCHECK
    umod_t ns = (umod_t)rx-1;  ns *= ns;
    jjassert( ns >= a[0] );
    jjassert( ns >= a[n-2] );
    jjassert( 0  == a[n-1] );
#endif // CARRYCHECK

    umod_t cy = 0;
    carry_thru(a, n, rx, cy);

    if ( cy==0 )  return 0;
    else
    {
#ifdef  CARRYCHECK
        jjassert( cy < rx );
#endif  // CARRYCHECK
        return (ulong)cy;
    }
}
// -------------------------
