
#include "hfloat.h"
#include "hfdatafu.h"
#include <fxt/aux0/sign.h> // sign(), Abs()
#include <fxt/aux1/copy.h>  // null()

#include <fxt/jjassert.h>
#include "hfparanoia.h"


#include <values.h>  // MAXLONG
#include <cmath>  // log()
#include <sstream>
#include <cstring>  // strcspn()


#include "hfdata.h"

//#include <cmath>
//#include <fxt/fxtio.h>
//#include <ctype.h>
#include <cstdlib>  // exit()


#define istrstream istringstream

#define HUGE_EXP  307
#define HUGE_DBL  (1.0e+307) // jjnote: use values from header

int hf_to_double(const hfloat &a, double &d);
ulong hf_from_double(double d, hfloat &a);
int hf_to_int(const hfloat &a, long &i);
ulong hf_from_int(long i, hfloat &a);
ulong hf_from_uint(ulong i, hfloat &a);


int
hf_to_double(const hfloat &a, double &d)
{
    if ( a.is_zero() )
    {
        d = 0.0;
        return 0;
    }

    const double drx = (double)hfdata::rx;
    dt_mantissa_to_double(*a.data(),d);

    // jjnote: abort in lib:
    jjassert( (long)(log(d)+(double)a.exp()*log(drx)) <= HUGE_EXP ); // " overflow while converting to double "

    d *= a.sign();
    d *= pow(drx,(double)a.exp());

    return 0;
}
//===================== end =======================


ulong
hf_from_double(double d, hfloat &a)
//
// returns how many LIMBS were made
//
{
    if ( 0==d )
    {
        a.set_zero();
	return 1;
    }

    a.sign( d<0 ? -1 : (d==0?0:1) );
    d = fabs(d);

    jjassert( d<HUGE_DBL );

    const double drx  = (double)hfdata::rx;
    const double drx1 = 1.0/(double)hfdata::rx;
    long ex = 0;
    while ( d<1.0 )
    {
        d *= drx ;
        ex--;
    }

    while ( d>=1.0 )
    {
        d *= drx1 ;
        ex++;
    }
    a.exp( ex );

    ulong k = dt_double_to_mantissa(d, *a.data());

    a.normalize();

#ifdef  HF_PARANOIA
    jjassert( a.OK() );
#endif

    return k;
}
//======================= end =======================


int
hf_to_int(const hfloat &a, long &i)
{
    double d;
    hf_to_double(a, d);
    d = floor(d+0.5);

    // jjnote: abort in lib:
    jjassert( (d>=MINLONG) && (fabs(d)<=MAXLONG) ); // " overflow in conversion to integer "

    i = (long)d;
    return 0;
}
//================== end =====================



ulong
hf_from_int(long i, hfloat &a)
// returns how many LIMBS were made
{
    ulong k;
    if ( 0==i )
    {
        a.set_zero();
	k = 1;
    }
    else
    {
        ulong u = (ulong)Abs(i);
        k = hf_from_uint(u,a);
        a.sign( (int)sign(i) );
    }

#ifdef  HF_PARANOIA
    jjassert( a.OK() );
#endif

    return k;
}
//================== end =======================


ulong
hf_from_uint(ulong i, hfloat &a)
// returns how many LIMBS were made
{
    ulong k;
    if ( 0==i )
    {
        a.set_zero();
	k = 1;
    }
    else
    {
        k = dt_int_to_mantissa(i, *a.data());
        a.exp( (long)k );  // jjcast
        a.sign(+1);
    }

#ifdef  HF_PARANOIA
    jjassert( a.OK() );
#endif

    return k;
}
//================== end =======================


ulong
i2hfloat(long i, hfloat &a)
// returns how many LIMBS were made
{
    return hf_from_int(i,a);
}
//============== end ===============


ulong
u2hfloat(ulong i, hfloat &a)
// returns how many LIMBS were made
{
    return hf_from_uint(i,a);
}
//============== end ===============


void
i2hfloat_prec_adj(long i, hfloat &y)
{
    y.prec( y.size() );
    ulong p = i2hfloat(i,y);
    y.prec(p);  // adjust precision of result
}
//================= end ===============


void
u2hfloat_prec_adj(ulong i, hfloat &y)
{
    y.prec( y.size() );
    ulong p = u2hfloat(i,y);
    y.prec(p);  // adjust precision of result
}
//================= end ===============



int
hfloat2i(const hfloat &a, long &i)
{
    return hf_to_int(a,i);
}
//=================== end ===============


int
hfloat2d(const hfloat &a, double &d)
{
    return hf_to_double(a,d);
}
//=================== end ===============


