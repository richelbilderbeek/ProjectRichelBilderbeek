
#include "hfloat.h"
#include "hfdata.h"
#include "hfverbosity.h"  // hfprintcd()

#include "fxtmult.h"
#include "workspace.h"
#include <fxt/aux1/shift.h> // shift_left()

#include <fxt/fxtio.h>

#include <cmath>


//#define  NDEBUG
#include <fxt/jjassert.h>


// 'real' initialisation of static members in init.cc !
// (because of the special initialisation mechanism)
const char *hfloat::version_string = "17-November-2012";
double hfloat::overflow  = +1000000000.0;  // biggest exponent, must fit into type long
double hfloat::underflow = -1000000000.0;  // smallest exponent, must fit into type long
int   hfloat::forbid_unnormalized = 1;
int   hfloat::check_itiroot_result = 0;

ulong hfloat::defaultprec = 64;
ulong hfloat::longlimbs = 64;

// (pointers to) constants used for calculations,
// will be allocated and computed when needed:
hfloat* hfloat::const_pi = 0;
hfloat* hfloat::const_logrx = 0;
hfloat* hfloat::const_sqrt2 = 0;
hfloat* hfloat::const_logsqrt2 = 0;

// the instance 'hfloat_initialiser'
// of the class hfloat_init
// initialises the 'hfloat' class:
// it MUST be the initialised as the last static member of class hfloat !
hfloat_init hfloat::hfloat_initialiser = hfloat_init
(           // description             (default)
 10000,     // default radix           (10000)
 1024,      // default precision in LIMBs  (1024)
 1,         // whether to check fxt mult via sum of digit test (1)
 0          // whether to check iterations for inverse n-th root (0)
 );


void  // static
hfloat::hello()
{
    cout << "  ----============== HFLOAT version " << hfloat::version() << " ===============---- " << endl;
    cout << "       author: Joerg Arndt,  email: arndt (AT) jjj.de " << endl;
#if defined  __GNUC__
//#define  XSTR(s)  STR(s)
//#define  STR(s)  #s
    cout << "     compiler used: GNU C " << __VERSION__ << endl;
    cout << "     compilation date: " << __DATE__  << ", " << __TIME__ << endl;
#if defined OFLAGS
    cout << "     compilation flags were:\n   " << OFLAGS << endl;
#endif // OFLAGS
#endif  // __GNUC__
    cout << "       HFLOAT is online at http://www.jjj.de/hfloat/   " << endl;
    cout << "  ----===========================================================----  " << endl;
    cout << endl;
}
//--------------


static int
unique_id()
{
    static int idnum = 0;
    ++idnum;
    return idnum;
}
//--------------


// explicit
hfloat::hfloat(ulong n/*=defaultprec*/)
    : hfid(unique_id()), ex(0), sg(0)
{
    if ( hfverbosity::printhfcd )
        cout << "\n hfloat(size=" << n << "): "
             << "#" << id();

    dt = new hfdata(n);
//    jjassert( hfloat_init::init_done == true );
}
//--------------


hfloat::hfloat(const hfloat &h)
    : hfid(unique_id())
{
    if ( hfverbosity::printhfcd )
        cout << "\n hfloat(id=" << h.id() << "): "
             << "#" << id();

    dt = new hfdata( h.size() );
    copy(h);
}
//--------------


hfloat::~hfloat()
{
    if ( hfverbosity::printhfcd )
        cout << "\n ~hfloat(): "
             << "#" << id()
             << "  size=" << size();

    delete dt;
}
//--------------


void
hfloat::copy(const hfloat &h)
{
    if ( this==&h )  return;  // nothing to do

    if ( hfverbosity::printcopy )
    {
        double hd;
        hfloat2d(h,hd);
        cout << "hfloat::copy(const hfloat &h): (double)h=" << hd << endl;
    }

    sign( h.sign() );
    exp( h.exp() );
    data()->copy( *h.data() );  // copy data
}
//--------------


double
prec_convert(ulong p, ulong rx2, ulong rx1/*=0*/)
{
    if ( 0==rx1 )  rx1 = hfloat::radix();
    return  (double)p * log((double)rx1)/log((double)rx2);
}
//--------------

void
hfloat::prec(ulong p, int rr/*=0*/)
{

    ulong np =p;
    if ( rr!=0 )  np = (ulong)(ceil(prec_convert(p,rr)));

    if ( hfverbosity::printresize )
        if ( np>size() )
            cout << "\n  resize hfloat #" << id() << endl;

    dt->prec(np);
}
//--------------

void
hfloat::exp(long x)
{
    jjassert( x>=underflow );
    jjassert( x<=overflow );
    ex = x;
}
//--------------


