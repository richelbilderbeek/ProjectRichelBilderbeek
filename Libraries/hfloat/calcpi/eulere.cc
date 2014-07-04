
#include <cmath>
#include <iostream>
#include <cstdlib>

#include "hfloat.h"


// Some decimal digits for comparison:
//2.718281828459045235360287471352662497757247093699959574966967627724076630353


#define STIRL(x) \
floor((x*ROOTCT*log(ROOT)+(x+0.5)*log(x)-x+0.5*log(2.0*M_PI))/log(drx))

#define STIRL_SIMPLE(x) \
floor(((x+0.5)*log(x)-x+0.5*log(2.0*M_PI))/log(drx))


#define VARIANT_X 0  // use variant 0 (variant 1 is buggy!)


int
euler_e(hfloat &e)
{
#define  RTPW  256

    e = 1;
    e /= RTPW;
    exp(e,e);
    pow(e,RTPW,e);

    return 0;
}
//================================================


int
euler_e_series(hfloat &e)
{
    const long nn = e.prec();
    int    k;
    int    rx;   // radix
    double drx,l10rx;  // (double)radix, log10(drx)
    hfloat a(nn),b(nn),c(nn),d(nn);

    rx = (int)a.radix();
    drx = (double)rx;
    l10rx = log(drx)/log(10.0);


#if  ( VARIANT_X == 1 )
    //
    // the ROOT stuff here is a trick to make only short divs necessary
    //
    int    maxk, i;
    double dd;

    // return := e^(1/(ROOT^ROOTCT)):
    // set ROOTCT to 6 and ROOT to 8192
    // for RADIX=10000 and LDN=16 (=> 2^18 decimal digits of e)
#define ROOT   (8192)
#define ROOTCT (6)

    //#define ROOT   (1)
    //#define ROOTCT (0)

    a=1;
    c=1;

    maxk=10;
    do
    {
        //        cout << "\n stirl(" << maxk << ")=" << STIRL(maxk));

        ++maxk;

        if ( maxk >= rx )
        {
            maxk = rx-1;
            break;
        }
    }
    while( STIRL(maxk) < nn );

    cout << "\n maxk=" << maxk;

    dd = STIRL(maxk);

    cout << "\n ==> " << dd
         << " digits (or "
         << dd*l10rx << " decimal digits) will be correct ... "
         << endl;

    //    i=min(nn,dd+3); // no long operations here !
    //    a.prec(i); b.prec(i); c.prec(i);


    for (k=1; k<=maxk ; ++k)
    {
        for (i=0; i<ROOTCT; ++i)  div(a,(ulong)(ROOT),a);  // in place operation
        div(a,(long)(k),a);     // in place operation
        add(a,c,c);
    }

    print("\n c:\n",c);

    if (ROOT!=1)
    {
        for (i=0; i<ROOTCT; ++i)
        {
            k=ROOT;
            do
            {
                k/=2;
                sqr(c,a);
                c.copy(a);

            }
            while (k!=1);
        }

        print("\n c:\n",c);
    }

#else  // ---------------------------------------

    int    maxk;
    double dd;

    hfloat kmed(3);

    i2hfloat(1,a);
    i2hfloat(1,b);
    i2hfloat(1,c);

    maxk=10;
    do
    {
        //        cout << "\n stirl(" << maxk << ")=" << STIRL_SIMPLE(maxk));
        ++maxk;
    }
    while (STIRL_SIMPLE(maxk)<nn);

    cout << "\n maxk=" << maxk;

    dd=STIRL_SIMPLE(maxk);

    cout << "\n ==> " << dd
         << " digits (or "
         << dd*l10rx << " decimal digits) will be correct ... "
         << endl;


    for (k=1; k<=maxk ; ++k)
    {
//        div(a,(int)(k),a);     // in place operation
        div(a,(ulong)(k),a);     // in place operation

        add(a,c,c);
    }

    print("\n c:\n",c);

    print("\n last term added was=\n",a,7);


#endif //   ( VARIANT_X == 1 )

    e = c;

    return 0;
}
