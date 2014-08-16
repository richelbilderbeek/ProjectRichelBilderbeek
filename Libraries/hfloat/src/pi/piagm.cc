
#include <cmath>
#include <fxt/fxtio.h>
#include <fxt/jjassert.h>

#include "hfloat.h"
#include "hfverbosity.h"


int
pi_agm(hfloat &p, int quartq/*=0*/)
//
// quartq!=0 --> quartic variant
//
// return number of iterations needed
{
    if ( hfverbosity::piname )
    {
        cout << "\n ===== PI_algorithm: " << __FUNCTION__  << "(";
        if ( quartq )  cout << "quartic";
        cout << ")" << endl;
    }

    long n = p.prec();
    long pnp = hfverbosity::pinumprec;
    hfloat a(n);

    int k;
    if( quartq )
    {
	iroot(2,4,a);                   // 1/sqrt(sqrt(2))
	k = r_prime_sum_4th(a, p, n, &a);  // the work is done here
    }
    else
    {
	isqrt(2,a);                    // 1/sqrt(2)
	p = 1;
	p /= 4;  // sum_0=1/4
	k = r_prime_sum(a, p, n, &a, 1);   // the work is done here
    }
    // here p=1-sum_{k=0}^{\infty}{(2^(n-1)*c_n^2)}
    if ( hfverbosity::pinums )  print("\nr_prime()=\n",a,pnp);

    p *= 2;  // p=2-sum_{k=0}^{\infty}{(2^n*c_n^2)}
    p -= 1;  // p=1-sum_{k=0}^{\infty}{(2^n*c_n^2)}

    sqr(a,a);
    a *= 2;          // a=2*a^2

    div(a,p,p);     // p=2*a^2/(1-sum_{k=0}^{\infty}{(2^n*c_n^2)})

    return k;
}
//========================== end =======================




// pi = 2*a^2/(2*R'-1)
//    = 2*a^2/(1-sum_{k=0}^{\infty}{2^k*c_k^2}

//  0 < Pi-Pi_n < Pi^2*2^(n+4)*e^(-Pi*2^(n+1))/AGM^2
//
//  steps    correct decimal digits (DEC_PREC(k))
// ------------------------------------------
//  0                      1
//  1                      2
//  2                      5
//  3                     10
//  4                     20
//  5                     42
//  6                     85
//  7                    172
//  8                    347
//  9                    696
// 10                   1394
// 11                   2791
// 12                   5585
// 13                  11173
// 14                  22349
// 15                  44703
// 16                  89411
// 17                 178826
// 18                 357657
// 19                 715320
// 20                1430646
// 21                2861298
// 22                5722602
// 23               11445211

