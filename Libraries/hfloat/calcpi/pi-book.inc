// -*- C++ -*-
//
// this file is included from:
// hfloat/examples/main.cc
// hfloat/testing/main.cc
//

#include <cmath>
#include <cstdlib>  // atol(), exit()
//#include <stdio.h>
#include <iostream>
//#include <ctype.h>   // for isdigit()
//#include <string.h>

#include <fxt/mult/fxtmult.h>

#include "../src/include/hfloat.h"

#define  RADIX  (hfloat::radix())

#define  DEFAULT_LDN  10

void
usage(const char *argv0, int default_ldn, int radix)
{
    cout<<
        "\n pi.elf - high-precision algorithms to compute pi and other constants."
        "\n Usage variants:"
        "\n 1. " << argv0 << " - interactive use, follow command prompt." <<
        "\n 2. " << argv0 << " ldn alg radix resultfile - command line call " <<
        "\n      ldn:   (default: " << default_ldn  << ") is the log_2 of the desired precision in LIMBs "
        "\n             (1 LIMB is 4 decimal or hexadecimal digits"
//        "\n             the precision is 2^(ldn*log_10(radix)) digits"
        "\n             e.g. ldn=11 means 2^11=2048 LIMBS=8196 digits)"
        "\n      alg:   algorithm (see list below), default is 3 = Gauss-AGM "
        "\n      radix: 10000 for decimal output (def), or 65536 for hexadecimal output" <<
        "\n      resultfile: name of a file for the digits; def: no save" <<
        "\n 3. " << argv0 << " --help - this help screen"
//        << endl
        ;
}
//================ end USAGE ====================


//================ begin manual_operating ========

#define DEFAULT_ALG  3 //Hae: GAUSS-AGM
#define DEFAULT_RADIX 10000 //Hae: decimal places

void
manual_operating(char *pname)
{
    char buf[200];
    char *pbuf = buf; 
    size_t bufsize = sizeof(buf);
    char sbase[100];
    int  ldn, digits, alg;
    ulong rx;
//    ulong n;
    char fname[100] = "";
   
    printf("pi.elf - high-precision algorithms to compute pi and other constants.\n");
    while(1) {
        APPLICATION_USAGE(pname);
        printf("Enter <digits> <algorithm> dec | hex [resultfile]\n");
        *buf = '\0'; digits = 1024; alg = DEFAULT_ALG; rx = DEFAULT_RADIX;
        *fname = '\0';
        cin.getline(pbuf, bufsize);
        int n = sscanf(buf, "%d %d %s %s", &digits, &alg, sbase, fname);
        if (buf[0] == '?' || buf[1] == '?'
            || buf[0] == 'h' || buf[1] == 'h'
            || buf[0] == 'H' || buf[1] == 'H')  continue;

        if (n == 0 || digits < 0 )
        {  
            cout << "Bye." << endl;
            break;
        }
        if (digits < 32) digits = 32; // smaller values result in SIG... or wrong results

        ldn = (long)floor(log10(digits-1) / log10(2))-1;
        n = (ulong)1 << ldn; // only LIMBS = 10000 or 65536
        hfloat::default_prec(n);
        rx =10000;
        if (strncasecmp(sbase, "he", 2) == 0)  rx=65536; 
        hfloat::radix(rx);
        DO_APPLICATION(n, alg, pname, fname);
    }
    return;
}
//================ end manual_operating ========


int
main(int argc, char **argv)
{
    int ldn;
    ulong n;
    char fname[100] = "";

    if ( argc<=1 )  // no arg -> manual operating (Hae)
    {
        ldn = DEFAULT_LDN;   // default precision
        /* ask the user for arguments:
           Enter <digits> <alg> <base> <fname>
                     |      |     |       |
                     |      |     |       ---- resulting file 
                     |      |     |
                     |      |     ------ 10 or 16
                     |      ------------ one of the algorithm-codes
                     ------------------- # of dig's of the result
                                         will be trunc to next lower
                                         power of two.
        */
        manual_operating(argv[0]);
        return 0;
    }

   // cmd line args present: use original (joerg's) cmd line interface
   for (int k=0; argv[1][k]!=0; ++k)
   {
       if ( (argv[1][k]=='?')
            || (argv[1][k]=='h')
            || (argv[1][k]=='H')
            || (argv[1][k] == '-') )
       {
           usage(argv[0], DEFAULT_LDN, RADIX);

           APPLICATION_USAGE(argv[0]);

           exit(0);
       }
   }

    ldn = atoi(argv[1]); // precision from arg

    if ( ldn<0 )  ldn = -ldn;

    if (ldn < 2) ldn = 2; // Hae, otherwise: SIGABRT

    n = ((ulong)1<<ldn); 

    hfloat::default_prec(n);

    int arg2 = DEFAULT_ALG;
    // 2 or more args  => application dependent parameter:
    if(argc>2)  arg2 = atoi(argv[2]);

    int rx = RADIX;
    // 3 or more args  => user gave radix:
    if(argc>3)  rx = atoi(argv[3]); // radix from arg 3

    hfloat::radix(rx);
    hfloat::radix(rx); // Hae: don't know why, but it works

   // 4 or more args  => user gave result file name:
    if(argc>4)
      strcpy(fname, argv[4]);

   if(argc>5)  cerr<<"\n WARNING: excess argument(s) ignored ! ";

//------- call the big & mighty functions ------

    DO_APPLICATION(n,arg2,argv[0],fname);

//----------------------------------------------


//    hfdata::print_statistics(n);
//    fxtmult::print_statistics(n);

    cerr<<endl;

    return 0;
}
//===================== end MAIN =====================================
