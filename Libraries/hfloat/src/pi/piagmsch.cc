
#include <fxt/fxtio.h>

#include "hfloat.h"
#include "hfverbosity.h"


#define  SAVE_FIRST_STEP  1  // 0 or 1 (default)

//#if  ( SAVE_FIRST_STEP!=0 )
//#warning 'FYI: SAVE_FIRST_STEP is set in pi_agm_sch()'
//#else
//#warning 'FYI: SAVE_FIRST_STEP is NOT set in pi_agm_sch()'
//#endif

int
pi_agm_sch(hfloat &A)
{
    if ( hfverbosity::piname )
        cout << "\n ===== PI_algorithm: " << __FUNCTION__ << "() ===== " << endl;

    long pnp = hfverbosity::pinumprec;

    long n = A.prec();
    hfloat a(n), B(n), t(n), S(n);
#define  b  B  // save variable

#if  ( SAVE_FIRST_STEP!=0 )
    isqrt(2, B);          // B = sqrt(1/2)
    div2(B, A);           // sqrt(1/2)/2
    t = A;
    a = 1;  a /= 2;       // 1/2
    add(a, A, a);         // a = sqrt(1/2)/2 + 1/2
    S = 1;  S /= 8;       // 1/8
    sub(t, S, t);         // t = sqrt(1/2)/2 - 1/8
    mul(S, (ulong)3, S);  // 3/8
    add(A, S, A);         // A = sqrt(1/2)/2 + 3/8
    mul2(t, t);           // t = sqrt(1/2) - 1/4
#else  // SAVE_FIRST_STEP
    a = 1;
    A = 1;  // == a^2
    B = 1;  B /= 2;
    t = 1;  t /= 2;
#endif  // SAVE_FIRST_STEP

    long lastprec = 0;
    int k;
#if  ( SAVE_FIRST_STEP!=0 )
    for (k=1;  ; ++k)
#else
    for (k=0;  ; ++k)
#endif
    {
        if ( hfverbosity::pistep )
            cout << "\n ----- step " << k << ": ----- " << endl;

        add(A, B, S);
        div(S, (ulong)4, S);  // S = (A+B)/4
        if ( hfverbosity::pimorenums )  print("\nS_k=\n",S,pnp);

        sqrt(B, b);           // b = sqrt(B)
        if ( hfverbosity::pinums )  print("\nB_k=\n",b,pnp);

        add(a, b, a);
        div2(a,a);            // a' = (a+b)/2
        if ( hfverbosity::pinums )  print("\nA_k=\n",a,pnp);

        sqr(a, A);            // A = a'^2
        if ( hfverbosity::pimorenums )  print("\nA_k^2=\n",A,pnp);

        sub(A, S, B);
        mul2(B, B);           // B' = 2*(A-S)
        if ( hfverbosity::pimorenums )  print("\nB_k^2=\n",b,pnp);

        sub(A, B, S);
        if ( hfverbosity::pimorenums )  print("\nC_k^2=\n",S,pnp);

        mul2pow(S, k+1, S);   // 2^(k+1) * (A-B)
        if ( hfverbosity::pinums )  print("\nADD_k=\n",S,pnp);
        sub(t, S, t);         // t -= 2^(k+1)*(A-B)


        if ( lastprec>=n/2 )  break;

        lastprec = -S.exp();
    }

    sqr(a, a);
    mul2(a,a);
    div(a, t, A);  // pi = 2*a*a/t

    return k;
}
//======================= end =======================