ulong
d2hfloat(double d, hfloat &a)
// returns how many LIMBS were made
{
    return  hf_from_double(d,a);
}
//================= end ===============



// for debug:
#define PR(x)


static void
fatal_error(const char *bla)
{
    cerr << "\n ! ERROR in hf_from_string(): "
         << bla << endl;

    exit (-1);
}
// ----------------


long discard_surrounding_blanks(const char **strp);
long read_rx_ex(const char* str, long len, long &rx, long &ex);
long read_dot_sgn(const char* str, long mlen, int &s);
long set_exponent(long dt, long fnz, long ex, long rx, long &xm);


ulong
hf_from_string(const char *str, hfloat &a)
//
// must be of the form
// [+|-] mantissa [ (*rx^) | E | e [+|-]ex]
// where rx is a power of 10
//
// this routine might be fooled be strange (invalid) strings
//
// returns # of LIMBs produced
{
    PR( cout << endl; );

    jjassert( hfdata::rxbase==10 );  // only for base a power of 10 !

    long len = discard_surrounding_blanks(&str);
    PR( cout << " hf_from_string(): len=" << len << endl; );
    jjassert( len>0 );


    // --- read radix and exponent:
    long ex;
    long rx;
    long mlen;  // length of mantissa
    mlen = read_rx_ex(str,len,rx,ex);
    PR( cout << " hf_from_string(): mlen=" << mlen << endl; );


    // --- dec dot and sign:
    long dt;
    int s;
    dt = read_dot_sgn(str, mlen, s);
    a.sign(s);

    if ( dt==mlen-1 )   // handle trailing dec pt
    {
        mlen--;
        PR( cout << " hf_from_string():  mlen=" << mlen << endl; );
        if ( mlen<=0 )  fatal_error(" ? no digits (mlen)");
    }


    // --- scan mantissa for first nonzero digit:
    long fnz;  // first nonzero digit
    fnz = (long)strcspn(str,"123456789");  // jjcast
    PR( cout << " hf_from_string(): fnz=" << fnz << endl; );

    if ( fnz>=mlen )  // no digit different from '0' found
    {
        PR( cout << " hf_from_string(): zero. " << endl; );
        a.set_zero();
        return 1;
    }


    // --- set exponent:
    long xm;
    long xx;
    xx = set_exponent(dt,fnz,ex,rx,xm);
    a.exp( xx );
    PR( cout << " hf_from_string(): LIMB exp= " << a.exp() << endl; );


    // ----- read the LIMBs
    LIMB *ad = a.data()->dig();
    long pr = a.prec();
    int  hrx = (int)(hfdata::rx);
    int  bp  = (int)(hfdata::rxbspw);

    char ls[10];  // jjnote: magic, assume 10>=bp+1
    for(long k=0; k<bp; ++k)  ls[k]='0'; // prepend zeros
    ls[bp] = 0;  // terminate string

    long j,x;
    for(x=0,j=fnz; x<1 && j<mlen ; ++x)  // --- read the first LIMB
    {
        long y;
        for(y=xm; y<bp && j<mlen ; ++y, ++j)  // get string for one LIMB
        {
            char c = str[j];
            if ( '.'==c )
            {
                ++j;
                if ( j==mlen )  c = 0;
                else            c = str[j];
            }

            ls[y] = c;
        }

        while ( y<bp )  { ls[y]='0';  ++y; }  // fill if incomplete
        PR( cout << " hf_from_string(): 1.LIMB=" << ls << endl; );

        long d;
        std::istrstream(ls) >> d;  // convert
        jjassert( d>=0 );
        jjassert( d<hrx );
        ad[x] = (LIMB)d;
    }

    for ( ; x<pr && j<mlen ; ++x)  // --- read the LIMBs
    {
        long y;
        for (y=0; y<bp && j<mlen ; ++y, ++j)  // get string for one LIMB
        {
            char c = str[j];
            if ( '.'==c )
            {
                ++j;
                if ( j==mlen )  c = 0;
                else            c = str[j];
            }

            ls[y] = c;
        }

        while ( y<bp )  { ls[y]='0';  ++y; }  // fill if incomplete
        PR( cout << " hf_from_string(): LIMB=" << ls << endl; );

        long d;
        std::istrstream(ls) >> d;  // convert
        jjassert( d>=0 );
        jjassert( d<hrx );
        ad[x] = (LIMB)d;
    }

    PR( cout << " hf_from_string(): appending " << pr-x << " zero LIMBs " << endl; );
    if ( x<pr )  null( (*a.data()).dig()+x, pr-x);  // fill remaining digits with zeros

    jjassert( a.normalized() );
    return x+1;
}
//================== end ====================


