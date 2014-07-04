
#include "hfloat.h"
#include "hfverbosity.h"

void
print_diff(const hfloat & s,  const hfloat *p, ulong n, ulong n1=0)
{
    if ( (long)n1<0 )  n1 = 0;

    hfloat tt;
    for (ulong k=n1; k<n; ++k)
    {
        tt = s;
        tt -= p[k];
        cout << " k=" << k << ": ";
        print(tt, 5);
//        if ( k>0 )  print((s-p[k-1])/(s-p[k]), 11);
//        cout << endl;
    }
}
//---------------

ulong
delta_squared(hfloat *p, ulong n)
{
    hfloat td1, td2, tt;
    for (ulong k=n-1; k>=2; --k)
    {
        td1 = p[k] - p[k-1];
        tt = p[k-1] - p[k-2];
        td2 = td1 - tt;
//        td2 = p[k] + p[k-2] - 2*p[k-1];
        sqr(td1, td1);
        td1 /= td2;

//        td1 *= 3;  td1 /= 2;

        p[k] -= td1;
    }

    n -= 2;  // two less
    for (ulong k=0; k<n; ++k)  p[k] = p[k+2];

    return n;
}
//---------------


int
main()
{
    const int prec = 1024;
    hfloat::default_prec(prec);
    hfverbosity::hush_all();

    hfloat s;  s = constant_pi(s.prec());

    ulong n = 30;
    hfloat p[n];

    // fill in partial sums (log convergence):
    sum_partial(gregory_term, p, n);
    for (ulong k=0; k<n; ++k)  p[k] *= 4;

    cout << "---- partial sums:" << endl;
    print_diff(s, p, n);


    // fill in sumalt-massaged partial sums (linear convergence):
    hfloat tt;
    for (ulong k=n; k>0; --k)
    {
        sumalt_partial(p, tt, k);
        p[k-1] = tt;
    }

    cout << "---- after sumalt:" << endl;
    print_diff(s, p, n);

    // FAKE geometric convergence:
//    for (ulong k=0; k<n; ++k)
//    {
//        p[k] = 1;
//        mul2pow(p[k], -k, p[k]);
//        if (k&1) p[k].negate();
//        p[k] += s;
//    }
//    cout << "---- FAKE:" << endl;
//    print_diff(s, p, n);


    // apply delta square (quadratic convergence):
    ulong dct = 0;
    while ( n>=2 )
    {
        n = delta_squared(p, n);
        ++dct;
        cout << "---- after " << dct << ". delta squared:" << endl;
        print_diff(s, p, n, n-5);
//        if ( dct==3 )  break;
    }

    cout << endl;
    return 0;
}
//---------------
