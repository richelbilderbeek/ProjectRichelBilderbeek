
#include <cmath>
#include <fxt/fxtio.h>
#include <fxt/jjassert.h>

#include "hfverbosity.h"
#include "hfloat.h"


int
pi_cubic_agm(hfloat &p)
// return number of iterations needed
{
    if ( hfverbosity::piname )
        cout << "\n ===== PI_algorithm: " << __FUNCTION__ << "() ===== " << endl;

    long n = p.prec();

    long prec;
    long pnp = hfverbosity::pinumprec;
    hfloat a(n), b(n), r(n), t(n), c(n);

    a = 1;   // a_0 = 1

    b = 3;
    isqrt(b,b);
    b *= 3;
    b -= 1;
    b /= 2;  // b_0 = (sqrt(3)-1)/2

    r = 1;

    int k;
    for (k=0;  ; ++k)
    {
        if ( hfverbosity::pistep )
            cout << "\n ----- step " << k << ": ----- " << endl;

	c = a;
	sqr(c,c);  // a^2

	// A_k:
	p = b;
        p *= 2;
        p += a;
	p /= 3;    // (a+2*b)/2
        if ( hfverbosity::pinums )  print("\nA_k=\n",a,pnp);

	// B_k:
	t = a;
	t += b;    // a+b
	t *= b;    // b*(a+b)
	t += c;    // a^2+a*b+b^2
	b *= t;    // b*(a^2+a*b+b^2)
        b /= 3;    // b*(a^2+a*b+b^2)/3
	cbrt(b,b); // (b*(a^2+a*b+b^2)/3)^(1/3)
        if ( hfverbosity::pinums )  print("\nB_k=\n",b,pnp);

	a = p;

	// C_k:
	t = a;
	sqr(t,t);  // a_{k+1}^2
	c -= t;    // a_k^2 - a_{k+1}^2
        if ( hfverbosity::pinums )  print("\nC_k=\n",c,pnp);

	mulpow(c,3,k,c);  // 3^{k+1}*(a_k^2 - a_{k+1}^2)

	// R_k:
	r -= c;    // 1 - sum_{k=0}^{\infty}{  3^{k+1}*(a_k^2 - a_{k+1}^2) }
        if ( hfverbosity::pinums )  print("\nR_k=\n",r,pnp);

        //       	if ( c.exp() < -n/2 )  break;
	prec = -2*c.exp();
        if ( hfverbosity::piprec )  cout << "\n precision=" << prec << endl;
	if( prec>=n )  break;
    }


    sqr(a,a);
    mul(a,(ulong)3,a);   // 3*a_{n+1}^2

    div(a,r,p);   // pi = 3*a_{n+1}^2 / (1-sum{...})

    return k;
}
//================= end PI_CUBIC_AGM =======================


