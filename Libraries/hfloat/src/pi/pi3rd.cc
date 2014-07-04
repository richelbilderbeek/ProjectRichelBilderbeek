
#include <cmath>
#include <fxt/fxtio.h>

#include "hfloat.h"
#include "hfverbosity.h"
#include <fxt/sort/minmaxmed23.h>  // min2(), max2()

// jjnote: semi ugly: heuristics
#define LOG_PREC(k)   max2(0.0, (-3.0*(double)s.exp()*log(drx)))

#define LIMB_PREC(k)  (long)floor(LOG_PREC(k)/log(drx))  // precision in LIMBS


int pi_3rd_order(hfloat &p)
//
// cubic iteration for pi:
// p_0 = 1/3
// s_0 = (sqrt(3)-1)/2
// r_{k+1} = 3/(1+2*(1-s_k^3)^(1/3))
// s_{k+1} = (r_{k+1}-1)/2
// p_{k+1} = r_{k+1}^2*p_k - 3^k*(r_{k+1}^2-1)
//
// returns number of iterations needed
//
{
    if ( hfverbosity::piname )
        cout << "\n ===== PI_algorithm: " << __FUNCTION__ << "() ===== " << endl;

    long n = p.prec();

    long pnp = hfverbosity::pinumprec;
    long prec;
    double drx;
    hfloat r(n), s(n);

    drx = (double)p.radix();

    p = 1;
    p /= 3;                               // p_0=1/3

    isqrt(3,s);
    s *= 3;
    s -= 1;
    s /= 2;                               // s_0=(sqrt(3)-1)/2
    if ( hfverbosity::pinums )  print("\nS_0=\n",s,pnp);

    int k;
    for(k=1;  ; ++k)
    {
        if ( hfverbosity::pistep )
            cout << "\n ----- step " << k << ": ----- " << endl;

	// R_k:
	pow(s,3,r);
	sub(1,r,r);
	cbrt(r,r);                        // (1-s^3)^(1/3)

	r *= 2;
	add(r,(ulong)1,r);
	inv(r,r);
	r *= 3;                           // r=3/(1+2*(1-s^3)^(1/3))
        if ( hfverbosity::pinums )  print("\nR_k=\n",r,pnp);

        sqr(r,s);                         // s used as temp
	p *= s;                           // p*r^2

	s -= 1;
        mulpow(s,3,k-1,s);                // 3^(k-1)*(r^2-1)

	sub(p,s,p);                       // p=p*r^2-3^(k-1)*(r^2-1)
        if ( hfverbosity::pinums )  print("\nP_k=\n",p,pnp);

	sub(r,(ulong)1,s);
	s /= 2;                           // s=(r-1)/2
        if ( hfverbosity::pinums )  print("\nS_k=\n",s,pnp);

	prec =  LIMB_PREC(k);
        if ( hfverbosity::piprec )  cout << "\n precision=" << prec << endl;
	if( prec>=n )  break;
    }

    inv(p,p);         // ! pi !

    return k;
}
//========================== end PI_3RD_ORDER ==========================

