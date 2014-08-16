
#include  "hfloat.h"

#include <fxt/fxtio.h>

void
next_zeta3_term(ulong k, hfloat &b, hfloat &t)
// compute t(k) = (-1)^k/(k^3*binomial(2k,k))
// assume t contains t(k-1), (k=0 initialises t), therefore
// must be called with args 0,1,2,3,... (especially starting with 0)
// called by zeta3()
{
//    cout << "zeta3_term(): k=" << k << endl;

    if ( k==0 )  b = 1;

    k += 1;

    b /= (4*k-2);
    b *= k;     // b = 1/binomial(2k,k)
//    print("\n 1/binomial(2k,k)=",b,8);

    t = b;
    t /= k;
    t /= k;
    t /= k;
    if ( !(k&1) )  t.negate();
//    print("\n (-1)^k/binomial(2k,k)/k^3=",t,8);
}
//---------------

int
zeta3(hfloat &z3)
// compute zeta(3) = \sum_{k=0}^{\infty}{1/k^3}
//   as  5/2 * \sum_{k=1}^{\infty}{(-1)^k/(k^3*binomial(2k,k))}
{
    hfloat b(z3.prec());
    hfloat t(z3.prec());
    z3 = 0;
    int k = 0;
    while ( 1 )
    {
        next_zeta3_term(k,b,t);
        z3 += t;
        if ( -t.exp() > (long)z3.prec() )  break;
        ++k;
    }

    z3 /= 2;
    z3 *= 5;

    return k;  // number of terms added
}
//---------------
