
#include <cmath>
#include <iostream>

#include "hfloat.h"
//#include "examples.h"  



int
exp_pi163(long n, hfloat &r)
//
// exp(x*sqrt(163))
//
// call with moderate precision (<=10 or so), exp takes long !
//
{
    hfloat x(n), t(n);

    pi_4th_order(x);

    print("\n x=",x,8);

    t = 1;
    t /= 163;
    print("\n 1/163= ",t,8);

    isqrt(t,t);
    print("\n sqrt(163)= ",t,8);

    t *= x;
    print("\n x*sqrt(163)= ",t,8);

    exp(t,r);
    print("\n exp(x*sqrt(163))=\n",r,18);

    sub(r, (ulong)744, t);
    print("\n exp(x*sqrt(163))-744=\n",t,18);

    cbrt(t,t);
    print("\n (exp(x*sqrt(163))-744)^(1/3)=\n",t,18);

    t += 1;
    floor(t,t);
    print("\n =approx=\n",t,18);


    return 0;
}
//-----------------------------