LIMB
hfloat::get_limb(ulong n) const
{
    if ( is_zero() )  return 0;

    if ( n>=prec() )  return 0; // index>prec --> return 0
    else              return (data()->dig())[n];
}
//--------------


void
hfloat::set_limb(ulong n, LIMB x)
{
    if ( n<prec() )  (data()->dig())[n] = x;
    else  jjassert( 0 ); // "hfloat::set_limb(): index out of range"
}
//--------------

LIMB
hfloat::get_limb_rtd(long n) const  // rtd = relative to dot
{
    if ( is_zero() )  return 0;

    long v = exp()-1-n;
    if ( v<0 )  return 0;
    else        return get_limb((ulong)v);
}
//--------------

int
hfloat::odd() const
{
    return  get_limb_rtd(0) & 1;
}
//--------------


int
hfloat::even() const
{
    return !odd();
}
//--------------


//int
//hfloat::get_bit(ulong n) const
//{
//    if ( is_zero() )  return 0;
//
//    ulong bpl = data()->rxbits;  // bits per limb
//    ulong v = n/bpl;
//    if ( v>=prec() )  return 0;
//    ulong u = (ulong)get_limb(v);
//    ulong m = ((ulong)1<<( bpl - 1 - (n%bpl)));
//    m &= u;
//
//    if ( m )  return 1;
//    else      return 0;
//}
////--------------
//
//int
//hfloat::get_bit_rtd(long n) const  // rtd = relative to dot
//{
//    if ( is_zero() )  return 0;
//
//    long bpl = data()->rxbits;  // bits per limb
//    ulong u = (LIMB)get_limb_rtd(n/bpl);
//    ulong m = ((ulong)1<<(n%bpl));
//    m &= u;
//
//    if ( m )  return 1;
//    else      return 0;
//}
////--------------


int
hfloat::normalized() const
{
    if ( is_zero() )  return 1;

    // first LIMB is zero:
    if ( (dt->dig())[0] == 0 )  return 0;

    // underflow:
    if ( ex < underflow )  return 0;

    // overflow:
    if ( ex > overflow )  return 0;

    return 1;
}
//--------------


void
hfloat::normalize()
{
    if ( normalized() )  return;

    ulong f;
    for (f=0; f<prec(); ++f)    // search first digit != 0
    {
        if ( (dt->dig())[f]!=0 )  break;
    }

    if ( f!=0 )
    {
        shift_left(dt->dig(), dt->prec(), f);
	ex -= f;
        if ( f>=prec() )  set_zero();  // all digits are 0
    }

    if ( ex < underflow )  set_zero();  // underflow

    if ( ex > +overflow )  // overflow
    {
	if ( sg==0 )  sg=+1;
        jjassert( 0 ); // " Overflow "
    }
}
//--------------


void
hfloat::rand01()
{
    sign(+1);
    exp(0);
    (*data()).rand(0,prec());
    normalize();
}
//--------------


void
hfloat::dump(const char *bla, long n) const
{
//    cout << endl;
    if ( bla )  cout << bla << endl;
    print("value=", *this, 7);

    cout << " id()= " << id()
         << "   @"<< this
         << "  sign()=" << sign()
         << "  exponent()=" << exp()
         << endl;

    dt->dump(" data:",n);
}
//--------------


int
hfloat::check() const
{
    jjassert( dt );
    if ( hfloat::forbid_unnormalized )  jjassert( normalized() );
    return  ( dt->check() );
}
//--------------


void // static
hfloat::default_prec(ulong n)
{
    defaultprec = n;
    ulong wsz = fxtmult::ndoubles_fxtmul(n,n) * sizeof(double);
    ulong nsz = workspace::noswap_bytes();
    if ( wsz>nsz )  wsz = nsz; // ... and use mass storage multiply
    workspace::grow(wsz);
}
//--------------


void // static
hfloat::print_info()
{
    cout << " hfloat: radix = " << radix() << endl;

    ulong dp = default_prec();
    cout << " hfloat: default precision is " << dp << " LIMBs" << endl
         << " hfloat:  = " << prec_convert(dp,10) << " dec"
         << " / " << prec_convert(dp,16) << " hex"
         << " digits"
         << "  = "  << prec_convert(dp,2) << " bits"
         << endl;

    cout << " hfloat: iterations for inverse n-th root ";
    if ( check_itiroot_result )  cout << "ARE ";
    else                         cout << "are NOT ";
    cout << "checked " << endl;

    fxtmult::print_info(dp);

    workspace::print_info();

    cout << endl;
}
//-----------------------------
