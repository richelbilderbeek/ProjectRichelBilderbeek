
#include <cmath>
#include <fxt/fxtio.h>
#include <fxt/jjassert.h>

#include "hfloat.h"
#include "hfverbosity.h"

#include <fxt/aux0/sign.h>  // Abs()


int get_arctan_formula(int m[], int arg [], int fno);
void print_arctan_formula(int m[], int arg [], int last);

int
pi_arctan(hfloat &p, int fno)
//
// compute \pi/4=\sum_{k=0}^{\infty}{m(k)*arctan(1/arg(k))}
//
// return how many terms where added
{
    if ( hfverbosity::piname )
        cout << "\n ===== PI_algorithm: " << __FUNCTION__ << "() ===== " << endl;

    long n = p.prec();

    int last;
    int i,k,maxk;
    int tt;
    long pnp = hfverbosity::pinumprec;
    ulong  ret = 0;
    hfloat a(n);   // term m*1/(arg^(2k+1))
    hfloat b(n);   // partial sum
    hfloat d(n);   // term m*1/((2k+1)*arg^(2k+1))
    hfloat bigarg(50);   // term m*1/((2k+1)*arg^(2k+1))
    int m[99], arg[99];

    last=get_arctan_formula(m,arg,fno);
    if ( hfverbosity::piname )  print_arctan_formula(m,arg,last);


    p = 0;
    for(i=0; i<=last; ++i) // =========== loop thru arctan terms
    {
        if ( hfverbosity::pistep )
            cout << "\n ----- term " << i << ": "
                 << m[i] << "*arctan(1/" << arg[i] << ") ----- "
                 << endl;

	maxk = (int)ceil((double)n*log((double)a.radix())/(2.0*log((double)arg[i])));
        ret += maxk;

	a = m[i];
	a /= arg[i];

	b = a;    // 0. arctan partial sum (term m/arg)

	for(k=1; k<=maxk; ++k)
	{
	    a /= arg[i];
	    a /= arg[i];

	    tt = (2*k+1)*((k&1)?-1:1);

	    d = a;
	    d /= tt;     // summand

	    b += d;      // partial sum
	}

        if ( hfverbosity::pinums )  print("\nterm=\n",b,pnp);
        p += b;
    }

    p *= 4;

    return (int)ret;
}
//========================== end PI_ARCTAN =======================



int
get_arctan_formula(int m[], int arg [], int fno)
{
    fno %= 10;

    if ( (fno<2) || (fno>7) )  fno=4;

    switch ( fno )
    {
	case 2:
	{
	    m[ 0]=+4; arg[ 0]=5;
	    m[ 1]=-1; arg[ 1]=239;
	    return 1;
	}
	
	case 3:
	{
	    m[ 0]=+12;  arg[ 0]=18;
	    m[ 1]=+8;   arg[ 1]=57;
	    m[ 2]=-5;   arg[ 2]=239;
	    return 2;
	}
	
	case 4:
	{
	    m[ 0]=+44; arg[ 0]=57;
	    m[ 1]=+7;  arg[ 1]=239;
	    m[ 2]=-12; arg[ 2]=682;
	    m[ 3]=+24; arg[ 3]=12943;
	    return 3;
	}
	
	case 5:
	{
	    m[ 0]=+88;  arg[ 0]=192;
	    m[ 1]=+39;  arg[ 1]=239;
	    m[ 2]=+100; arg[ 2]=515;
	    m[ 3]=-32;  arg[ 3]=1068;
	    m[ 4]=-56;  arg[ 4]=173932;
	    return 4;
	}
	
	case 6:
	{
	    m[ 0]=322; arg[ 0]=577;
	    m[ 1]=76;  arg[ 1]=682;
	    m[ 2]=139; arg[ 2]=1393;
	    m[ 3]=156; arg[ 3]=12943;
	    m[ 4]=132; arg[ 4]=32807;
	    m[ 5]=44;  arg[ 5]=1049433;
	    return 5;
	}
	
	case 7:
	{
	    m[ 0]=+1587;  arg[ 0]=2852;
	    m[ 1]=+295;   arg[ 1]=4193;
	    m[ 2]=+593;   arg[ 2]=4246;
	    m[ 3]=+359;   arg[ 3]=39307;
	    m[ 4]=+481;   arg[ 4]=55603;
	    m[ 5]=+625;   arg[ 5]=211050;
	    m[ 6]=-708;   arg[ 6]=390112;
	    return 6;
	}
	
	case 11:
	{
	    m[ 0]=+36462; arg[ 0]=390112;
	    m[ 1]=+135908;arg[ 1]=485298;
	    m[ 2]=+274509;arg[ 2]=683982;
	    m[ 3]=-39581; arg[ 3]=1984933;
	    m[ 4]=+178477;arg[ 4]=2478328;
	    m[ 5]=-114569;arg[ 5]=3449051;
	    m[ 6]=-146571;arg[ 6]=18975991;
	    m[ 7]=+61914; arg[ 7]=22709274;
	    m[ 8]=-69044; arg[ 8]=24208144;
	    m[ 9]=-89431; arg[ 9]=201229582;
	
	    m[10]=-43938; arg[10]=0; // 2189376182 > MAXINT !!
	    //char arg10[]="+.002189376182*10000^+3";
	    return 10;
	}
    }

    return -1;
}
//================= end GET_ARCTAN_FORMULA ==================


void
print_arctan_formula(int m[], int arg [], int last)
{
    cout << "\n Pi/4 = ";

    for (int i=0; i<=last; ++i)
    {
        cout << " " << (m[i]>0?'+':'-')
             << Abs(m[i]) <<"*arctan(1/"
             << arg[i] << ")";
    }

    cout << endl;
}
//================= end PRINT_ARCTAN_FORMULA ==================
