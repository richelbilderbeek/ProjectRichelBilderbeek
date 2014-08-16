

#include "hfloat.h"
#include "hfverbosity.h"

#include "../mult/fxtmult.h"
//#include <fxt/jjassert.h>

#include <iostream>
#include <cmath>
#include <cstdlib> // exit()


static void
say_work(ulong n)
{
    const double n2 = (double)(2*n);
    double fftnwork = n2*log(n2)/log(2.0);
//    cout << "  work = " << fxtmult::fxtwork/fftnwork << " full prec real FFTs" << endl;
    cout << "  work = " << fxtmult::fxtwork/fftnwork/3 << " full prec multiplies" << endl;
    fxtmult::fxtwork = 0;
}
// -------------------------------

static void
check(const hfloat &r0, const hfloat &r)
{
    ulong d;
    cmp(r0, r, d);
    d = r.prec()-d;

    cout << "diff=" << d << "  (of " << r.prec() << ")";
    cout << "  i.e. " << r.prec()-d << " are correct";

    say_work(r.prec());

    if ( d>15 )
    {
        cout << "      ***** !YUCK! ***** ";
        print("\n r=\n",r, 16);
        print_last("last digits:\n", r, 16);
    }

    if ( d>=50 )
    {
//        print("\n r0=\n",r0);
//        print("\n r=\n",r);
//        jjassert( 0 );
    }

    cout << endl;
//    cout << endl;
}
// -------------------------------



void
pi_check(long n, hfloat &r)
{
    fxtmult::fxtwork = 0;
    hfverbosity::hush_all();
    hfverbosity::piname = 1;

    hfloat r0(n);
    cout << "algorithm to compare to =" << endl;
    int atanq = (n < (1<<12));
    if ( atanq )
    {
        cout << " pi_arctan(r,arg2):" << endl;
        pi_arctan(r0,53);
    }
    else
    {

        cout << " pi_4th_order(r,0):" << endl;
        pi_4th_order(r0,0);
        say_work(r0.prec());
    }

    print("\n RESULT:\n",r0, 16);
    print_last("\n last digits are:\n", r0, 16);
    cout << endl;
    cout << endl;

    if ( atanq )
    {
        pi_4th_order(r,0);
        check(r0,r);
    }

    pi_4th_order(r,1);
    check(r0,r);

    pi_agm_sch(r);
    check(r0,r);

//    exit(0); //////////////

    pi_agm(r,0);
    check(r0,r);

    pi_agm3(r,1);
    check(r0,r);

    pi_agm(r,1);
    check(r0,r);

    pi_agm3(r,4);
    check(r0,r);

    pi_agm3(r,-4);
    check(r0,r);

    pi_agm3(r,-1);
    check(r0,r);

    pi_cubic_agm(r);
    check(r0,r);

    pi_3rd_order(r);
    check(r0,r);

    pi_2nd_order(r);
    check(r0,r);

    pi_derived_agm(r);
    check(r0,r);

    pi_5th_order(r);
    check(r0,r);

    pi_9th_order(r);
    check(r0,r);

    exit(0);
//    r = r0;
}
// -------------------------------

