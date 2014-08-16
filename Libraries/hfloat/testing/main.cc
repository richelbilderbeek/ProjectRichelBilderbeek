
#include "test.h"

#include <cmath>
#include <cstdlib>  // atol()
#include <iostream>

#include "hfloat.h"
#include "fxtmult.h"


#define  APPLICATION_USAGE(x)  test_usage(x)

#define  DO_APPLICATION(n,arg2,argv0)  do_test(n,arg2)


#define  RADIX  ((int)hfloat::radix())

#define  DEFAULT_LDN  10


void
usage(const char *argv0, int default_ldn, int radix)
{
    cerr<<
        "USAGE:  '"<< argv0 <<" LDN WHAT RADIX FNAME'"
        "   (or  '"<< argv0 <<" --help'  for this help)"
        "\n First arg (LDN) is the (base 2) logarithm of the desired precision in LIMBs"
        "\n   (the decimal precision is prec*log_10(RADIX))"
        "\n   e.g. LDN=11 means 2^11=2048 LIMBS;  default is "
        << default_ldn << " (or " << (1<<default_ldn) << " LIMBs)"
        "\n Second arg (WHAT) chooses what to do (see below)"
        "\n Third arg (RADIX) gives radix (default is 10000);  currently set to " << radix <<
        "\n Fourth arg (FNAME) gives filename where to save the result."
        <<endl;
}
//================ end USAGE ====================


int
main(int argc, char **argv)
{
    int ldn = DEFAULT_LDN;
    ulong n;

    if ( argc>1 )
    {
        for (int k=0; argv[1][k]!=0; ++k)
        {
            if ( (argv[1][k]=='?') || (argv[1][k]=='h') || (argv[1][k]=='H') )
            {
                usage(argv[0], DEFAULT_LDN, RADIX);

                APPLICATION_USAGE(argv[0]);

                exit(0);
            }
        }

        ldn = atoi(argv[1]); // precision from arg
    }


    if ( ldn<5 )
    {
        ldn = 5;
        cerr << "ldn set to 5 (less than 32 LIMBs makes little sense)" << endl;
    }

    n = ((ulong)1<<ldn);

    hfloat::default_prec(n);


    int arg2 = 0;
    // 2 or more args  => application dependent parameter:
    if ( argc>2 )  arg2 = atoi(argv[2]);

    int rx = RADIX;
    // 3 or more args  => user gave radix:
    if ( argc>3 )  rx = atoi(argv[3]); // radix from arg 3

    hfloat::radix(rx);

    char *fname = 0;
    if ( argc>4 )  fname = argv[4];

    if ( argc>5 )  cerr << "WARNING: excess argument(s) ignored ! " << endl;


//------- call the big & mighty functions ------

    hfloat::print_info();

    DO_APPLICATION(n, arg2, argv[0]);

//----------------------------------------------


    hfdata::print_statistics(n);
    fxtmult::print_statistics(n);

    cerr<<endl;

    return 0;
}
//===================== end MAIN =====================================


void
do_test(long n, int arg2)
{
    switch(arg2)
    {
    case 0 : test0(n);  break;  //  cmp, add, sub 
    case 1 : test1(n);  break;  //  sqr, mul, div, floor
    case 2 : test2(n);  break;  //  root + pow
    case 3 : test3(n);  break;  //  st2hfloat
    case 4 : test4(n);  break;  //  ...
    case 5 : test5(n);  break;  //  ...
    default: test_usage("");
    }
}
//================ end ====================



void
test_usage(const char *argv0)
{
    argv0 = 0;  // suppress warning
    cerr<<
	"\n  highly experimental test code ... "
	"\n  arg2= 0 ... 5 "
	<<endl;
}
//================ end ====================

