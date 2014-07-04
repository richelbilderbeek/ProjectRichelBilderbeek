
#include <cstdlib>  // for exit()
#include <iostream>

#include "examples.h"

#include "hfloat.h"
#include "hfverbosity.h"

#include "../mult/fxtmult.h"


void
usage(const char *argv0, int default_ldn, int radix)
{
    cerr<<
        "USAGE:  '"<< argv0 <<" LDN WHAT RADIX FNAME'"
        "   (or  '"<< argv0 <<" --help'  for this help)"
        "\n First arg (LDN) is the (base 2) logarithm of the desired precision in LIMBs"
        "\n   A LIMB is the 'superdigit' used by hfloat internally"
        "\n   (the decimal precision is prec*log_10(RADIX))"
        "\n   e.g. LDN=11 means 2^11=2048 LIMBS;  default is "
        << default_ldn << " (or " << (1<<default_ldn) << " LIMBs)"
        "\n Second arg (WHAT) chooses what to do (see below)"
        "\n Third arg (RADIX) gives radix (default is " << radix << ")"
        "\n   (usually you'll use 10000 for decimal digits, 65536 for hex digits)"
        "\n Fourth arg (FNAME) gives filename where to save the result."
        <<endl;
}
//================ end USAGE ====================


void
examples_usage(const char *argv0)
{
    cerr<<
	"\n Second arg chooses what to do:"
	"\n  Computations marked with '!' are for modest precisions only."
	"\n    0 => pi, quartic iteration with r=4"
	"\n    1 => pi, quartic iteration with r=16"
	"\n    2 => pi, 2.order iteration"
	"\n    3 => pi, agm iteration"
	"\n    4 => pi, agm3 iteration, faster variant"
	"\n    5 => pi, agm3 iteration, slower variant"
	"\n    6 => pi, derived agm iteration"
	"\n    7 => pi, quintic iteration"
	"\n    8 => pi, 3.order iteration"
	"\n    9 => pi, 9.order iteration"
	"\n   10 => pi, cubic agm iteration"
	"\n   13 => pi, agm iteration, quartic variant"
	"\n   14 => pi, agm3 iteration, quartic faster variant"
	"\n   15 => pi, agm3 iteration, quartic slower variant"
	"\n   16 => pi, agm iteration a la Schoenhage (DEFAULT)"
	"\n   5N => ! pi, N-term arctan series (N=2...7)"
	"\n   60 => ! pi, as arctan(1) (via sumalt)"
	"\n  100 => ! eulers e  (2.7182818...) via exp(1)"
	"\n  101 => ! eulers e  (2.7182818...) via series"
	"\n  111 => log(2) =0.6931471805599453...  via agm"
	"\n  112 => ! log(2) =0.6931471805599453...  via sumalt"
	"\n  120 => ! zeta(3) =1.202056903159594...  via sumalt"
	"\n  141 => sqrt(2) =1.4142135623"
	"\n  161 => golden =(sqrt(5)+1)/2 =1.61803398874989..."
	"\n  163 => ! exp(pi*sqrt(163)) =262537412640768743.999..."
	"\n  207 => ! i**i =exp(-pi/2) =0.2078795763507619..."
	"\n  314 => pi-check (run different algorithms for pi & compare the results)"
	"\n  847 => agm(1,1/sqrt(2)) =0.8472130847939790866064991234..."
	"\n  915 => ! catalan=0.915965594177219015 ... via sumalt()"
	"\n  999 => (your) stuff in yourstuff.cc"
	<< endl;

    cerr <<
	"\n  e.g.: " << argv0 << " 11 1 65536"
	"\n    use method 1, precision= 2^11=2048 (radix 65536) LIMBs"
	"\n    (i.e. precision is 2048*16 bits= 4096 bytes)"
	"\n  e.g.: " << argv0 << " 8 0 10000  (default action)"
	"\n    use method 0, precision= 2^8=256 (radix 10000) LIMBs"
	"\n    (i.e. precision is 256*4=1024 decimal digits)"
	"\n  e.g.: " << argv0 << " 18 16 10000 result.txt"
	"\n    compute pi to 1 million decimal digits (4*2^18=1M)"
        "\n    use Schoenhage's agm, save result to result.txt"
	<< endl;
}
//================ end ====================


