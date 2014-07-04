
#include <cmath>
#include <fxt/fxtio.h>

#include "hfloat.h"
#include "hfverbosity.h"



// see borwein^2 p.170:
#define LOG_PREC_R(k,r)  -(log(16.0*sqrt(r))+k*log(2.0)-pow(2.0,k)*sqrt(r)*M_PI)
#define LOG_PREC(k)  LOG_PREC_R((double)(k), 1.0 )

#define LIMB_PREC(k)  (long)floor(LOG_PREC(k)/log(drx))  // precision in LIMBS


int
pi_2nd_order(hfloat &p)
//
// quadratic iteration for pi
//
// return number of iterations needed
{
    if ( hfverbosity::piname )
        cout << "\n ===== PI_algorithm: " << __FUNCTION__ << "() ===== " << endl;

    long n = p.prec();

    long pnp = hfverbosity::pinumprec;
    double drx;
    hfloat y(n), a(n), z(n);

    drx=(double)a.radix();

    isqrt(2,y);                    // y_0 = 1/sqrt(2)
    a = 1;
    a /= 2;                        // a_0 = 1/2

    int k;
    for(k=1;  ; ++k)
    {
        if ( hfverbosity::pistep )
            cout << "\n ----- step " << k << ": ----- " << endl;

        long prec = LIMB_PREC(k);

        // Y_k:
        sqr(y,y);                        // y^2
        sub(1,y,y);                      // (1-y^2)

//        z = 1;
        isqrt(y,z);                      // (1-y^2)^(-1/2)  --> 1.0+
        if ( hfverbosity::pimorenums )
        {
            print("\n (1-y^2)^(-1/2)=\n",z,pnp);
            cout << "cmp1(~)=" << cmp1(z) << endl;
        }

        sub(z,(ulong)1,y);               // (1-y^2)^(-1/2)-1
        add(y,(ulong)2,p);               // (1-y^2)^(-1/2)+1
        inv(p,z);                        // 1/(y^(-1/2)+1) --> 0.5-
        if ( hfverbosity::pimorenums )
        {
            print("\n 1/(y^(-1/2+1)=\n",z,pnp);
            cout << "cmp1(~)=" << cmp1(z) << endl;
        }

        y *= z;                          // new y=(y^(-1/2)-1)/(y^(-1/2)+1) --> 0.0+
        if ( hfverbosity::pinums )
        {
            print("\nY_k=\n",y,pnp);
            cout << "cmp1(Y_k)=" << cmp1(y) << endl;
        }

        // A_k:
        add(y,(ulong)1,p);                // y+1
        sqr(p,p);                         // (y+1)^2
        mul(p,a,a);                       // a*(y+1)^2

        mul2pow(y,(k-1)+1,z);             // y*2^(2*(k-1)+3)

        a -= z;                           // new a=a*(y+1)^2-2^(k+1)*y
        if ( hfverbosity::pinums )  print("\nA_k=\n",a,pnp);
        if ( hfverbosity::piprec )  cout << "\n precision=" << prec << endl;
        if( prec>=n )  break;
    }

    inv(a,p);         // ! pi !

    return k;
}
//========================== end PI_2ND_ORDER ==========================

