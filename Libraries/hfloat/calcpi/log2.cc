
#include <cmath>
#include <iostream>
#include <cstdlib>

#include "hfloat.h"


#define  VARIANT_AGM  1


int log2(long n, hfloat &l)
{
    hfloat a(n), b(n), c(n), d(n);


#if  ( VARIANT_AGM == 1 )

    isqrt(2, b);  // b = 1/sqrt(2) = 2^(-1/2)
    log(b, c);    // log(2^(-1/2)) = -1/2*log(2)
    mul(c, (long)-2, d);   // log(2)
    cout << "\n\n log(2)=\n";
    print("\n logarithm=\n",d);

#else

    //
    // == \sum_{k=0}^{\infty}{1/((2*k+1)*3^(2*k+1))}
    //

    int kmax = (int)((n*log((double)a.radix())/log(3.0)-1.0)/2.0)+2;

    cout << "\n adding " << kmax+1 << " terms ... \n";

    a = 1;
    b = 3;
    d = 0;

    for(long k=0; k<=kmax; k++)
    {
        div(a, 2*k+1, c);   // c = 1/(2k+1)
        div(b, (long)9, b); // b = 1/3^(2k+1)
        mul(c, b, c);       // c = 1/((2*k+1)*3^(2*k+1))
        add(c, d, d);       // add up
    }

    mul(d, (long)2, d);

    print("\n log(2)= \n", d);

#endif // ( VARIANT_AGM == 1 )

    l = d;

    return 0;
}
// -------------------------


