
#include <cmath>
#include <iostream>
#include <fxt/jjassert.h>

#include "hfloat.h"
#include "hfverbosity.h"

void
check(const hfloat &a, const hfloat &b, ulong maxd)
{
    ulong d;
    cmp(a,b,d);
    d = a.prec() - d;
    cout << " the last " << d
         << " LIMBs (of total " << a.prec()
         << ") are incorrect " << endl;
    jjassert( d<=maxd );
}
//---------------

int
test4(long n)
{
    cout<<"\n TEST4: "<< endl;;
    hfverbosity::hush_all();
    hfloat::radix(10);
    hfloat a(n), b(n), c(n);

#define  pp  17
    hfloat d(n), x(n), t(n), v(n), y(n);

    hfverbosity::hush_all();
//    hfverbosity::tell_pi();

    a = 1;
    exp(a, c);
    print("e=\n",c);
    jjassert( approximate(c, exp(1.0)) );

    return 0;
}
//========================= end ==========================