int
main(int argc, char **argv)
{
    int ldn = 10;  // DEFAULT LDN
    int rx = (int)hfloat::radix();  // DEFAULT RADIX
    ulong n;

    if ( argc>1 )
    {
        for (int k=0; argv[1][k]!=0; ++k)
        {
            if ( (argv[1][k]=='?') || (argv[1][k]=='h') || (argv[1][k]=='H') )
            {
                usage(argv[0], ldn, rx);
                examples_usage(argv[0]);
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


    int arg2 = 16;
    // 2 or more args  => application dependent parameter:
    if ( argc>2 )  arg2 = atoi(argv[2]);

    // 3 or more args  => user gave radix:
    if ( argc>3 )  rx = atoi(argv[3]); // radix from arg 3

    hfloat::radix(rx);


    char *fname = 0;
    if ( argc>4 )  fname = argv[4];

    if ( argc>5 )  cerr << "WARNING: excess argument(s) ignored ! " << endl;



    hfloat::print_info();

    hfloat r(n);    // for the result

//    hfverbosity::hush_all();  // do not echo any operations
    hfverbosity::tell_all();  // echo all operations
//    hfverbosity::tell_pi();  // echo pi-related intermediate results
    hfverbosity::tell_fxtmult();  // give info about fxtmult
//    fxtmult::checkmult = 0;

    if( arg2>=50 && arg2<60 )
    {
        cout << " pi_arctan(r,arg2):" << endl;
	pi_arctan(r,arg2);
    }
    else
    {
	switch(arg2)
	{
	case 0:   cout << " pi_4th_order(r,0):" << endl;
            pi_4th_order(r,0);  break;

	case 1:   cout << " pi_4th_order(r,1):" << endl;
            pi_4th_order(r,1);  break;

	case 2:   cout << " pi_2nd_order(r):" << endl;
            pi_2nd_order(r);  break;

	case 3:   cout << " pi_agm(r,0):" << endl;
            pi_agm(r,0);  break;

	case 4:   cout << " pi_agm3(r,1):" << endl;
            pi_agm3(r,1);  break;

	case 5:   cout << " pi_agm3(r,-1):" << endl;
            pi_agm3(r,-1);  break;

	case 6:   cout << " pi_derived_agm(r):" << endl;
            pi_derived_agm(r);  break;

	case 7:   cout << " pi_5th_order(r):" << endl;
            pi_5th_order(r);  break;

	case 8:   cout << " pi_3rd_order(r):" << endl;
            pi_3rd_order(r);  break;

	case 9:   cout << " pi_9th_order(r):" << endl;
            pi_9th_order(r);  break;

	case 10:  cout << " pi_cubic_agm(r):" << endl;
            pi_cubic_agm(r);  break;

	case 13:  cout << " pi_agm(r,1):" << endl;
            pi_agm(r,1);  break;

	case 14:  cout << " pi_agm3(r,4):" << endl;
            pi_agm3(r,4);  break;

	case 15:  cout << " pi_agm3(r,-4):" << endl;
            pi_agm3(r,-4);  break;

	case 16:  cout << " pi_agm_sch(r):" << endl;
            pi_agm_sch(r);  break;

            // [[case 50..59: see above]]

        case 60: cout << " pi via 4*sumalt(gregory_term):" << endl;
            sumalt(gregory_term, r);  r *= 4;  break;

	case 100: cout << " euler_e(r):" << endl;
            euler_e(r);  break;             // e = 2.718281828459045...

	case 101: cout << " euler_e_series(r):" << endl;
            euler_e_series(r);  break;      // e = 2.718281828459045...

	case 111: cout << " log2(n,r):" << endl;
            log2(n,r);  break;          // log(2)=0.6931471...

	case 112: cout << " sumalt(log2_term, r):" << endl;
            sumalt(log2_term, r);  break;      // log(2)=0.6931471...

	case 120: cout << " zeta(3) = 1.202056903159594... :" << endl;
            zeta3(r);  break;

	case 141: cout << " sqrt(2):" << endl;
            sqrt(2,r);  break;

	case 161: cout << " golden = (sqrt(5)+1)/2 =1.61803398874989... :" << endl;
            sqrt(5, r);  r+=1;  r/=2; break;

	case 163: cout << " exp_pi163(n,r):" << endl;
            exp_pi163(n,r);  break;     // exp(pi*sqrt(163))

	case 207: cout << " i**i = exp(-Pi/2) =0.2078795763507619... :" << endl;
            r = constant_pi(n);  r/=2;  r.negate();  exp(r, r);  break;

	case 314: cout << " pi_check:" << endl;
            pi_check(n,r);  break;

	case 847: cout << " agm(1,1/sqrt(2)) = 0.8472130847:" << endl;
            isqrt(2,r); agm1(r, r);  break;

	case 915: cout << " sumalt(catalan_term, r):" << endl;
            sumalt(catalan_term, r);  break;  // compute catalan=0.91596...

	case 999: cout << " your_stuff(n,r):" << endl;
            your_stuff(n,r);  break;      //  <--- your code in yourstuff.cc

	default:  { examples_usage(argv[0]); exit(0); }  // usage info
	}
    }
    // ---------

    cout << " done. " << endl;

    if ( fname )  // save result:
    {
        save(fname,r);
        cout<<"\n result saved to file "<<fname<<"\n"<<flush;
    }

    print("\n RESULT:\n",r, r.prec()<=16?r.prec():16 );
    cout<<" precision="<<r.prec()<<" LIMBS  =="
        << prec_convert(r.prec(),10) <<" decimal digits";

    print_last("\n last digits are:\n", r, 16);

    cout << "\n --------------- computation done -------------- " << endl;


    hfdata::print_statistics(n);
    fxtmult::print_statistics(n);

    cerr<<endl;

    return 0;
}
//===================== end MAIN =====================================
