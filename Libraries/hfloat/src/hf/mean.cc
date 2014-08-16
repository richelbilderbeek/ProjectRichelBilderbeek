
#include <fxt/fxtio.h>

#include "hfloat.h"
#include "hfverbosity.h"


int
agm1(const hfloat &b, hfloat &x)
//  compute AGM(1,b)
{
    static hfloat one(1);  // jjnote: static hfloat
    one = 1;
    return agm(one, b, x);
}
//======================= end ======================


int
agm(const hfloat &a, const hfloat &b, hfloat &x)
//
// arithmetic_geometric_mean
//
// AGM(a,b):=
// common limit after repeated application of
// {x, y}  |-->  {(x+y)/2, sqrt(x*y)}
// starting with {a,b}
//
// returns number of steps needed
//
{
    if ( hfverbosity::meanname )
        cout << "\n ===== " << __FUNCTION__ << endl;

    hfloat ak(x.prec()), bk(x.prec());

    const ulong precgoal = x.prec();
//    if ( a.prec()<precgoal )  precgoal = a.prec();
//    if ( b.prec()<precgoal )  precgoal = b.prec();

    const long mnp = hfverbosity::meanprec;
    if ( hfverbosity::meannums )
    {
        print("\nA_0= ", a, mnp);
        print("B_0= ", b, mnp);
    }

    // ---- first step:
    add(a, b, ak);
    div2(ak, ak);  // ak = (a+b)/2
    mul(a, b, bk);
    sqrt(bk, bk);  // bk = sqrt(a*b)

    ulong prec = agree_prec(ak, bk, x);

    if ( hfverbosity::meannums )
    {
        print("\nA_1= ",ak,mnp);
        print("B_1= ",bk,mnp);
        cout << "prec_1= " << prec << endl;
    }

    // ---- more steps:
    int k = 1;
    while ( prec<precgoal/2 )
    {
        k++;
        add(ak, bk, x);   // a+b == x
	mul(ak, bk, bk);  // a*b
	sqrt(bk, bk);    // bk == b_new = sqrt(a*b)
	div2(x, ak);     // ak == a_new = (a+b)/2

        prec = agree_prec(ak, bk, x);

        if ( hfverbosity::meannums )
        {
            print("\nA_k= ", ak, mnp);
            print("B_k= ", bk, mnp);
            cout << "prec_k= " << prec << endl;
        }

    }

    add(ak, bk, ak);
    div2(ak, x);  // x = (a+b)/2

    return  k;
}
//======================= end ======================



int
hgm(const hfloat &a, const hfloat &b, hfloat &x)
//
// harmonic_geometric_mean
//
// HGM(a,b):=
// common limit after repeated application of
// {x,y} |--> {2*x*y/(x+y),sqrt(x*y)}
// starting with {a,b}
//
// HGM(1,n)=2/Pi*log(4*n)+O(1/n^2)
//
// if y:=(x^n)/4
// then
// n*y*(HGM(1,y+1)/HGM(1,y)-1)=1/log(x)+O(n/3^n)
// and
// n*(HGM(1,n+1)-HGM(1,n))=2/Pi+O(1/n)
//
// HGM(a,b)=a*b/agm(a,b)
//
// see: newman: a simplified version ...,
//       math. comp. (44) 1985 pp.207-210
//
// returns number of steps needed
//
{
    if ( hfverbosity::meanname )
        cout << "\n ===== " << __FUNCTION__ << endl;

    hfloat ak(x.prec());

    mul(a, b, ak);

    int  ret = agm(a, b, x);

    div(ak, x, x);

    return ret;
}
//======================= end ======================



int
j_mean(const hfloat &a, const hfloat &b, hfloat &x)
//
// j_mean :=
// common limit after repeated application of
// {x, y}  |-->  {(x+y)/2, sqrt((x*x+y*y)/2)}
// starting with {a,b}
//
// returns number of steps needed
//
{
    if ( hfverbosity::meanname )
        cout << "\n ===== " << __FUNCTION__ << endl;

    hfloat ak(x.prec()), bk(x.prec()), tk(x.prec());

    const ulong precgoal = x.prec();
//    if ( a.prec()<precgoal )  precgoal=a.prec();
//    if ( b.prec()<precgoal )  precgoal=b.prec();

    const long mnp = hfverbosity::meanprec;
    if ( hfverbosity::meannums )
    {
        print("\nA_0= ", a, mnp);
        print("B_0= ", b, mnp);
    }

    // ---- first step:
    sqr(a, tk);
    sqr(b, bk);
    add(ak, tk, bk);
    div2(bk, bk);
    tk = bk;
    sqrt(bk, bk);  // sqrt((a^2+b^2)/2)

    add(a, b, ak);
    div2(ak, ak); // (a+b)/2

    ulong prec = agree_prec(ak, bk, x);

    if ( hfverbosity::meannums )
    {
        print("\nA_1= ", ak, mnp);
        print("B_1= ", bk, mnp);
        cout << "prec= " << prec << endl;
    }

    // ---- more steps:
    int k=1;
    while ( prec<precgoal/2 )
    {
        k++;
        sqr(ak, x);
        add(ak, bk, ak);
	div2(ak, ak); // a_new = (a+b)/2
	bk = tk;
        add(x, bk, bk);
        div2(bk, bk);
        tk = bk;
	sqrt(bk, bk);    // b_new = sqrt((a^2+b^2)/2)

        prec = agree_prec(ak, bk, x);

        if ( hfverbosity::meannums )
        {
            print("\nA_k= ", ak, mnp);
            print("B_k= ", bk, mnp);
            cout << "prec= " << prec << endl;
        }
    }

    add(ak, bk, ak);
    div2(ak, x);    // (a+b)/2

    return k;
}
//======================= end ======================

