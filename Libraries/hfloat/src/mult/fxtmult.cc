
#include "convolution/realconvolution.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "fxtmult.h"
#include "workspace.h"

#include "mod/mod.h"
#include "sort/minmaxmed23.h"
#include "aux1/arith1.h"
#include "aux1/copy.h"

#include "fxtio.h"

#include <cmath>  // log()


//#define  USE_NTT  // define to use NTTs (4 times slower on my machine)

// saving characters:
#define  CACHE_SQR  void (* fxtmult::sqrcnvl1)(double *, ulong)
#define  MEM_SQR    void (* fxtmult::sqrcnvl2)(double *, ulong)
#define  CACHE_MUL  void (* fxtmult::mulcnvl1)(double *, double *, ulong)
#define  MEM_MUL    void (* fxtmult::mulcnvl2)(double *, double *, ulong)


#ifdef USE_NTT
#include "ntt/ntt.h"
#warning '*** using NTT-convolution, this is SLOW *** '
CACHE_SQR = ntt_auto_convolution;
CACHE_MUL = ntt_convolution;
MEM_SQR   = ntt_auto_convolution;
MEM_MUL   = ntt_convolution;

#include "mod/mod.h"
class NTTinit // sole purpose is to initialize the class mod
{
public:
    NTTinit() { mod::init(0x3fffc00000000001ULL); } // modulus
    ~NTTinit() {;}
};
static::NTTinit initNTThere;

#else  // USE_NTT

// ---- in-cache versions: ----
CACHE_SQR = fht_auto_convolution0;  // default
CACHE_MUL = fht_convolution0;  // default

//CACHE_SQR = loc_fht_auto_convolution;
//CACHE_MUL = loc_fht_convolution;
// ----------------------------

// ---- out-of-cache versions: ----
//MEM_SQR  = matrix_fft_auto_convolution0;
//MEM_MUL  = matrix_fft_convolution0;
//./pi 22 161 100  17.88s user 0.20s system 99% cpu 18.109 total
//./pi 24 161 10000  84.67s user 0.89s system 99% cpu 1:25.57 total

MEM_SQR = loc_fht_auto_convolution;  // default
MEM_MUL = loc_fht_convolution;  // default
//./pi 22 161 100  11.83s user 0.18s system 99% cpu 12.043 total
//./pi 24 161 10000  54.87s user 0.74s system 99% cpu 55.829 total

//MEM_SQR = split_radix_fft_auto_convolution0;  // slow!
//MEM_MUL = split_radix_fft_convolution0;  // slow!
//./pi 22 161 100  46.09s user 0.38s system 99% cpu 46.481 total
// ----------------------------

#endif  // USE_NTT



#define  USE_DEV_FILES  0  // 0 (regular files) or 1 (devices, !DANGER!)

#if  ( USE_DEV_FILES==0 )
const char * const fxtmult::filename1 = "/tmp/massstorage1.bin";
const char * const fxtmult::filename2 = "/tmp/massstorage2.bin";
#else  // USE_DEV_FILES
#warning '*****************************************'
#warning '! using devices for mass storage FFTs !  '
#warning '! you absolutely MUST know what this     '
#warning '! technically means or +++ STOP NOW +++  '
#warning '*****************************************'
#error   ' =-->  EDIT THIS FILE TO PROCEED '
const char * const fxtmult::filename1 = "/dev/hda2";
const char * const fxtmult::filename2 = "/dev/hda3";
#endif  // USE_DEV_FILES


int     fxtmult::checkmult = 1;
int     fxtmult::verbosity = 0;

double  fxtmult::fxtwork = 0.0;
//double  fxtmult::diskio = 0.0;
//double  fxtmult::diskiotime = 0.0;
//double  fxtmult::ndiskseeks = 0.0;

const char * const fxtmult::classname = "fxtmult";


void
copy_out(const LIMB *a, ulong an, double *f, ulong fn)
{
#ifndef  USE_NTT
    ::copy0(a, an, f, fn);
#else
    jjassert( sizeof(mod) == sizeof(double) );
    umod_t *m = (umod_t *)f;  // jjcast
    ::copy0(a, an, m, fn);
#endif
}
// -------------------------

void
copy_in(const double *f, ulong fn, LIMB *a, ulong an)
{
#ifndef  USE_NTT
    ::copy0(f, fn, a, an);
#else
    const umod_t *m = (const umod_t *)f;  // jjcast
    ::copy0(m, fn, a, an);
#endif
}
// -------------------------

ulong
my_carry(double *a, ulong n, uint rx)
{
#ifndef  USE_NTT
    return carry(a, n, rx);
#else
    umod_t *m = (umod_t *)a;  // jjcast
    return carry(m, n, rx);
#endif
}
// -------------------------

int // static
fxtmult::multiply(const LIMB *a, ulong an,
                  const LIMB *b, ulong bn,
                  LIMB *c, ulong cn,
                  uint rx)
