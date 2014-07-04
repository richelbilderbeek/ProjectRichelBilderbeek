#include <cmath>
#include <iostream>
#include <fxt/jjassert.h>

#include "hfloat.h"


void
doit(const char *x, hfloat &a)
{
    cout << "\n\"" << x << "\":";
    st2hfloat(x,a); 
    print(" =?= \n",a,0);
} 
//-------------------------


int
test3(long /*n*/)
{
    cout<<"\n TEST3 conversion of strings to hfloats"<<flush;

    hfloat a;

    // --- valid strings:

    // zero:
    doit("0",a);        jjassert( a==0 );
    doit("0.e0",a);     jjassert( a==0 );
    doit(".0e0",a);     jjassert( a==0 );
    doit("0*10^6",a);   jjassert( a==0 );
    doit("0.0*10^6",a); jjassert( a==0 );
    doit("00000",a);    jjassert( a==0 );
    doit("0.0",a);      jjassert( a==0 );
    doit(".0",a);       jjassert( a==0 );
    doit("0.",a);       jjassert( a==0 );
    doit("00.",a);      jjassert( a==0 );
    doit("00.00",a);    jjassert( a==0 );
    doit(".000000",a);  jjassert( a==0 );
    doit("0",a);        jjassert( a==0 );
    doit(" 0",a);       jjassert( a==0 );
    doit("0 ",a);       jjassert( a==0 );
    doit(" 0 ",a);      jjassert( a==0 );

    doit("1.",a);   jjassert( a==1 );
    doit("1",a);    jjassert( a==1 );
    doit(" 1",a);   jjassert( a==1 );
    doit("1 ",a);   jjassert( a==1 );
    doit(" 1 ",a);  jjassert( a==1 );
    doit("2.",a);   jjassert( a==2 );
    doit("2",a);    jjassert( a==2 );
    doit(" 2",a);   jjassert( a==2 );
    doit("2 ",a);   jjassert( a==2 );
    doit(" 2 ",a);  jjassert( a==2 );


    double r=1e-12;  // relative error allowed for

    doit("3.E9",a);   jjassert( approximate(a,0.3e10,r) );
    doit("3E9",a);    jjassert( approximate(a,0.3e10,r) );
    doit("30E9",a);   jjassert( approximate(a,0.3e11,r) );
    doit("30.E9",a);  jjassert( approximate(a,0.3e11,r) );
    doit(".3E9",a);   jjassert( approximate(a,0.3e9,r) );
    doit(".03E9",a);  jjassert( approximate(a,0.3e8,r) );
    doit(".003E9",a); jjassert( approximate(a,0.3e7,r) );

    doit("3.E99",a);   jjassert( approximate(a,0.3e100,r) );
    doit("3E99",a);    jjassert( approximate(a,0.3e100,r) );
    doit("30E99",a);   jjassert( approximate(a,0.3e101,r) );
    doit("30.E99",a);  jjassert( approximate(a,0.3e101,r) );
    doit(".3E99",a);   jjassert( approximate(a,0.3e99,r) );
    doit(".03E99",a);  jjassert( approximate(a,0.3e98,r) );
    doit(".003E99",a); jjassert( approximate(a,0.3e97,r) );

    doit("12.345*10^6",a);     jjassert( approximate(a,12.345e6,r) );
    doit("0012.345*10^6",a);   jjassert( approximate(a,12.345e6,r) );

    doit("+.87654000*10^1",a); jjassert( approximate(a,0.87654000e1,r) );
    doit(".87654000*10^1",a);  jjassert( approximate(a,0.87654000e1,r) );
    doit("0.87654000*10^1",a); jjassert( approximate(a,0.87654000e1,r) );
    doit("87654000.*10^1",a);  jjassert( approximate(a,  87654000e1,r) );

    doit("-.87654000*100^1",a);   jjassert( approximate(a,-.87654000e2,r) );
    doit("-.87654000*1000^-7",a); jjassert( approximate(a,-.87654000e-21,r) );
    doit("+.87654*10^3",a);       jjassert( approximate(a,+.87654000e3,r) );
    doit(".87654*10000^6",a);     jjassert( approximate(a, .87654000e24,r) );

    doit("0000.00087654",a);     jjassert( approximate(a,0.00087654000e0,r) );
    doit("0000.87654",a);        jjassert( approximate(a,0.87654000e0,r) );
    doit("00000000087654",a);    jjassert( approximate(a,87654,r) );
    doit("000087654*10^5 ",a);   jjassert( approximate(a,87654e5,r) );
    doit("8.7654",a);            jjassert( approximate(a,8.7654,r) );
    doit(".87654",a);            jjassert( approximate(a,.87654,r) );
    doit("0.87654",a);           jjassert( approximate(a,.87654,r) );
    doit("00.87654",a);          jjassert( approximate(a,.87654,r) );


    doit("+1.8765432109876543210987654321e-7",a);
    jjassert( approximate(a,1.8765432109876543210987654321e-7,r) );

    doit("+18765432109876543210987654321e-7",a);
    jjassert( approximate(a,18765432109876543210987654321e-7,r) );

    doit("+18765432109876543210987654321.e-7",a);
    jjassert( approximate(a,18765432109876543210987654321e-7,r) );

    doit("+18765432109876543210987654321.",a);
    jjassert( approximate(a,18765432109876543210987654321e0,r) );


    return 0;
}
//========================= end ==========================
