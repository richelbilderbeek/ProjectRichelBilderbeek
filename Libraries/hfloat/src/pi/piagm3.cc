
#include <cmath>
#include <fxt/fxtio.h>
#include <fxt/jjassert.h>

#include "hfverbosity.h"
#include "hfloat.h"

#include <fxt/aux0/sign.h>  // Abs()


// herein are two variants of the agm iteration for pi
// fast:
//  pi = 2*a^2/(sqrt(3)*(2*R'-1)-1)
//     = 2*a^2/(sqrt(3)*(1-sum_{k=0}^{\infty}{2^k*c_k^2})-1)
// slow:
//  pi = 6*a^2/(sqrt(3)*(2*R'-1)+1)
//     = 6*a^2/(sqrt(3)*(1-sum_{k=0}^{\infty}{2^k*c_k^2})+1)



int
pi_agm3(hfloat &p, int var/*=4*/)
//
// var:
//  -1: slow 2.order
//  +1: fast 2.order
//  -4: slow 4.order
//  +4: fast 4.order
//
// return number of iterations needed
//
//  accuracy:
//  0 < Pi-Pi_n < s3*Pi^2*2^(n+4)*e^(-s3*Pi*2^(n+1))/AGM^2
//  where
//  for the fast variant s3=sqrt(3)
//  for the slow variant s3=1/sqrt(3)
//  (or about 1/3 of the correct digits at the same step)
//
//  fast variant:
//  steps    correct decimal digits
// --------------------------------
//  0                      2
//  1                      6
//  2                     15
//  3                     34
//  4                     71
//  5                    147
//  6                    298
//  7                    600
//  8                   1205
//  9                   2414
{
    if ( hfverbosity::piname )
    {
        cout << "\n ===== PI_algorithm: " << __FUNCTION__ << "(";

        if ( Abs(var)==4 )  cout << "quartic, ";

        if ( var>0 )  cout << "fast";
        else          cout << "slow";

        cout << " variant)" << endl;
    }

    long n = p.prec();

    int quartq=0;
    long pnp = hfverbosity::pinumprec;

    hfloat a(n);
    hfloat s3(n);

    if ( Abs(var)>1 )  quartq = 1;

    sqrt(3,p);
    s3 = p;

    if ( var>0 )  p += 1;
    else          p -= 1;

    isqrt(2,a);
    mul(p,a,a);
    a /= 2;                  // (sqrt(6)+-sqrt(2))/4


    int k;
    if ( quartq )
    {
	sqrt(a,a);

        // the work is done here:
	k = r_prime_sum_4th(a,p,n,&a);
    }
    else
    {
        // the work is done here:
	k = r_prime_sum(a,p,n,&a,0);
    }
    // here p=1-sum_{k=0}^{\infty}{(2^(n-1)*c_n^2)}
    if ( hfverbosity::pinums )  print("\nr_prime()=\n",a,pnp);

    sqr(a,a);

    if (var>0)  a *= 2;
    else        a *= 6;

    p *= 2;
    p -= 1;
    p *= s3;

    if ( var>0 )  p -= 1;
    else          p += 1;

    div(a,p,p);

    return k;
}
//========================== end PI_AGM3 =======================



