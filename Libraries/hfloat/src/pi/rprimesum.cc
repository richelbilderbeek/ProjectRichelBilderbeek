
#include <cmath>
#include <fxt/fxtio.h>

#include <fxt/jjassert.h>
#include "hfloat.h"
#include "hfverbosity.h"

#define  VARIANT  0  // (0 or 1) chooses variant of computation

//#if  ( VARIANT==0 )
//#warning 'FYI: r_prime_sum() uses VARIANT 0'
//#else  // VARIANT
//#warning 'FYI: r_prime_sum() uses VARIANT 1'
//#endif


int
r_prime_sum(const hfloat &b0, hfloat &x, ulong n,
            hfloat *m/*=0*/, int sum0q/*=0*/)
//
// compute 1-sum_{k=0}^{\infty}{(2^(n-1)*c_n^2)}
// for the agm iteration starting with 1 and b0
//
// if (sum0q) then sum_0 is expected in x (on input)
//
// c_{n+1} := (a_n-b_n)/2
// c_0 = a_0^2-1
//
// result in x
// optional: agm in *m
//
// returns  number of iterations needed
//
{
    int vq = hfverbosity::pinums;      // if !=0 print several quantities:
    ulong ppr = (int)hfverbosity::pinumprec;  // how many LIMBs are printed

    if ( m )  jjassert( (*m).data() != x.data() );

    hfloat b(n), sum(n), t(n);
    b = b0;    // B_0= (given as arg)
    if ( vq )  print("\nB_0=", b, ppr);

    // SUM_0 = (1-b^2)/2:
    if ( sum0q )
    {
        sum = x;
        if ( vq )  print("\nS_0(given)=", sum, ppr);
    }
    else
    {
        sqr(b, t);
        sub(1, t, sum);
        sum /= 2;          // sum_0 = (1-b*b)/2 = 2^(-1) * c_0^2
        if ( vq )  print("\nS_0=", sum, ppr);
    }


    x = 1;    // A_0 = 1
    long prec;
    int k;
    for (k=1;  ; ++k)
    {
        if ( vq )  cout << "\n ----- step " << k << ": ----- " << endl;
        jjassert( k < 99 ); // "r_prime_sum(): no convergence"

#if  ( VARIANT==0 )
        add(x, b, t);                      // a+b
        if ( k != 1 )  b *= x;           // avoid mult by 1   // MUL
        div2(t, x);                       // new a:= (a+b)/2
        if ( vq )  print("\nA_k=", x, ppr);

        sqr(x, t);                        // a^2               // SQR
        t -= b;                          // c^2:=a^2-b^2
        if ( vq )  print("\nC_k^2=", t, ppr);

        mul2pow(t, k-1, t);                // 2^(k-1)*(c_k)^2
        if ( vq )  print("\nADD_k=", t, ppr);
        prec = -2*t.exp();
        if ( vq )  cout << "\n precision=" << prec << endl;

        sum += t;                         // sum_k=sum_{k-1} + 2^(k-1)*(c_k)^2
        if ( vq )  print("\nSUM_k=", sum, ppr);

        t = b;  sqrt(t, b);                // new b=sqrt(a*b)   // SQRT
        if ( vq )  print("\nB_k=", b, ppr);

        if ( (prec>=(long)n) || t.is_zero() )  goto done;  // ? next c^2 will be zero
#else  // VARIANT
        sub(x, b, t);
        t /= 2;            // new c=(a-b)/2
        sqr(t, t);         // c^2                    // SQR

        add(x, b, x);
        x /= 2;            // new a = (a+b)/2
        if ( vq )  print("\nA_k=", x, ppr);
        if ( vq )  print("\nC_k^2=", t, ppr);

        mul2pow(t, k-1, t);  // 2^(k-1)*c^2
        if ( vq )  print("\nADD_k=", t, ppr);
        prec = -2*t.exp();
        if ( vq )  cout << "\n precision=" << prec << endl;

        sum += t;          // sum_k=sum_{k-1} + 2^(k-1)*(c_k)^2
        if ( vq )  print("\nSUM_k=", sum, ppr);
        div2pow(t, k-1, t);  // restore c^2
//            print("\nDEBUG c^2=\n",t,ppr);

        sqr(x, b);          // a^2                    // SQR
        //  print("\nDEBUG a^2=\n",b,ppr);
        sub(b, t, t);        // b^2 = a^2-c^2  (CANCELLATION !)
        //  print("\nDEBUG a^2-c^2=\n",t,ppr); //

        sqrt(t, b);                // new b=sqrt(a*b)   // SQRT
        if ( vq )  print("\nB_k=", b, ppr);

        if ( prec>=(long)n )  goto done;  // ? next c^2 will be zero
#endif  // VARIANT
    }
 done:

    if ( m!=NULL )  // AGM
    {
        add(x, b, t);  // a+b
        div2(t, *m);  // m=(a+b)/2  (AGM)
    }

    sub(1, sum, x);    // x = 1-sum
//    print("\nDEBUG sum =\n",sum,ppr);

    return k;
}
// ========================== end ==========================