// multiplication:  c[] := a[] times b[]
{
#ifdef   USE_NTT
    checkmult = 0;
#warning  'fxtmult::checkmult disabled for NTT-convolution'
#warning  '  ... (we need sum_of_digits() for type mod)'
#endif

    ulong al = alpha_mul(an, bn);

    if ( al<=1 )  // convolution in memory
    {
        return fxt_multiply(a, an, b, bn, c, cn, rx);
    }
    else  // mass storage convolution
    {
        ulong fn = max_noswap_dfxtlen();
        return  disk_multiply(a, an, b, bn, c, cn, rx, fn, al);
    }
}
// -------------------------


int // static
fxtmult::square(const LIMB *a, ulong an,
                LIMB *c, ulong cn,
                uint rx)
// squaring:  c[] := a[] times a[]
{
#ifdef   USE_NTT
    checkmult = 0;
#warning  'fxtmult::checkmult disabled for NTT-convolution'
#warning  '  ... (we need sum_of_digits() for type mod)'
#endif

    ulong al = alpha_sqr(an);

    if ( al<=1 )  // convolution in memory
    {
        return fxt_square(a, an, c, cn, rx);
    }
    else  // mass storage convolution
    {
        ulong fn = max_noswap_dfxtlen();
        return  disk_square(a, an, c, cn, rx, fn, al);
    }
}
// -------------------------


ulong  // static
fxtmult::max_noswap_dfxtlen()
{
    return  previous_dfxtlen( workspace::noswap_doubles() );
}
// -------------------------

ulong // static
fxtmult::max_cache_dfxtlen()
{
    return  previous_dfxtlen( workspace::cache_doubles() );
}
// -------------------------

ulong // static
fxtmult::ndoubles_fxtsqr(ulong an)
{
    return next_dfxtlen(2*an);
}
// -------------------------

ulong // static
fxtmult::ndoubles_fxtmul(ulong an, ulong bn)
{
    return 2*next_dfxtlen( 2 * max2(an, bn) );
}
// -------------------------

ulong // static
fxtmult::alpha_mul(ulong an, ulong bn)
{
    ulong n = ndoubles_fxtmul(an,bn);
    ulong fn = max_noswap_dfxtlen();
    ulong al = n/fn;
    if ( al*fn != n )  ++al;
    return al;
}
// -------------------------

ulong // static
fxtmult::alpha_sqr(ulong an)
{
    ulong n = ndoubles_fxtsqr(an);
    ulong fn = max_noswap_dfxtlen();
    ulong al = n/fn;
    if ( al*fn != n )  ++al;
    return al;
}
// -------------------------

double // static
fxtmult::swapfile_bytes(ulong an)
{
    ulong al = alpha_mul(an,an);
    ulong fn = max_noswap_dfxtlen();
    if ( al>1 )  return  0.5 * (double)(al * fn * sizeof(double));
    else         return  0.0;
}
// -------------------------


void // static
fxtmult::print_info(ulong n/*=0*/)
{
    cout << " fxtmult: FFT multiplications ";
    if ( checkmult )  cout << "ARE ";
    else              cout << "are NOT ";
    cout << "checked via sum of digit test " << endl;

    if ( n!=0 )
    {
        double dn = swapfile_bytes(n);
        if ( dn!=0 )
        {
            cout << " fxtmult: swapfile1 is \"" << filename1 << "\"" << endl;
            cout << " fxtmult: swapfile2 is \"" << filename2 << "\"" << endl;
            cout << " fxtmult: max swapfile size will be (2x) "
                 << dn/(1024*1024) << " MB" << endl;
        }
        else
        {
            cout << " fxtmult: max workspace size for FFT mult will be "
                 << ndoubles_fxtmul(n,n)*sizeof(double) << " bytes " << endl;
        }
    }
}
// -------------------------


void // static
fxtmult::print_statistics(ulong n/*=0*/)
{
    const double fftMwork = 1024.0 * 1024.0 * 20;
    cout << " fxtmult: work was=" << fxtwork / fftMwork
         << " times length 2^20 real FFTs" << endl;

    if ( n )
    {
        const double dn = (double)n;
        const double fftnwork = 2.0*dn*log(2.0*dn)*(1.0/log(2.0));
        cout << " fxtmult: == " << fxtwork/fftnwork << " full prec real FFTs" << endl;
        cout << " fxtmult: == " << fxtwork/(3.0*fftnwork) << " full prec mults" << endl;
    }

//    if ( 0.0 != diskio )
//    {
//        cout << " fxtmult: disk I/O was " << diskio/(1024.0 * 1024.0) << " MB" << endl;
//        cout << " fxtmult: disk I/O time was " << diskiotime << endl;
//        cout << " fxtmult: # of disk seeks was " << ndiskseeks << endl;
//    }
}
// -------------------------
