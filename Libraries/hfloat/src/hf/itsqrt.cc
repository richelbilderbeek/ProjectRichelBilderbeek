
#include "hfloat.h"
#include "hfverbosity.h"
#include <fxt/sort/minmaxmed23.h>  // min2(), max2()
#include <fxt/aux1/copy.h>  // null()

#include <fxt/jjassert.h>
#include "hfparanoia.h"

#include <cmath>
#include <fxt/fxtio.h>


#define  THIRD_ORDER_SQRT 1  // set to 1
#define  THIRD_ORDER_INV  1  // set to 1

// for debug:
#define PR(x)
#define PRP    10

#define  CHECK_ITSQRT  0  // set this to 1 for check


//#warning  'sqrt_iteration() is experimental (loss of precision !)'

int
sqrt_iteration(const hfloat &dd, hfloat &x)
//
//  use  x -=  + (x*x-d)/(2*x)  and  v \appox 1/x
//
//  v +=  v * (1 - x * v)        --> 1/x --> 1/sqrt(d)
//  x -=  (x^2 - d) * v / 2      --> sqrt(d)
//
//  returns the number of iterations needed
{
#ifdef  HF_PARANOIA
    jjassert( dd.OK() );
#endif

//    jjassert( dd.data() != x.data() );
    jjassert( !dd.negative() );

    static hfloat d(64);  // jjnote: static hfloat
    d.prec( dd.prec() );   // possible resize
    d.copy(dd);
#define  dd  GONE

    if ( hfverbosity::itbegin )  cout << "\nIT_SQRT{:\n";
    PR( cout << __PRETTY_FUNCTION__ << endl; );
    PR( print("\n d=",d,11); );

    long  xe = (d.exp()/2)*2;
    PR( cout << "\n  d.exp()=" << d.exp() << "  xe=" << xe << endl; );
    d.exp( d.exp()-xe );    // remove (big) exponent for calculations

    const ulong pg = x.prec();         // precision goal
    const ulong rpg = (pg>=4?pg-4:1);  // jjnote: magic: realistic precision goal
    ulong pr = min2((ulong)64, pg);
    PR( hfloat z(pg); );

    static hfloat v(64);  // jjnote: static hfloat
    v.prec( pg/2 );       // possible resize
    v.prec( pr );
    null(v.data()->dig(), v.size());  // jjnote: STATEMENT MUST BE HERE
    isqrt(d, v);  // v = 1/sqrt(d)
    PR( print("v_0=",v,4); );
    PR( sqr(v,z);  z *= d;  z -= 1;  print("v_0prec=",z,4); );

    null(x.data()->dig(), x.prec());  // jjnote: STATEMENT MUST BE HERE
    x.prec( pr );
    mul(v, pr, d, pr, x, pr);  // x = sqrt(d)
    PR( print("x_0=",x,4); );
    PR( sqr(x,z);  z -= d;   print("x_0prec=",z,4); );

    static hfloat y(64);  // jjnote: static hfloat
    y.prec( pg );         // possible resize

    const ulong i3 = 16;
    static hfloat tt(i3);  // jjnote: static hfloat for third order terms

    ulong ap = pr-4;  // achieved precision
    int j = 1;
    const int maxit = (int)(8+log((double)pg)/log(2.0));
    for (  ; j<maxit; ++j)
    {
        pr = min2(2*pr, pg);
        ulong hp = pr/2;
        ulong qp = pr/4;
        PR( cout << "\n ------ j=" << j << "  pr=" << pr << endl; );
        y.prec( pr );
        v.prec( hp );
        x.prec( hp );

        // ---- NEXT V (SECOND ORDER TERM):
        null(v.data()->dig()+qp, v.size()-qp);
        PR( sqr(v,z);  z *= d;  z -= 1;  print("v1_prec=",z,4); );
        sqr(v, qp, y, hp);         // v*v    quart prec sqr
        mul(y, hp, x, hp, y, pr);  // v*v*x  half prec mult
        sub(v, y, y);              // add_2 := v-v*v*x
        // here y = second order term for inverse
        PR( print("v2_add=",y,4); );
        add(v, y, v);              // v_2 = v + v*(1-v*x)
        PR( sqr(v,z);  z *= d;  z -= 1;  print("v2_prec=",z,4); );
#if  ( THIRD_ORDER_INV==1 )
//#warning 'FYI: THIRD_ORDER_INV is set, fine.'
        sqr(y, i3, y, i3);        // (v*(1-v*x))^2
        mul(y, i3, x, i3, y, i3); // x*(v*(1-v*x))^2 = v*(1-v*x)^2;
        // here y = third order term for inverse
        PR( print("v3_add=",tt,4); );
        add(v, y, v);             // v_3 = v_2 + v*(1-v*x)^2
        PR( sqr(v,z);  z *= d;  z -= 1;  print("v+_prec=",z,4); );
#else  // THIRD_ORDER_INV
#warning  ' THIRD_ORDER_INV not set =--> LOSS OF PRECISION ! '
#endif  // THIRD_ORDER_INV
        // here v should have the precision that x has,
        // which is a bit less that half of the current precision
        PR( jjassert( -z.exp() > (long)hp-15 ) ); // "Inv failed"


        x.prec( pr );
        // ---- NEXT X (SECOND ORDER TERM):
        sqr(x, hp, y, pr);          // x*x;  half prec sqr;
        sub(y, d, y);               // x*x-d
        mul(y, hp, v, hp, y, pr);   // (x*x-d)/x;  half prec mult;
        div2(y, y);                 // y := (x*x-d)/(2*x) == second order term
        PR( print("y_old=",y,11); );

        // here y = second order term
        sub(x, y, x);               // x =  x - (x*x-d)/(2*x)
        // here we (almost) doubled the precision of x,
        // a bit less that the current precision
        PR( print("   sub=",y,4); );
        PR( sqr(x,z);  z -= d;   print("x2_prec=",z,4);  long tap=-z.exp(); );
        PR( cout << "    pr=" << pr << "  ap=" << tap << "  diff=" << pr-tap << endl; );
            PR( jjassert( -z.exp() > (long)pr-25) ); // "Sqrt failed"


#if  ( THIRD_ORDER_SQRT==1 )
//#warning 'FYI: THIRD_ORDER_SQRT is set, fine.'
        // ---- IMPROVE Y (CORRECT FOR NEW X):
        // use 1/(x-y) = 1/x*(1+y/x-...) = v*(1+y*v-...) = v + y*v*v - ...
//        v.prec( pr );
        ulong p3 = 16;
        sqr(v, p3, tt, p3);         // v^2
        mul(y, p3, tt, p3, tt, 2*p3); // y*v^2
        add(v, tt, v);              // v = v + y*v*v = v*(1+v*y)
        PR( sqr(v,z);  z *= d;  z -= 1;  print("v+_prec=",z,4); );
        // here v should have half of the current precision

        // ---- IMPROVE X (THIRD ORDER TERM):
        sqr(y, p3, y, p3);         // (x*x-d)^2/(4*x^2) = y^2
        mul(y, p3, v, p3, y, p3);  // (x*x-d)^2/(4*x^3) = y^2/x
        div2(y, y);                // (x*x-d)^2/(8*x^3) = y^2/(2*x) == third order term
        sub(x, y, x);              // next x =  x - (x*x-d)/(2*x) - (x*x-d)^2/(2*x)^3
        // here x should have the current precision
        PR( print("   3rd=",y,4); );
        PR( sqr(x,z);  z -= d;   print("x3_prec=",z,4);  tap=-z.exp(); );
        PR( cout << "    pr=" << pr << "  ap=" << tap << "  diff=" << pr-tap << endl; );
#else  // THIRD_ORDER_SQRT
#warning  ' THIRD_ORDER_SQRT not set =--> LOSS OF PRECISION ! '
#endif  // THIRD_ORDER_SQRT

        ap =  -y.exp();  // jjnote: heuristic
        if ( hfverbosity::itprec )  cout << " (" << ap << "," << pr << ")\n";

        if ( pr>=rpg )  break;
    }
    jjassert( j != maxit );  // "sqrt_iteration(): no convergence"

    x.exp( x.exp()+xe/2 );  // exponent of result
    PR( print("x=",x,11); );
//    PR( sqr(x,y); y-=dd; print("x*x-d=",y,11); );


#if  ( CHECK_ITSQRT != 0 )
#warning 'CHECK_ITSQRT activated =--> sloooow '
    d.exp( xe );
    sqr(x,y);
    ulong dl;  cmp(d,y,dl);  dl = x.prec()-dl;
    if ( dl>15 )
    {
        cout << "sqrt(): limb-diff=" << dl << "  of " << x.prec() << endl;
        print("d=\n",d,11);
        print("x=\n",x,11);
        print("(sqrt())^2=\n",y,11);
        jjassert( 0 );
    }
#endif  // CHECK_ITSQRT


    if ( hfverbosity::itbegin )  cout << "}\n";

#ifdef  HF_PARANOIA
    jjassert( d.OK() );
    jjassert( x.OK() );
#endif

    return j;
}
// =================== end ================
