
#include "hfdata.h"
#include "hfverbosity.h"

#include <fxt/sort/minmaxmed23.h>  // min2(), max2()
#include <fxt/bits/bit2pow.h>  // ld()
#include <fxt/fxtio.h>
#include <fxt/jjassert.h>
#include <fxt/aux1/copy.h>  // copy0()


#include <cmath>
#include <cstdlib>  // RAND_MAX, rand()
#include <cstring>  // strcpy()


ulong   hfdata::nbytes = 0;
ulong   hfdata::nbytesmax = 0;
long    hfdata::ndata = 0;

// meaningless values to make sure initialisation works:
ulong  hfdata::rx = 0;       // 10000;
ulong  hfdata::ldrx = 0;     // 12
ulong  hfdata::rxbits = 0;   // 13
double hfdata::lg10rx = -1.0;   // 4
bool   hfdata::rx2pw = false;   // false
//ulong  hfdata::rxdig = 0;     // 4
const char*  hfdata::rxfmt = "";    // "%04d";
ulong  hfdata::rxbase = 0;    // 10
ulong  hfdata::rxbspw = 0;    // 4
void (* hfdata::mulcnvl)(double *, double *, ulong) = NULL;
void (* hfdata::sqrcnvl)(double *, ulong) = NULL;


hfdata::hfdata(ulong n)
    : limbs_(0),
      size_(0),
      prec_(0)
{
    if ( hfverbosity::printdtcd )  cout << "\n   hfdata(size_=" << n << ") ";

    size(n);

    if ( hfverbosity::printdtcd )  cout << "  @ " << (void *)limbs_ << endl;

    ndata++;
    jjassert( ndata>0 );
}
//--------------


hfdata::~hfdata()
{
    if ( hfverbosity::printdtcd )  cout << "\n   ~hfdata() " << endl;

    delete [] limbs_;
    ndata--;
    jjassert( ndata>=0 );
}
//--------------


void
hfdata::size(ulong n)
{
    LIMB *oldd = limbs_;
    LIMB *newd = 0;
    ulong osz = size_;

    if ( n!=0 )
    {
        newd = new LIMB[n];
        nbytes += (n * sizeof(LIMB));

        if ( oldd )  // copy digits
        {
            ::copy0(oldd, osz, newd, n);
        }
        else  // initialize with zeros
        {
            for (ulong j=0; j<n; ++j)  newd[j] = 0;
        }
    }

    if ( oldd )
    {
        delete [] oldd;
        nbytes -= (osz * sizeof(LIMB));

        if ( hfverbosity::printresize )
        {
            cout << "  hfdata::" << __FUNCTION__ << "(): "
                 << (void *)oldd << " [" << osz << "]  --> "
                 << (void *)newd << " [" << n << "]" << endl;
        }
    }


    limbs_ = newd;
    size_ = n;
    prec_ = n;

    if ( nbytes>nbytesmax )  nbytesmax = nbytes;
}
//--------------


void
hfdata::prec(ulong p)
{
    if ( p<=size_ )  prec_ = p;
    else             size(p);
}
//--------------


void
hfdata::copy(const hfdata &h)
{
    if ( hfverbosity::printcopy )
    {
        cout << "\n   hfdata::copy(const hfdata &) " << endl;
    }

    if ( this==&h )  return; // nothing to do

    if ( hfverbosity::printcopy )
    {
        cout << "\n   hfdata::copy(const hfdata &) "
             << "calling copy()" << endl;
    }

    ::copy0(h.dig(), h.prec(), limbs_, prec_);
}
//--------------


static void
i_rand(LIMB *a, ulong n, int nine)
{
//    srand(time(0));

    int rn = (RAND_MAX/nine);

    while ( n-- )  a[n] = (LIMB)((int)rand()/rn);
}
//--------------
// used for:

void
hfdata::rand(ulong n1, ulong n2)
{
    ulong mi = min2(n1, n2);
    mi = min2(size_, mi);

    ulong ma = max2(n1, n2);
    ma = min2(size_, ma);

    i_rand(limbs_+mi, ma-mi, (int)radix()-1);
}
//--------------


void
hfdata::dump(const char *bla/*=0*/, ulong n/*=0*/) const
{
    if ( n==0 )  n = prec_;
    if ( n>size_ )  n = size_;

    if ( bla )  cout << bla << "   @"<< this << endl;

    cout << "   size_="<< size_
         << "   prec_=" << prec_
         << "   radix()="<< radix()
         << endl;

    cout << "   DIGIT[]= "<< (void *)limbs_
         << " ... " << (void *)(limbs_ + size_ - 1)
         << ":  " << endl;

    for (ulong k=0; k<n; ++k)  cout << limbs_[k] << "," << ((k+1)&15?"":"\n");
    cout << endl;
    cout << endl;
}
//--------------



char *
get_radix_format(ulong r)
{
    static char fmt[22];
    strcpy(fmt,"%05d,");
    //          01234

    fmt[2] = (char)('0' + (char)ceil(log((double)r)/log(10.0)));

    if ( 10 == hfdata::rxbase )
    {
        fmt[2] = (char)('0'+ (char)(hfdata::rxbspw));
        fmt[4] = 0;
    }

    if ( 16 == hfdata::rxbase )
    {
        fmt[2] = (char)('0'+ (char)(hfdata::rxbspw));
        fmt[3] = 'x';
        fmt[4] = 0;
    }

    return fmt;
}
//--------------


inline int
ispowof(long x, int p)
// returns 0 or k so that p^k==x
{
    int k=0;
    while( x>1 && x==(x/p)*p )  { x/=p; k++; }
    return (x==1?k:0);
}
//--------------
// used for ...

void // static
hfdata::radix(ulong r, const char *rfmt/*=0*/)
{
    jjassert( r>=2 ); // " radix must be >=2 "

    jjassert( r<=(1<<(8*sizeof(LIMB))) ); // " radix doesn't fit into LIMB "

    rx = r;

    ldrx = ld(rx);
    lg10rx = log((double)rx) /log(10.0);

    rxbase = rx;
    rxbspw = 1;

    int p;
    p = ispowof(rx,10);
    if ( p )
    {
        rxbase = 10;
        rxbspw = p;
    }

    p = ispowof(rx,16);
    if ( p )
    {
        rxbase = 16;
        rxbspw = p;
    }

    if ( !rfmt ) rxfmt = get_radix_format(rx);
    else         rxfmt = rfmt;

    if ( rx==((uint)1<<ldrx) )
    {
        rx2pw = true;
	rxbits = ldrx;
    }
    else
    {
        rx2pw = false;
	rxbits = ldrx+1;
    }
}
//--------------



#define  WARNIF(x)  if ( x ) { cerr << "\nWARNING: " << #x << endl;  errq=1; }
int
hfdata::check() const
{
    int errq = 0;

    WARNIF( !limbs_ );
    WARNIF( !size_ );

    WARNIF( ndata<0 );

    WARNIF( rx>65536 );

    for (ulong k=0; k<prec_; ++k)
    {
        if ( limbs_[k] >= rx )
        {
            cerr << "\nWARNING: limbs_[" << k << "] == " << limbs_[k] << " > rx"<< endl;
            errq = 1;
            jjassert( limbs_[k]<rx );
        }
    }

    return errq;
}
//--------------



void // static
hfdata::print_statistics(ulong /*n*/)
{
    cout << " hfdata: bytes currently allocated: "
         << hfdata::nbytes << endl;

    cout << " hfdata: max bytes allocated: "
         << hfdata::nbytesmax << " (plus workspace)" << endl;
}
//--------------
