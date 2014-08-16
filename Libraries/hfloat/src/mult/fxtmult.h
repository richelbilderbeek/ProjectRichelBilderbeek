#if !defined HAVE_FXTMULT_H__
#define      HAVE_FXTMULT_H__

#include "fxttypes.h"   // for ulong, LIMB
#include "mod/mtypes.h"


class fxtmult
// class to handle FFT multiplications
{
public:
    static int  square(const LIMB *a, ulong an,
                       LIMB *c, ulong cn,
                       uint rx);

    static int  multiply(const LIMB *a, ulong an,
                         const LIMB *b, ulong bn,
                         LIMB *c, ulong cn,
                         uint rx);

    // convolutions used:
    static void (* mulcnvl1)(double *, double *, ulong);  // mult inside cache
    static void (* mulcnvl2)(double *, double *, ulong); // mult beyond cache size
    static void (* sqrcnvl1)(double *, ulong);  // sqr inside cache
    static void (* sqrcnvl2)(double *, ulong); // sqr beyond cache size
    // ... beyond total ramsize mass storage convolutions are used


    // mult/fxtsquare.cc:
    static int fxt_square(const LIMB *a, ulong an,
                          LIMB *c, ulong cn,
                          uint rx);

    // mult/fxtmultiply.cc:
    static int fxt_multiply(const LIMB *a, ulong an,
                            const LIMB *b, ulong bn,
                            LIMB *c, ulong cn,
                            uint rx);

    // mult/disksquare.cc:
    static int disk_square(const LIMB *a, ulong an,
                           LIMB *c, ulong cn,
                           uint rx,
                           ulong fn, ulong al);

    // mult/diskmultiply.cc:
    static int disk_multiply(const LIMB *a, ulong an,
                             const LIMB *b, ulong bn,
                             LIMB *c, ulong cn,
                             uint rx,
                             ulong fn, ulong al);

    static int  checkmult;  // whether to do the sum of digits test
    static int  verbosity;  // whether to echo which kind of mult is in progress

    static ulong max_noswap_dfxtlen();
    static ulong max_cache_dfxtlen();

    static ulong ndoubles_fxtsqr(ulong an);
    static ulong ndoubles_fxtmul(ulong an, ulong bn);
    static ulong alpha_sqr(ulong an);
    static ulong alpha_mul(ulong an, ulong bn);
    static double swapfile_bytes(ulong an);

    static const char * const filename1;
    static const char * const filename2;

    static double  fxtwork;      // how much work was done in fast transforms
//    static double  diskio;       // disk I/O in bytes
//    static double  diskiotime;
//    static double  ndiskseeks;   // # of seek operations

    static void  print_info(ulong n=0);
    static void  print_statistics(ulong n=0);

    static const char * const classname;
};
// -------------------------


// mult/fxtmult.cc:
void copy_out(const LIMB *a, ulong an, double *f, ulong fn);
void copy_in(const double *f, ulong fn, LIMB *a, ulong an);
ulong my_carry(double *f, ulong n, uint rx);


// mult/auxil.cc:
ulong next_dfxtlen(ulong n);
ulong previous_dfxtlen(ulong n);

ulong sum_of_digits(const double *a, ulong n, double nine, ulong s);
ulong sum_of_digits(const LIMB *a, ulong n, ulong nine, ulong s);

ulong mult_sum_of_digits(const LIMB *a, ulong an,
                         const LIMB *b, ulong bn,
                         ulong nine);

ulong sqr_sum_of_digits(const LIMB *a, ulong an, ulong nine);


// mult/carry.cc:
void carry_thru(double *a, ulong n, uint rx, double &cy);
ulong carry(double *a, ulong n, uint rx);


void carry_thru(umod_t *a, ulong n, uint rx, umod_t &cy);
ulong carry(umod_t *a, ulong n, uint rx);


#endif // !defined HAVE_FXTMULT_H__
