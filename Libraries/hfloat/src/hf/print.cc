


#include "hfloat.h"

#include <fxt/jjassert.h>
#include <fxt/fxtio.h>

#include <cstdlib>  // exit()
#include <fstream>
#include <cstdio>  // snprintf()


int hf_save(std::ostream &os, const char *what, const hfloat &a, ulong s, ulong e);
int hf_save_nn(std::ostream &os, const char *what, const hfloat &a, ulong s, ulong e);

static bool pretty_print = true;
//void set_pretty_print(bool q)  { pretty_print = q; }


static inline void pform(std::ostream &os, const LIMB x)
{
    char t[16];
    snprintf(t, 16, hfdata::rxfmt, x);
    os << t;
}
//========== end =================

int
hf_save(std::ostream &os, const char *what, const hfloat &a, ulong s, ulong e)
{
    int r = hf_save_nn(os, what, a, s, e);
    os << endl;
    return r;
}
//========== end =================

static void
print_limbs(std::ostream &os, LIMB *ad, ulong s, ulong e, int csq=0)
{
    os << setfill('0');


    ulong k = s;
    pform(os, ad[k]);
    ++k;

    if ( csq )  // comma seperated
    {
        os << ',';
        for (  ; k<e-1; ++k)
        {
            pform(os, ad[k]);
            os << ',';
        }
    }
    else
    {
        for (  ; k<e-1; ++k)  pform(os, ad[k]);
    }

    pform(os, ad[k]);
}
//========== end =================

int
hf_save_nn(std::ostream &os, const char *what, const hfloat &a, ulong s, ulong e)
//
// print digits s...e
// e==0 => print all digits
// negative n => print last n LIMBs
//
// return:  0 == ok
//         -1 == failure
{
//    os << "RXFMT=[" << hfdata::rxfmt << "]\n";

    if ( 0==e )  e = a.prec();
    if ( e>a.prec() )  e = a.prec();
    jjassert( s<=e );

    if ( what!=NULL )  os << what << flush;

    if ( os.fail() )
    {
        cerr<< "\n save(): FAILED ! "<<endl;
        return -1;
    }


    if ( a.is_zero() )
    {
        os << "0.0";
        return 0;
    }

    LIMB *ad = a.data()->dig();

    if ( s==0 )  os << ( a.sign()<0 ? '-' : '+' ) << '.';

    int rxb = (int)(hfdata::rxbase);
    if ( 16==rxb )  os << setbase(rxb);

    int   z = 0;  // # of leading zeros
    int  rx = (int)(hfdata::rx);
    if ( (0==s) && (rxb!=rx) )
    {
        int    p = (int)(hfdata::rxbspw);
        LIMB   a0 = ad[s];
        --z;
        while ( (a0<rx) && (p--) )  // count leading zeros
        {
            rx /= rxb;
            ++z;
        }

        ulong  k = s;
        if ( z )  // print nonzero digits of first LIMB
        {
            os << ad[k];
            k++;
        }

        print_limbs(os, ad, k, e, 0);
    }
    else
    {
        print_limbs(os, ad, s, e, 0);
    }

    os << setbase(10) << setfill(' ');

    if ( 0==s )  // print exponent
    {
        if ( pretty_print )
        {
            os << "*" << rxb
               << "^" << (long)((hfdata::rxbspw) * a.exp()-z);
        }
        else
        {
            os << "*" << hfdata::radix() << "^" << a.exp();
            //                os << " R " << a.exp();
        }
    }

    return 0;
}
//========== end =================


void
print(const hfloat &r, ulong n/*=0*/)
{
    save(cout, "", r, n);
}
//======== end ============


void
print(const char *what, const hfloat &a, ulong n/*=0*/)
{
    save(cout, what, a, n);
}
//========== end =================


void
print_last(const char *what, const hfloat &a, ulong n)
{
    save_last(cout, what, a, n);
}
//========== end ============


void
save(std::ostream &os, const hfloat &r, ulong n/*=0*/)
{
    if ( n==0 )  n = r.prec();

    hf_save(os,"", r ,0, n);
}
//======== end ============

void
save_nn(std::ostream &os, const char *what, const hfloat &a, ulong n/*=0*/)
{
    if ( n==0 )  n = a.prec();

    hf_save_nn(os, what, a, 0, n);
}
//========== end =================

void
save(std::ostream &os, const char *what, const hfloat &a, ulong n/*=0*/)
{
    if ( n==0 )  n = a.prec();

    hf_save(os, what, a, 0, n);
}
//========== end =================


void
save_last(std::ostream &os, const char *what, const hfloat &a, ulong n)
{
    ulong s;
    if ( n>a.prec() )  s = 0;
    else               s = a.prec()-n;

    hf_save(os, what, a, s, a.prec());
}
//========== end ===============


void
save(const char* fname, const hfloat &r)
{
    std::ofstream datfile;

    datfile.open(fname,ios::out);
    jjassert( datfile!=NULL );

    save(datfile, NULL, r, r.prec());

//    datfile.flush();

    if( datfile.fail() )
    {
	cerr<<"\n save(): ERROR saving data ! (exiting) "<<endl;
	exit(-666);
    }

    datfile.close();
}
//======== end ============
