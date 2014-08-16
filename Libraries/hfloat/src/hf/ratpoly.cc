
#include <cmath>
#include <fxt/fxtio.h>
#include <fxt/jjassert.h>

#include <fxt/aux0/gcd.h>
#include "hfloat.h"

#include "hfparanoia.h"

void
print_ratpoly(const char *bla, ulong deg, const long *num, const long *den)
{
    cout << bla;

    for(ulong k=0; k<=deg; ++k)
    {
        cout << " + " << num[k] << "/" << den[k] << "*x^"<<k;
    }

    cout << endl;
}
// ===================== end =======================



void
ratpoly_derive(ulong deg, const long *num, const long *den,
               long *dnum, long *dden)
//
// may be used in place, i.e. dnum==num, dden=den
//
{
    dnum[deg] = 0;
    dden[deg] = 1;

    for (ulong k=0; k<deg; ++k)
    {
        dnum[k] = (k+1) * num[k+1];
        dden[k] = den[k+1];

        long  g = gcd(dnum[k], dden[k]);

        if ( g!=1 )
        {
            dnum[k] /= g;
            dden[k] /= g;
        }
    }
}
// ===================== end =======================



void
ratpoly(const hfloat &x, ulong deg, const long *num, const long *den, hfloat &p)
//
// compute p(x)=\sum_{k=0}^{deg}{num[k]/den[k]*x^k}
//
{
#ifdef  HF_PARANOIA
    jjassert( x.OK() );
//    print_ratpoly("\nRatpoly=", deg, num, den );
#endif

    ulong  n = p.prec();
    hfloat a(n), b(n);

    b = num[deg];
    if ( den[deg]!=1 )  b /= den[deg];

    for (long k=deg-1; k>=0; --k)
    {
        b *= x;

        if ( num[k]!=0 )
        {
	    a = num[k];
            if ( den[k]!=1 )  a /= den[k];
            b += a;
	}
    }

    p = b;
}
// ================== end =====================
