
#include "hfloat.h"


void
elliptic_K(const hfloat &k, hfloat &K, int pq/*=0*/)
// compute
//   K(k) = pi / (2*agm(1,k'))  [ if pq==0 ]
//  K'(k) = pi / (2*agm(1,k))   [ else ]
{
    if ( 0==pq )  // need complement
    {
        sqr(k, K);
        sub(1, K, K);
        sqrt(K, K);  // == sqrt(1-k*k)
    }
    else
    {
        K = k;
    }

    agm1(K, K);

    const hfloat &pi = constant_pi( K.prec() );
    div(pi, K, K);

    K /= 2;
}
// =================== end ===================
