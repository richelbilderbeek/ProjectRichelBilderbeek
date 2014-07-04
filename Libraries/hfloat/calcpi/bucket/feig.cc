
#include <cmath>
#include <iostream>
#include <cstdlib> // exit()

#include "hfloat.h"

#include <fxt/jjassert.h>
//#include "feig.h"  // included below


#define print_nn(x...) save_nn(cout, x)


void print_str(const char *name, ulong ct, const hfloat &x)
{
    cout << " " << name << "str[" << ct << "]=\"";
    print_nn("", x);
    cout << "\";" << endl;
}
//=========================

void read_str(const char *str, hfloat &h)
{
    jjassert( 0!=str );

    if ( str[0]!='X' )  // str[i]!="X-END"
    {
        ulong ret;
        ret = st2hfloat( str, h );
//        if ( 0!=ret )
//        {
//            cout << "\n st2hfloat() returned " << ret << "! \n";
//            cout.flush();
//            exit(-123);
//        }
    }
}
//=========================


int main()
{
//    ulong n = 32;  // orig value =^= 128 dec. dig.
//    ulong n = 128;  // 512 dig
    ulong n = 1024; // 4096 dig
    hfloat::default_prec(n);

    // index of last result from previous computation (cf. feig.h):
    const ulong lastsa = 0; // set to val !=0 to compute more sa[] with same prec

    const ulong arrsz = 34;  // >32

    const ulong refines = 20; // max # of refinement steps

    char *sastr[arrsz];
    char *derivstr[arrsz];
    char *halfstr[arrsz];

    hfloat sa[arrsz];    // superattractive periodic points
    hfloat half[arrsz];  // value after half of the iterations
    hfloat deriv[arrsz]; // derivative of the iterated map at sa[.]


    const double l10rx = log((double)hfloat::radix()) / log(10.0);


    // delta = +4.669201609102990671853;
    // alpha = -2.50290787509589284;
    // crit  = -1.40115518909205042685;

    for (ulong i=0; i<arrsz; ++i)  half[i] = 1;
    half[1] = 1;

    // ----- setup derivatives:
    deriv[0] = +1;
    deriv[1] = -1;

    // ----- setup sa[]:
    sa[0]=0;
    sa[1]=-1;

    for (ulong i=0; i<arrsz; ++i)
    {
        sastr[i] = derivstr[i] = halfstr[i] = "X-END";
    }


#include "feig.h" /* values of superattractive periodic points as strings */

    // -------- read values from *str[]:
    for (ulong i=2; i<arrsz; ++i)
    {
        read_str( sastr[i], sa[i]);
        read_str( derivstr[i], deriv[i]);
        read_str( halfstr[i], half[i]);
    }


    hfloat z,  c;
    hfloat dc;
    hfloat eps;
    hfloat tt, tt2;
    long  cmp, oldcmp;
    for (ulong sact=lastsa+1; sact<=arrsz-2; ++sact) // ----- loop ------
    {
        ulong period = 1UL<<sact;
        cout << "\n ======== " << sact
             << ": ===============  period=" << period
             << " =============== " << endl;

        if ( sa[sact].sign()>0 ) // --- no precomputed sa[]
        {
            tt = sa[sact-2] - sa[sact-1];
            tt2 = 1.0/4.669201609102990671853;
            tt *= tt2;
            c = sa[sact-1] - tt;
        }
        else  c = sa[sact];

//        print("// c0=",c);

        z = 123.0;
        oldcmp = 0;
        for (ulong rct=0; rct<refines; ++rct) // ---------- refine loop --------------
        {
            // f(c,z) := z^2+c
            z = c;      // f^1(c,0) = c
            dc = 1;     // d_c f(c,0) = 1
            ulong pct;
            for (pct=1; pct<period/2; ++pct) // ------- iterate loop 1 -------
            {
                // ----- derivative recursion:
                // d_c f^{n}(c,0)=d_c f(c,f^{n-1}(c,0))=1+2*f^{n-1}(c,0)*d_c f^{n-1}(c,0)
                // f^{n-1}(c,0) is in z, d_c f^{n-1}(c,0) is in dc
                mul2(z, tt);
                mul(dc, tt, dc);
                add(dc, 1UL, dc);

                // --- function recursion:
                // f^{n}(c,0)=f(c,f^{n-1}(c,0))=f^{n-1}(c,0)^2+c
                sqr(z, z);
                add(z, c, z);
            }
            half[sact] = z;

            for (pct=0; pct<period/2; ++pct) // ------- iterate loop 2 -------
            {
                mul2(z, tt); // --- derivative
                mul(dc, tt, dc);
                add(dc, 1UL, dc);

                sqr(z, z);    // --- function    z -> z^2+c
                add(z, c, z);
            }
            deriv[sact] = dc;

            // ----- correct c ------
            eps = z;
            eps /= dc;
            c -= eps;  // c -= z/dc

            cout << "// -- step " << rct << ": "; // << endl;
            print_nn("  z= ",z, 5);
            print_nn("  eps= ",eps, 5);
//            print("// c_new= ", c  );
//            print("//  drv= ", deriv[sact] );
//            print("// half= ", half[sact] );

            cmp = (eps.is_zero()?-n:eps.exp());
            cout << "\n//  cmp=" << cmp << "  correct dec. dig. >=" << -floor(cmp*l10rx+0.5);
            cout << endl;

            // check precision:
            if ( cmp<-((long)n-4) )  break;  // ok ?
            if ( cmp==oldcmp )  break;  // no improvement ?
            oldcmp = cmp;

        } // ----------------------- end refine loop ---------------------------


        sa[sact] = c;
        print_str("sa", sact, sa[sact]);
        print_str("half", sact, half[sact]);
        print_str("deriv", sact, deriv[sact]);

        tt = half[sact-1]/half[sact];
        print_str("alpha", sact, tt);

        tt = sa[sact-2]-sa[sact-1];
        print("// diff(-)= ",tt,10);
        tt2 = sa[sact-1]-sa[sact];
        print("// diff(+)= ",tt2,10);
        tt /= tt2;
        print_str("delta", sact, tt);

//        hfloat2d(tt, delta);
    }

    return 0;
}
/* ============================== end FEIGENBAUM ========================= */
