
#include "hfloat.h"


void
elliptic_E(const hfloat &k, hfloat &E, int pq/*=0*/)
// compute
//   E(k) = E(k) * R(k)     [ if pq==0 ]
//  E'(k) = E'(k) * R'(k)   [ else ]
{
    elliptic_K(k, E, pq);
    hfloat R( E.prec() );

    if ( 0==pq )  // need complement
    {
        sqr(k, R);
        sub(1, R, R);
        sqrt(R, R);  // == sqrt(1-k*k)
    }
    else
    {
        R = k;
    }

    r_prime_sum(R, R, R.prec());
    E *= R;
}
// =================== end ===================
