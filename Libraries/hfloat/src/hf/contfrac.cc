
#include "hfloat.h"

#include <cmath> // floor()

//#define  VOODOO  // for debugging
#if defined VOODOO
#include <fxt/fxtio.h>
#endif


int
hfloat_to_contfrac(const hfloat &x, ulong n, long cf[])
//
//  Convert continued fraction to hfloat.
//  This is a very sloppy implementation.
//
{
    hfloat t( x.prec() );
    t = x;

    ulong k = 0;
    long  xi = 0;
#if defined VOODOO
    cout << n << " terms requested in hfloat_to_contfrac() " << endl;
#endif

    while ( k<n )
    {
        double di;  hfloat2d(t, di);  xi = (long)floor(di);

        cf[k] = xi;

#if defined VOODOO
        print(" :: t=",t,16);
        cout << " ::  hfloat_to_contfrac(): term " << k << " = " << xi << endl;
#endif

        t -= xi;

        if ( t.is_zero() )
        {
            for ( ++k; k<n ; ++k)  cf[k]=0;
            break;
        }

#if defined VOODOO
        print(" ::  t=",t,16);
#endif

        inv(t, t);

        ++k;
    }

    return 0;
}
//====================== end HFLOAT_TO_CONTFRAC ==========================


int
contfrac_to_ratio(const long cf[], ulong n, hfloat &p, hfloat &q)
//
//  convert continued fraction to ratio
//  this is a very careless implementation ...
//
{
    if ( n==0 )
    {
        p = cf[0];
        q = 1;
        return 0;
    }

    ulong prec = p.prec();
    hfloat pmm(prec), qmm(prec);
    hfloat pm(prec), qm(prec);

    pmm = 1;
    qmm = 0;

    pm = cf[0];
    qm = 1;

#if defined VOODOO
    hfloat *x = 0;
    hfloat s5(prec);
    sqrt(5,s5);

    if ( p!=0 )
    {
        x = new hfloat(prec);
        *x = p;
    }
#endif

    for (ulong k=1; k<=n; ++k)
    {
        p = cf[k]*pm + pmm;
        q = cf[k]*qm + qmm;

#if defined VOODOO
        cout << k << ": " << endl;
        print(" p[k]= ", p, 16);
        print(" q[k]= ", q, 16);
        //        cout << " q[k]= " << q << endl;
        //        cout << " p/q=  " << (pmm=p/q) << endl;

        pmm = p;
        pmm /= q;
        //        print(" p/q=  ",pmm,32);

        if ( x )
        {
            // how good approx is (absolute value):
            pmm -= (*x);
            print(" p/q-x= ", pmm, 3);

            // how 'surprising' approx is:
            sqr(q,qmm);
            qmm *= s5;
            qmm *= pmm;  // in the order of 1, smaller values indicate good approx
            print(" (p/q-x) * (sqrt(5)*q^2)= ", qmm, 3);
        }
#endif
        pmm = pm;
        pm = p;

        qmm = qm;
        qm = q;
    }


#if defined VOODOO
    if ( x )  delete x;
#endif

    return 0;
}
//====================== end CONTFRAC_TO_RATIO ==========================


int
contfrac_to_hfloat(const long cf[], ulong n, hfloat &x)
//
//  convert continued fraction to hfloat
//  this is a very straightforward (inefficient) implementation ...
//
{
    if ( n==0 )  x = 0;
    else         x = cf[--n];

    while ( n-- )
    {
        if ( cf[n]==0 )  break;
        inv(x,x);
        x += cf[n];
    }

    return 0;
}
//====================== end CONTFRAC_TO_HFLOAT ==========================

