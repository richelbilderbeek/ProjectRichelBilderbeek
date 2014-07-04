
#include <cmath>
#include <iostream>
#include <fxt/jjassert.h>

#include "hfloat.h"
#include "hfverbosity.h"

static void
check(const hfloat &a, const hfloat &b)
{
    print("a=",a,11);
    print("b=",b,11);
    ulong idx;
    int sgn = cmp(a,b,idx);
    cout << "sgn=" << sgn << "  idx=" << idx << endl;
    sgn = cmp(b,a,idx);
    cout << "-sgn=" << sgn << "  idx=" << idx << endl;
}
//------------------------

int
test0(long n)
{
    cout << "\n TEST0  n=" << n << endl;

    hfverbosity::hush_all();
    hfloat a(n);
    hfloat b(n), c(n), d(n);

    a = 31415;
    b = 31416;
    c = -2;
    check(a,a);
    check(a,b);
    check(a,c);
    check(b,c);

    int rx = 10000;
    hfloat::radix(rx);
    cout << "RADIX=" << rx << endl;

    pi_by_log_rx(n,a);

    print("pi/log(q)=agm(..)=",a);
    jjassert( approximate(a, M_PI/log(rx), 1e-7) );

    pi_4th_order(b);
    print("pi=",b);

    c = rx;  log(c,c);
//    c = constant_logrx(n);
    print("log(q)=",c);

    b /= c;
    print("pi/log(q)=",b);

    a -= b;
    print("diff=",a);

    a = constant_logsqrt2(n);
    jjassert( approximate(a, log(sqrt(2.0))) );

    return 0;
}
//============================ end ===============================
