
#include <cmath>
#include <iostream>

#include "hfloat.h"
#include "hfverbosity.h"
#include "examples.h"  



int
your_stuff(long n, hfloat &res)
//
//  playground ...
//
{
    hfverbosity::hush_all();
    hfloat d(n), x(n);

    isqrt(22222,x);
    elliptic_K(x,d);
    cout << "\n your result=" << d << endl;

    elliptic_K(x,x,1);
    cout << "\n your result II=" << x << endl;

    res = x;

    return 0;
}
// ========================= end YOURSTUFF ========================
