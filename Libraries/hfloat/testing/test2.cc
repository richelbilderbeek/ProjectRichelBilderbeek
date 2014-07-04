#include <cmath>
#include <iostream>
#include <fxt/jjassert.h>

#include "hfloat.h"
#include "mytimer.h"

int
doit(const hfloat &a, hfloat &b, hfloat &c, hfloat &/*d*/)
{
    for(int k=-8; k<=8; ++k)
    {
        cout<<"\n ---- root/pow k="<<k<<": "<<endl;

//        b = a;  root(b, k, b);
        root(a, k, b);  // b = a^(1/k)

        print(" b=",b,20);

        pow(b, k, c);  // c = b^k
        print(" c=",c,20);

        if ( k!=0 )
        {
            c -= a;
            print(" TEST 0=?=",c,20);
            long q =  (long)c.prec() + c.exp();
            cout << "q=" << q << endl;
            if ( q > 11 )
            {
                cout<<" ERROR at k="<< k <<" ! "<<endl;
                jjassert( 0 );
            }
        }

    }

    return 0;
}
//-------------------------------
 

int
test2(long nn)
{
    hfloat::radix(10000);
    hfloat a(nn), b(nn), c(nn), d(nn);

    cout<<"\n TEST2 "<<flush;

    d2hfloat(1.0/M_PI,a);
//    a = 4;

    cout<<"\n ================  : "<<endl;
    doit(a,b,c,d);

    cout<<"\n ================  short input: "<<endl;
    a.prec(5);
    doit(a,b,c,d);

    return 0;
}
//====================== end =====================

