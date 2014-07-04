
#include "fxttypes.h"

#include "workspace.h"
#include "aux1/copy.h"  // fill()

#include "jjassert.h"  // jjnote: asserts used in code: workspace class for hfloat
#include "fxtio.h"

#include <cstdlib>  // getenv(), atol()
#include <cstring>  // strlen()

static ulong str2ulong(const char *p)
{
    long v = 0;
    if ( p!=0 )
    {
        v = atol(p);
        for (long i=(long)strlen(p); i>=0; --i) // jjcast
        {
            char c = p[i];
            if ( (c=='k') || (c=='K' ) )  { v *= (1UL<<10); break; }
            if ( (c=='m') || (c=='M' ) )  { v *= (1UL<<20); break; }
            if ( (c=='g') || (c=='G' ) )  { v *= (1UL<<30); break; }
        }
    }
    return (ulong)v;  // jjcast
}
// -------------------------


// tuning parameter:
#define  WS_EXTRA_DOUBLES  0  // 0 (default) or 1: pad space to avoid cache problems
#define  WS_SENTINEL  0  // 0 (default) or 1 (catch some accesses beyond requested size)
//
#if ( WS_SENTINEL==1 )
#warning 'FYI: workspace sentinel active'
#endif // WS_SENTINEL

double *workspace::ptr_ = 0;
int    workspace::inuse_ = 0;

const ulong workspace::extra_doubles_ = WS_EXTRA_DOUBLES;

ulong *workspace::sentinel_ = 0;
ulong  workspace::sentinel_val_ = (ulong)~0;

ulong workspace::nbytes_ = 0;
ulong workspace::ndoubles_ = 0;

ulong workspace::noswap_bytes_ = 0;
ulong workspace::cache_bytes_ = 0;

ulong workspace::noswap_doubles_ = 0;
ulong workspace::cache_doubles_ = 0;

const char * const workspace::classname = "workspace";


// The instance 'workspace_initializer' of the class workspace_init
//   initializes the 'workspace' class:
// It MUST be initialized as the last static member of class workspace!
workspace_init workspace::workspace_initializer = workspace_init();



#define  KILOBYTE  (ulong(1UL<<10))
#define  MEGABYTE  (ulong(1UL<<20))
#define  GIGABYTE  (ulong(1UL<<30))

workspace_init::workspace_init()
{
//    cerr << __PRETTY_FUNCTION__ << endl;
    char *p;
    workspace::noswap_bytes_ = 32*MEGABYTE; // note: magic default
    p = getenv("NOSWAP_BYTES");
    if ( p!=0 )
    {
        ulong me = 0;
        me = str2ulong(p);
        if ( 0!=me )  workspace::noswap_bytes_ = me;
    }
    workspace::noswap_doubles_ = workspace::noswap_bytes_/sizeof(double);

    workspace::cache_bytes_ = 256*KILOBYTE; // note: magic default
    p = getenv("CACHE_BYTES");
    if ( p!=0 )
    {
        ulong me = 0;
        me = str2ulong(p);
        if ( 0!=me )  workspace::cache_bytes_ = me;
    }
    workspace::cache_doubles_ = workspace::cache_bytes_/sizeof(double);
}
// -------------------------

workspace_init::~workspace_init()
{
    double *p = workspace::ptr_;
    if ( p )  delete [] p;
}
// -------------------------


void // static
workspace::grow(ulong n)
{
    jjassert( !inuse_ ); // "tried to resize workspace while in use"
    if ( nbytes_<n )
    {
        if ( ptr_ )
        {
//            operator delete (ptr_);
            delete [] ptr_;
            ptr_ = 0;
        }

        ulong dn = n/sizeof(double);
        if ( dn*sizeof(double) != n )  ++dn;

#if ( WS_SENTINEL==1 )
        dn += 1;  // +1 for sentinel
#endif // WS_SENTINEL

//        dn += extra_doubles_;  // not recorded in ndoubles_ !

        if ( n!=0 )  ptr_ = new double[extra_doubles_+dn];

        nbytes_ = n;
        ndoubles_ = dn;

//        cerr << __PRETTY_FUNCTION__
//             << ": growing to "
//             << nbytes_ << " bytes == "
//             << ndoubles_ << " doubles"
//             << endl;
//        fill((double *)ptr_, dn, 3.1415);  // jjcast
//        jjassert( nbytes_ <= noswap_bytes_ );
    }
}
// -------------------------


void // static
workspace::get_ws(char *&p, ulong n)
{
    jjassert( !inuse_ );

//    cerr << "\n" << __FUNCTION__ << " n=" << n
//         << "  == " << n/sizeof(double) << " doubles" << endl;

    if ( n>nbytes_ )  grow(n);

    inuse_ = 1;
#if ( WS_SENTINEL==1 )
    p = (char*)ptr_ + nbytes_ - n;  // give mem at end of pool  // jjcast
    sentinel_ = (ulong *)(p + n + extra_doubles_*sizeof(double));  // jjcast
    *sentinel_ = sentinel_val_;
#else
    p = (char*)ptr_;  // jjcast
#endif // WS_SENTINEL
}
// -------------------------

void // static
workspace::get_ws(LIMB *&p, ulong n)
{
    get_ws((char *&)p, n*sizeof(LIMB));  // jjcast
}
// -------------------------

void // static
workspace::get_ws(double *&p, ulong n)
{
    get_ws((char *&)p, n*sizeof(double));
}
// -------------------------


void // static
workspace::get_noswap_ws(char *&p, ulong n)
{
    jjassert( n <= noswap_bytes_ );
    get_ws(p,n);
}
// -------------------------

void // static
workspace::get_noswap_ws(LIMB *&p, ulong n)
{
    get_noswap_ws((char *&)p, n*sizeof(LIMB));
}
// -------------------------

void // static
workspace::get_noswap_ws(double *&p, ulong n)
{
    get_noswap_ws((char *&)p, n*sizeof(double));
}
// -------------------------


void // static
workspace::let_ws()
{
    jjassert( inuse_ );
#if ( WS_SENTINEL==1 )
    jjassert( *sentinel_ == sentinel_val_ ); // "access out of bounds in workspace"
#endif // WS_SENTINEL
    inuse_ = 0;
}
// -------------------------


static void
size_info(const char *bla, ulong ti)
{
    const double t = (double)ti;
    const double k = 1024, m = k*k;
    double d = t/sizeof(double);
    cout << bla << (ulong)t << " bytes ";
//    cout << " = " << d << " doubles ";
    if ( t>=m )
    {
        cout << " =" << t/m << " MB ";
        cout << " =" << d/m << " Mdoubles ";
    }
    else if ( t>=k )
    {
        cout << " =" << t/k << " kB ";
        cout << " =" << d/k << " kdoubles ";
    }

    cout << endl;
}
// -------------------------


void // static
workspace::print_info()
{
    size_info(" workspace: size  = ", nbytes());
    cout << " workspace: #doubles = " << ndoubles() << endl;
    cout << " workspace: extra (pad) doubles = " << extra_doubles_ << endl;
    size_info(" workspace: noswap size = ", noswap_bytes());
    size_info(" workspace: cache size  = ", cache_bytes());
}
// -------------------------
