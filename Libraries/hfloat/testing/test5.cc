//
// was: simple example 8: 
// bogo lucas lehmer test:
// p=2^q-1 prime <== cosh(2^(q-2)*log(2+sqrt(3)))%p=0


#include "hfloat.h"
#include "hfverbosity.h"

#include <fxt/jjassert.h>
#include <iostream>
#include <cmath>

/*
void
LL(ulong q, hfloat &x)
{
    x = 4;
    for (ulong k=0; k<q-2; ++k)
    {
        sqr(x,x);
        x -= 2;
    }

    x /= 2;
}
//---------------
*/

void
LL(ulong q, hfloat &x)
{
    x = 2;
    for (ulong k=0; k<q-2; ++k)
    {
        sqr(x,x);
        x *= 2;
        x -= 1;
    }   
}
//---------------



int
test5(long n)
{
    ulong  q = 13;  // test 2**q-1,  try 13 (prime) and 14 (not prime)
    // 2,3,5,7,13,17,19,31,61,89,107,127,521,607

    hfverbosity::hush_all();
//    hfverbosity::pinums = 1;
//    hfverbosity::meannums = 1;

    // precision in LIMBs, use o power of two:
    hfloat::default_prec(n);

    // radix, use 10000 (decimal) or 65536 (hex numbers):
    hfloat::radix(10000);

    hfloat a, b, c, m;

    double d = 0;
    a = constant_sqrt2(n);
    print("const_sqrt2=\n",a,15);
    jjassert( approximate(a,sqrt(2.0)) );

    a = constant_pi(n);
    print("const_pi=\n",a,15);
    jjassert( approximate(a,M_PI) );

    a = constant_logrx(n);
    print("const_logrx=\n",a,15);
    jjassert( approximate(a,log((double)hfloat::radix())) );

    d = log(sqrt(2.0));
    a = constant_logsqrt2(n);
    print("const_logsqrt2=\n",a,15);
    cout.precision(23);  cout << "\n =?= " << d << endl;
    jjassert( approximate(a,d) );


    m = 1;
    mul2pow(m,q,m);
    m -= 1;
    print("mersenne=\n",m);

    sqrt(3,a);
    a += 2;
    print("2+sqrt(3)=\n",a);

    log(a,b);
    print("log(2+sqrt(3))=\n",b);

    mul2pow(b,q-2,c);
    print("2^(q-2)*log(2+sqrt(3))=\n",c);

//    cosh(c,a);  // a should be an integer
//    print("cosh(...)=\n",a);

    exp(c,a);  a /= 2;  // a should be close to an integer
    print("exp(...)=\n",a);

    round(a,a);
    print("round()=\n",a);

    LL(q,b);
    print("== LL()=\n",b);

    a -= b;
    print("0 =?= a-b=\n",a,10);
    jjassert( a.is_zero() );

    fmod(b,m,b);
    print("mod()=\n",b);

    round(b,b);
    print("round(mod())=\n",b,10);

    if ( b!=0 )
    {
        b -= m;
        round(b,b);
        print("round(mod())-m=\n",b,10);
    }

    print("mersenne=\n",m,10);
    if ( b==0 )  cout << "is PRIME." << endl;
    else         cout << "is NOT prime." << endl;

    return 0;
}
//---------------
