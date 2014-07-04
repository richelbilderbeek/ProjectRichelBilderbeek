
#include <cmath>
#include <fxt/fxtio.h>
#include <fxt/jjassert.h>

#include "hfloat.h"
#include "hfverbosity.h"



int
pi_5th_order(hfloat &p)
//
// quintic iteration for pi
//
{
    if ( hfverbosity::piname )
        cout << "\n ===== PI_algorithm: " << __FUNCTION__ << "() ===== " << endl;

    long n = p.prec();

    long prec;
    long pnp = hfverbosity::pinumprec;
    hfloat s(n), x(n), y(n), z(n), a(n), t(n);

    sqrt(5,s);
    s -= 2;
    s *= 5;
    // s = 5*(sqrt(5)-2);
    if ( hfverbosity::pinums )  print("\nS_0=\n",s,pnp);

    a = 1;
    a /= 2;
    if ( hfverbosity::pinums )  print("\nA_0=\n",a,pnp);

    int k;
    long p5 = 1;
    for (k=1;  ; ++k)
    {
        if ( hfverbosity::pistep )
            cout << "\n ----- step " << k << ": ----- " << endl;

        // === A:  // a_1 = 0.31831553048893283332601569946
        if ( k!=1 )  p5 *= 5;
#define  t2  x
        sqr(s, t);
        t2 = s;
        t2 *= -2;
        t2 += 5;
        t2 += t;
        t2 *= s;
        sqrt(t2,t2);
        a *= t;
        t -= 5;
        t /= 2;
        t += t2;
        t *= p5;
        a -= t;
        // a = sqr(s)*a-p5*((sqr(s)-5)/2+sqrt(s*(sqr(s)-2*s+5)));
        if ( hfverbosity::pinums )  print("\nA_k=\n",a,pnp);

        prec = 2 * cmp1(s);
        if ( hfverbosity::piprec )  cout << "\n precision=" << prec << endl;
        if( prec>=n )  break;

        // === X:  // x_1 =  3.236067977499789696409173668731276
        x = 5;
        x /= s;
        x -= 1;
        // x = 5/s-1;
        if ( hfverbosity::pinums )  print("\nX_k=\n",x,pnp);

        // === Y:  // y_1 = 12
        y = x;
        y -= 1;
        sqr(y, y);
        y += 7;
        // y = sqr(x-1)+7;
        if ( hfverbosity::pinums )  print("\nY_k=\n",y,pnp);

        // === Z:  // z_1 = 1.890038899781125961869812624
        sqr(y, t);
        pow(x, 3, z);
        z *= 4;
        t -= z;
        sqrt(t, z);
        z += y;
        z *= x;
        div2(z, t);
        root(t, 5, z);
        // z = root(x*(y+sqrt(sqr(y)-4*pow(x,3)))/2,5);
        if ( hfverbosity::pinums )  print("\nZ_k=\n",z,pnp);

        // === S:  // s_1 = 1.0000006028070010000685772650633552
        t = x;
        t /= z;
        t += z;
        t += 1;
        sqr(t, t);
        s *= t;
        t = 25;
        div(t, s, s);
        // s = 25/(s*sqr(z+x/z+1));
        if ( hfverbosity::pinums )  print("\nS_k=\n",s,pnp);
    }

    inv(a, p);         // ! pi !

    return k;
}
//========================== end PI_5TH_ORDER ==========================
