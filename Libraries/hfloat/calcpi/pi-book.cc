
#include <sys/time.h>  // gettimeofday(), timeval
#include <cstdlib>  // exit()
//#include <cstring>
#include <iostream>


#include <fxt/aux0/timer.h>

#define MIN(x,y) ((x)<(y)?(x):(y))

#define APPLICATION_USAGE(x)   examples_usage(x)

#define DO_APPLICATION(n,alg,argv0,fname) do_examples(n,alg,argv0,fname)

#include "pi-book.h"
#include "pi-book.inc"

#include "hfloat.h"
#include "hfverbosity.h"

timeval t0, t1;

void
do_examples(long n, int alg, const char *argv0, char *fname)
{
//    int binsaveq;
    hfloat r(n);    // for the result
    char result[100]; // for the result explanation

    hfverbosity::hush_all();  // do not echo any operations
    // hfverbosity::tell_all();  // echo all operations
    // hfverbosity::tell_pi();  // echo pi-related intermediate results
    // hfverbosity::tell_fxtmult();  // give info about fxtmult
    // fxtmult::checkmult = 0;

//    cout<<" precision of result will be="<< r.prec() <<" LIMBS ";
//    cout<<" =="<< r.dec_prec() <<" decimal digits" << endl;
//    binsaveq = hfdata::rx2pw;  // if radix=2^x then binsave

    // ---------
    gettimeofday(&t0, 0);

    if( alg>=52 && alg<=57 )
    {
        sprintf(result, "pi= with an arctan series of %d terms", alg-50);
        cout << "pi: " << alg-50 << "-term arctan series:" << endl;
        pi_arctan(r,alg);
    }
    else
    {
            switch(alg)
            {
        case 0:  strcpy(result, "pi= with Borwein's quartic (r=4)      ");
//            cout << result << endl;
            pi_4th_order(r,0);  break;

        case 1:  strcpy(result, "pi= with Borwein's quartic (r=16)     ");
//            cout << result << endl;
            pi_4th_order(r,1);  break;

        case 2:  strcpy(result, "pi= with Borwein's quadratic          ");
//            cout << result << endl;
            pi_2nd_order(r);  break;

        case 3:  strcpy(result, "pi= with Gauss-AGM                    ");
//            cout << result << endl;
            pi_agm(r,0);  break;

        case 4:  strcpy(result, "pi= with AGM3 fast                    ");
//            cout << result << endl;
            pi_agm3(r,1);  break;

        case 5:  strcpy(result, "pi= with AGM3 slower                  ");
//            cout << result << endl;
            pi_agm3(r,-1);  break;

        case 6:  strcpy(result, "pi= with Borwein's Derived AGM        ");
//            cout << result << endl;
            pi_derived_agm(r);  break;

        case 7:  strcpy(result, "pi= with Borwein's quintic            ");
//            cout << result << endl;
            pi_5th_order(r);  break;

        case 8:  strcpy(result, "pi= with Borwein's cubic              ");
//            cout << result << endl;
            pi_3rd_order(r);  break;

        case 9:  strcpy(result, "pi= with Borwein's nonic              ");
//            cout << result << endl;
            pi_9th_order(r);  break;

        case 10: strcpy(result, "pi= with AGM cubic                    ");
//            cout << result << endl;
            pi_cubic_agm(r);  break;

        case 13: strcpy(result, "pi= with AGM quartic                  ");
//            cout << result << endl;
            pi_agm(r,1);  break;

        case 14: strcpy(result, "pi= with AGM3, quartic fast           ");
//            cout << result << endl;
            pi_agm3(r,4);  break;

        case 15: strcpy(result, "pi= with AGM3, quartic slower         ");
//            cout << result << endl;
            pi_agm3(r,-4);  break;

        case 16: strcpy(result, "pi= with Gauss-AGM, Schoenhage variant");
//            cout << result << endl;
            pi_agm_sch(r);  break;

        case 100:strcpy(result, "e = via exp(1)                         ");
//            cout << result << endl;
            euler_e(r);  break;             // 2.718281828459045...

        case 101:strcpy(result, "e = via series:                         ");
//            cout << result << endl;
            euler_e_series(r);  break;      // 2.718281828459045...

        case 111:strcpy(result, "ln(2)= :                                ");
//            cout << result << endl;
            log2(n,r);  break;          // log(2)=0.6931471...

        case 163:strcpy(result, "exp(pi*sqrt(163))= :                    ");
//            cout << result << endl;
            exp_pi163(n,r);  break;     // exp(pi*sqrt(163))

        case 999:strcpy(result, "your stuff                              ");
//            cout << result << endl;
            your_stuff(n,r);  break;      //  <--- your code in yourstuff.cc

        default:  { examples_usage(argv0); exit(0); }  // usage info
        }
    }
    // ---------

    cout << " done. " << endl;

    //    if(alg<99)  r-=3;  // fractional part of pi

    gettimeofday(&t1, 0);
    double t = timediff(t0, t1);

    // save result: save only if fname specified
    if (*fname)  save(fname,r);

    cout<< "\n RESULT:\n " << result << ", prec=" << r.prec()*4
        << (hfloat::radix() == 10000 ? " dec" : " hex") << " digits"
        <<", time= " << t << " secs" << endl;

    print("\nfirst digits: ",r,MIN(12,r.prec()));
    print_last("last  digits: ", r, MIN(12, r.prec()));
    if (*fname)  cout << "Result is saved to file " << fname << endl;

    cout << "--------------- computation done --------------\n ";
}
//================ end ====================

void
examples_usage(const char *pname)
{
    cout<<
        "\n    0 => pi: Borwein's quartic (r=4)   10 => pi: AGM cubic"
        "\n    1 => pi: Borwein's quartic (r=16)  13 => pi: AGM quartic"
        "\n    2 => pi: Borwein's quadratic       14 => pi: AGM3, quartic fast"
        "\n    3 => pi: Gauss-AGM                 15 => pi: AGM3, quartic slower"
        "\n    4 => pi: AGM3 fast                 16 => pi: Gauss-AGM, Schoenhage variant"
        "\n    5 => pi: AGM3 slower               5N => pi: N-term arctan series (N=2..7)"
        "\n    6 => pi: Borwein's Derived AGM    100 => e : via exp(1)"
        "\n    7 => pi: Borwein's quintic        101 => e : via series"
        "\n    8 => pi: Borwein's cubic          111 => ln(2):"
        "\n    9 => pi: Borwein's nonic          163 => exp(pi*sqrt(163)):"
//        "\n                                    999 => (your) stuff in yourstuf.cc"
        <<endl;
}
//================ end EXAMPLES_USAGE ====================