long
discard_surrounding_blanks(const char **strp)
//
// set *str to first nonblank char
// return # of nonblank chars
//
{
    const char *str = *strp;
    long j;
    long len = strlen(str);

    if ( len<=0 )  goto hier;

    // --- forget leading blanks:
    j = strspn(str," \t");
    str += j;
    len -= j;
    if ( len<=0 )  goto hier;

    // --- forget trailing blanks:
    len = strcspn(str," \t");
    if ( len<=0 )  goto hier;

hier:
    *strp = str;
    return len;
}
// ----------------


long
read_rx_ex(const char* str, long len, long &rx, long &ex)
//
// read "*10^NNN" , "eNNN" or so
// set rx=radix, ex=exponent
// return index of first char after mantissa
//
{
    long k = strcspn(str, "eE^");

    if ( k>=len )  // no exponent given
    {
        ex=0;
        PR( cout << " read_rx_ex(): default ex=" << ex << endl; );
        rx=10;
    }
    else
    {
        std::istrstream(str+k+1) >> ex;
        PR( cout << " read_rx_ex(): ex=" << ex << endl; );
        k = strcspn(str, "eE*");
        if ( k==len ) fatal_error("invalid exponent");

        if ( '*'==str[k] )  // "*rx^ex"
        {
            std::istrstream(str+k+1) >> rx;
            PR( cout << " read_rx_ex(): '*' rx=" << rx << endl; );
        }
        else    // "E" or "e"
        {
            rx = 10;
            PR( cout << " read_rx_ex(): 'E' rx=" << rx << endl; );
        }
    }

    return k;
}
// ----------------


long
read_dot_sgn(const char* str, long mlen, int &s)
//
// handle sign
// and decimal dot
// return position of decimal dot
//
{
    long dt;
    const char *cdt = strchr(str,'.');
    if ( cdt==NULL )  // no dot
    {
        dt = mlen;  // set dt at end of mantissa
    }
    else
    {
        dt = cdt-str;  // str[dt]=='.'
        jjassert( !strchr(cdt+1,'.') );  // no two dots
    }

    PR( cout << " read_dot_sgn(): dec pt=" << dt << endl; );

    s = +1;
    long i = 0;
    switch( str[i] )                   // test for sign
    {
    case '+' :  ++i;  break;
    case '-' :  ++i;  s = -1;  break;
    case '.' :  ++i;  break;
    default  :  jjassert( isdigit(str[i]) ); // must be valid digit
    }
    PR( cout << " read_dot_sgn(): sign=" << s << endl; );
    if ( i==mlen )  fatal_error(" ? no digits (i)");

    switch(str[i])                   // skip leading dec pt
    {
    case '.' :  ++i; break;
    default  :  jjassert( isdigit(str[i]) ); // must be valid digit
    }

    // here i points to first digit of the mantissa
    if ( i==mlen )  fatal_error(" ? no digits (i)");
    jjassert( isdigit(str[i]) );

    return dt;
}
// ----------------


long
set_exponent(long dt, long fnz, long ex, long rx, long &xm)
//
// return exponent wrt. hfdata::rx
// needs position of first nonzero digit (fnz),
// ex and rx from string
// xm is set to the (positive) number
//    (exponent_for_10) % (hfdata::rxbspw)
//
{
    long dx = dt-fnz;   // contribution for exponent from dec pt
    if ( dx<0 )  dx++;
    PR( cout << " set_exponent(): dx=" << dx << endl; );

    jjassert( 10==hfdata::rxbase );
    int p = 0; //hfdata::rxbspw;
    while ( 1!=rx )
    {
        p++;
        rx /= 10;
    }

    PR( cout << " set_exponent():  p=" << p << endl; );

    long tx = dx + p*ex;  // exponent for 10
    PR( cout << " set_exponent(): dx+p*ex = tx=" << tx << endl; );


    // --- set exponent according to tx
    long bp = (hfdata::rxbspw);
    long xd = tx/bp;
    xm = tx%bp;

    if ( xm>0 )
    {
        xm -= (hfdata::rxbspw);
        xd++;
    }
    PR( cout << " set_exponent(): xd=" << xd << endl; );
    xm = -xm;
    PR( cout << " set_exponent(): xm=" << xm << endl; );

    return xd;
}
// ----------------


//int
//hf_to_string(const hfloat &a, char *str)  // jjnote: not implemented
//{
//    jjassert( 0 ); // " ! not implemented ! "
//
//    str = (char *)(0* (int)(&a));  // avoid compiler warning
//
//    return 0;
//}
////================== end =====================



ulong
st2hfloat(const char *str, hfloat &a)
// returns how many LIMBS were made
{
    return hf_from_string(str,a);
}
//================= end ===============

