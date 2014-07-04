
//#include <cmath>
#include <iostream>
//#include <cstdlib>

#include "hfloat.h"
//#include "mytimer.h"
//#include <fxt/jjassert.h>


void
misc(ulong n, ulong p)
//
// do computations with precision n
// print with precision p
//
{
    hfloat e;
    e = 1;
    e = exp(e);
    print( "e=\n", e, p);
 
    hfloat pi;
    pi_4th_order(n,pi);
    print( "e=\n", e, p);

    hfloat t;



}


void
some_constants()
{    
    ulong n = 1024;

    hfloat_set_default_precision(n);
    hfloat_set_radix(10000);

    misc(n,25);


    hfloat_set_default_precision(n);
    hfloat_set_radix(64536);

    misc(n,32);
}

