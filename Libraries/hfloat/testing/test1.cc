
#include <iostream>
#include <fxt/jjassert.h>

#include "hfloat.h"

int
test1(long n)
{
//    hfloat::radix(1000);
    hfloat a(n), b(n), c(n), d(n);

    cout<<"\n TEST1 "<<flush;

    for (long k=-80; k<80; ++k)
    {
        mul2pow(a,k,b);

        c = a;
        if ( k>=0 )  for (long j=0; j<k; ++j)  mul2(c,c);
        else         for (long j=0; j<k; ++j)  div2(c,c);

        d = b - c;
        cout<<"k="<<k;  print("  diff=", d, 5);
        jjassert( d.is_zero() );
    }
    cout<<endl;

//    a = 33;
//    for (long k=0; k<10; ++k)  a *= a;
//    cout << "a=" << a << endl;
//    sqrt(a, b);
//    cout << "b=" << b << endl;
//    b *= b;
//    a -= b;
//    cout << "err=" << a << endl;
//    abort();

    return 0;
}
//========================= end ==========================

