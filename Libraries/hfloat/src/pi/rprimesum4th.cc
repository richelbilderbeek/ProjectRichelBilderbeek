
#include <cmath>
#include <fxt/fxtio.h>

#include <fxt/jjassert.h>
#include "hfloat.h"
#include "hfverbosity.h"

#define  VARIANT  0  // (0 or 1) chooses variant of computation

//#if  ( VARIANT==0 )
//#warning 'FYI: r_prime_sum_4th() uses VARIANT 0'
//#else  // VARIANT
//#warning 'FYI: r_prime_sum_4th() uses VARIANT 1'
//#endif


int
r_prime_sum_4th(const hfloat &b0, hfloat &x, ulong n,
                hfloat *m/*=NULL*/)
//
// compute 1-sum_{k=0}^{\infty}{(2^(n-1)*c_n^2)}
// with c_{n+1}:=(a_n-b_n)/2
// as 1-sum_{k=0}^{\infty}{(4^(n)*(sa_n^4-((sa_n^2+sb_n^2)/2)^2))}
//
// for the quartic agm iteration starting with 1 and b0:=sqrt(b)
//
// result in x
// optional: agm in *m
//
// returns number of iterations needed
//
{
    int vq = hfverbosity::pinums;      // if !=0 print several quantities:
    ulong ppr = hfverbosity::pinumprec;  // how many LIMBs are printed

    if ( m )  jjassert( (*m).data()!=x.data() );

    long prec;
    hfloat b(n), sum(n);
    hfloat t(n);
    hfloat u(n),s(n);
#if  ( VARIANT==0 )
    hfloat v(n);  // not needed with variant != 0
#endif

    b = b0;    // B_0= (given as arg)

    sqr(b,t);         // b_0^2
    t += 1;           // b_0^2+1
    div2(t,u);        // u_0= (b^2+1)/2 =(a_0^2+b_0^2)/2
    sqr(u,t);         // ((b_0^2+1)/2)^2
    sub(1,t,sum);     // sum_0 = 1 - ((b_0^2+1)/2)^2
    if ( vq )  print("\n sum_0:\n",sum,ppr);

    x = 1;     // a_0=1
    int k;
    for (k=1;  ; ++k)
    {
 	if ( vq )  cout << "\n ----- step " << k << ": ----- " << endl;
        jjassert( k < 99 ); // "r_prime_sum_4th(): no convergence"

#if  ( VARIANT==0 )
        add(x,b,t);                    // a+b
        b *= u;                        // b*(a^2+b^2)/2           // MUL
        if ( k!=1 )  b *= x;           // (avoid mult by 1)       // MUL
        root(b,4,b);                   // (a*b*(a^2+b^2)/2)^(1/4) // ROOT4
        if ( vq )  print("\nB_k=\n",b,ppr); // next b = (a*b*(a^2+b^2)/2)^(1/4)

        div2(t,x);
        if ( vq )  print("\nA_k=\n",x,ppr); // next a = (a+b)/2

        sqr(x,v);                      // a^2                      // SQR
        sqr(b,u);                      // b^2                      // SQR
        u += v;                        // a^2+b^2
        u /= 2;                        // u = (a^2+b^2)/2

        sqr(u,t);                      // t = ((a^2+b^2)/2)^2      // SQR
        sqr(v,s);                      // a^4                      // SQR

        s -= t;                        // s = a^4-((a^2+b^2)/2)^2
        mul2pow(s,2*k,s);              // 4^k*(...)
        if ( vq )  print("\nADD_k=\n",s,ppr);

        sum += s;                      // sum+=4^k*(...)

        prec = -4*s.exp();
        if ( vq )  cout << "\n precision=" << prec << endl;
        if ( (prec>=(long)n) || s.is_zero() )  goto done;  // ? next summand will be zero
#else  // VARIANT
        sub(x,b,t);
        div2(t,t);                     // next c = (a-b)/2
        if ( vq )  print("\nC_k=\n",t,ppr);
        sqr(t,t);                      // c^2                      // SQR

        add(x,b,x);
        div2(x,x);                     // next a = (a+b)/2
        if ( vq )  print("\nA_k=\n",x,ppr);

        sqr(x,u);                      // a^2                      // SQR

        if ( k!=1 )
        {
#define  v  b  // save a variable
            //            if ( vq )  print("\n(last a)^4=\n",s,ppr);
            add(u,t,v);                // a^2+c^2
            sqr(v,v);                  // (a^2+c^2)^2              // SQR
            //            if ( vq )  print("\n(a^2+c^2)^2=\n",v,ppr);
            sub(s,v,s);                // al^4 - (a^2+c^2)^2  (al := last a)
            //            if ( vq )  print("\n(last a)^4 - (a^2+c^2)^2=\n",s,ppr);
            mul2pow(s,2*(k-1),s);      // 4^k*(...)
            if ( vq )  print("\nADD_k=\n",s,ppr);
            sum += s;
#undef  v
        }

        sqr(t,t);                      // c^4                      // SQR
        prec = -t.exp();
        if ( vq )  print("\nC_k^4=\n",t,ppr);

        sqr(u,s);                      // a^4                      // SQR

        sub(s,t,t);                    // a^4 - c^4
//        root(t,4,b);                   // (a^4-c^4)^(1/4)          // ROOT4
        root_x(t,4,b);                   // (a^4-c^4)^(1/4)          // ROOT4
        if ( vq )  print("\nB_k=\n",b,ppr); // next b = (a^4-c^4)^(1/4)

        if ( prec>=(long)n )  goto done;  // ? next summand will be zero
#endif   // VARIANT
    }
 done:

    if ( m!=NULL )
    {
        add(x,b,t);
	div2(t,*m);
        sqr(*m,*m);  // m = AGM
    }

    sub(1,sum,x);    // x = 1-sum

    return k;
}
// ================================= end ==========================
