
#include <cmath>
#include <fxt/fxtio.h>
#include <fxt/jjassert.h>

#include "hfloat.h"
#include "hfverbosity.h"


//#define CORRECT_DEC_LIMBS(k) (1<<(k+1))  // see borwein^2 p.47 formula 2.5.3
//#define REQ_ITERATIONS (int)ceil(log(LOG10RADIX*n)/log(2.0)-1)

#define DECIMAL_PREC(n)  ((int)(floor((double)n*LOG10(hfdata::rx))))


int
pi_derived_agm(hfloat &p)
//
// derived agm iteration for pi
//
// return number of iterations needed
{
    if ( hfverbosity::piname )
        cout << "\n ===== PI_algorithm: " << __FUNCTION__ << "() ===== " << endl;

    long n = p.prec();

    long prec;
    long pnp = hfverbosity::pinumprec;
    hfloat a(n), x(n), y(n);
    hfloat isx(n), sx(n), iy1(n);

    // X_0:
    sqrt(2,x);       // x = sqrt(2)
    if ( hfverbosity::pinums )  print("\nX_0=\n",x,pnp);

    // Y_1:
    sqrt(x,y);       // y = sqrt(sqrt(2))
    if ( hfverbosity::pinums )  print("\nY_1=\n",y,pnp);

    // PI_0:
    add(x,(ulong)2,p); // pi = 2+sqrt(2)
    if ( hfverbosity::pinums )  print("\nPI_0=\n",p,pnp);

    // X_1:
    isqrt(x,isx);    // isx = 1/sqrt(x)
    mul(isx,x,sx);   // sx = sqrt(x)
    add(sx,isx,a);   // a = sqrt(x)+1/sqrt(x)
    div(a,(ulong)2,x); // (new) x = (sqrt(x)+1/sqrt(x))/2
    if ( hfverbosity::pinums )  print("\nX_1=\n",x,pnp);

    // PI_1:
    add(y,(ulong)1,a);  // a = y+1
    inv(a,iy1);         // iy1 = 1/(1+y)
    add(x,(ulong)1,a);  // a = x+1
    a *= iy1;           // a = (x+1)/(y+1)

    p *= a;            // (new) pi = pi*(x+1)/(y+1)
    if ( hfverbosity::pinums )  print("\nPI_1=\n",p,pnp);

    int k;
    for (k=2; ; ++k)
    {
        if ( hfverbosity::pistep )
            cout << "\n ----- step " << k << ": ----- " << endl;

	// X_k:
	isqrt(x,isx);           // isx = 1/sqrt(x)
	mul(isx,x,sx);          // sx = sqrt(x)
	add(sx,isx,a);          // a = sqrt(x)+1/sqrt(x)
	div(a,(ulong)2,x);      // (new) x = (sqrt(x)+1/sqrt(x))/2
        if ( hfverbosity::pinums )
        {
            print("\nX_k=\n",x,pnp);
        }

	// Y_k:
	mul(y,sx,a);            // a = y*sqrt(x)
	add(a,isx,a);           // a = (y*sqrt(x)+1/sqrt(x))
	mul(a,iy1,y);           // (new) y = (y*sqrt(x)+1/sqrt(x))/(y+1)
        if ( hfverbosity::pinums )
        {
            print("\nY_k=\n",y,pnp);
        }

	// PI_k:
        add(y,(ulong)1,a);        // a = y+1
	inv(a,iy1);               // iy1 = 1/(1+y)
        add(x,(ulong)1,a);        // a = y+1
	a *= iy1;                 // a = (x+1)/(y+1)
	prec = 2*cmp1(a);         // precision
        if ( hfverbosity::piprec )
            cout << "\n precision=" << prec << endl;

	p *= a;                   // (new) pi = pi*(x+1)/(y+1)
        if ( hfverbosity::pinums )  print("\nPI_k=\n",p,pnp);

	if( prec>=n )  break;
    }

    return k;
}
//================ end PI_DERIVED_AGM ==========================
