
#include <cmath>
#include <fxt/fxtio.h>

#include "hfloat.h"
#include "hfverbosity.h"
#include <fxt/sort/minmaxmed23.h>  // min2(), max2()


// jjnote: semi ugly: heuristics
#define LIMB_PREC(k)  (long)max2(0.0,(-9.0*x1m))  // gives precision in LIMBS

//#define LOG_PREC(k)   (LIMB_PREC(k)/log(drx))
//
//#define DEC_PREC(k)   floor(LOG_PREC(k)/log(10.))  // gives precision in decimal digits
//#define BYTE_PREC(k)  floor(LOG_PREC(k)/log(255.)) // gives binary precision in bytes


//
// 9th order iteration for pi:
//
// p_0 = 1/3
// r_0 = (sqrt(3)-1)/2
// s_0 = (1-r_0^3)^(1/3)
//
// t  = 1+2*r_k
// u  = ( 9*r_k* (1+r_k+r_k^2) )^(1/3)
// v  = t^2 + t*u + u^2
// m  = (27*(1+s_k+s_k^2))/(v)
// p_{k+1}  = m*p_k + 3^(2*k-1)*(1-m)
// s_{k+1}  = ((1-r_k)^3)/((t+2*u)*v)
// r_{k+1}  = (1-s_k^3)^(1/3)
//


int
pi_9th_order(hfloat &p)
//
// nonic iteration for pi
//
// return number of iterations needed
{
    if ( hfverbosity::piname )
        cout << "\n ===== PI_algorithm: " << __FUNCTION__ << "() ===== " << endl;

    long n = p.prec();

    long prec;
    long pnp = hfverbosity::pinumprec;
    double x1m = 0.0;  // exponent of m-1
    hfloat r(n), s(n);
    hfloat t(n), u(n), v(n), m(n);
    hfloat x(n);

    p = 1;
    p /= 3;                        // p_0=1/3

    sqrt(3,r);
    r -= 1;
    r /= 2;                        // r_0=(sqrt(3)-1)/2
    if ( hfverbosity::pinums )  print("\nR_0=\n",r,pnp);

    pow(r,3,s);
    sub(1,s,s);
    cbrt(s,s);                     // (1-r^3)^(1/3)
    if ( hfverbosity::pinums )  print("\nS_0=\n",s,pnp);

    int k;
    for (k=1; ; ++k)
    {
        if ( hfverbosity::pistep )
            cout << "\n ----- step " << k << ": ----- " << endl;

	add(r,(ulong)1,t);             // 1+r

	sqr(r,u);                      // r^2
	add(u,t,u);                    // (1+r+r^2)
	mul(u,r,u);                    // r*(1+r+r^2)
	mul(u,(ulong)9,u);             // 9*r*(1+r+r^2)
	cbrt(u,u);                     // u = (9*r*(1+r+r^2))^(1/3)
        if ( hfverbosity::pinums )  print("\nU_k=\n",u,pnp);

	add(t,r,t);                    // t = 1+2*r
        if ( hfverbosity::pinums )  print("\nT_k=\n",t,pnp);

	sqr(t,m);                      // t^2
	add(t,u,v);                    // t+u
	mul(u,v,v);                    // t*u+u^2
	add(m,v,v);                    // v = t^2+t*u+u^2
        if ( hfverbosity::pinums )  print("\nV_k=\n",v,pnp);

	inv(v,v);                      // 1/(t^2+t*u+u^2)

	sqr(s,m);                      // s^2
	add(m,s,m);                    // s+s^2
	add(m,(ulong)1,m);             // 1+s+s^2
	mul(m,(ulong)27,m);            // 27*(1+s+s^2)
	mul(m,v,m);                    // 27*(1+s+s^2)/v
        if ( hfverbosity::pinums )  print("\nM_k=\n",m,pnp);

	mul(p,m,p);                    // p*m
	sub(1,m,m);                    // 1-m

	x1m = (double)m.exp();

	mulpow(m,3,2*(k-1)-1,m);        // 3^(2*(k-1)-1)*(1-m):
	add(p,m,p);                     // p = p*m + 3^(2*(k-1)-1)*(1-m)
        if ( hfverbosity::pinums )  print("\nP_k=\n",p,pnp);

	prec = LIMB_PREC(k);         // precision
        if ( hfverbosity::piprec )
            cout << "\n precision=" << prec << endl;
	if ( prec>=n )  break;

	sub(1,r,s);                    // 1-r
	pow(s,3,s);                    // (1-r)^3
	mul(s,v,s);                    // (1-r)^3/v
	mul(u,(ulong)2,v);             // 2*u
	add(v,t,v);                    // t+2*u
	inv(v,v);                      // 1/(t+2*u)
	mul(s,v,s);                    // s = (1-r)^3/((t+2*u)*v)
        if ( hfverbosity::pinums )  print("\nS_k=\n",s,pnp);

	pow(s,3,r);                    // s^3
	sub(1,r,r);                    // 1-s^3
	cbrt(r,r);                     // r = (1-s^3)^(1/3)
        if ( hfverbosity::pinums )  print("\nR_k=\n",r,pnp);
    }

    inv(p,p);         // ! pi !

    return k;
}
//========================== end PI_9TH_ORDER ==========================

