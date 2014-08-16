
#include "hfloat.h"
#include <fxt/jjassert.h>

//
// jjnote: stuff here only LITTLE TESTED !
//

void
acosh(const hfloat &a, hfloat &b)
{
    long  c1 = cmp1(a);

    if ( c1==0 )
    {
	b = 0;
    }
    else
    {
        jjassert( c1 >= 0 ); // " acosh(x) for x<1 "

	hfloat x(b.prec());  // jjnote: temporary hfloat
	x = a;

	sqr(a,b);
	b -= 1;
	sqrt(b,b);
	x += b;
	log(x,b);  // log(x+sqrt(x^2-1))
    }
}
// =========== end ============


void
asinh(const hfloat &a, hfloat &b)
{
    hfloat x(b.prec());  // jjnote: temporary hfloat
    x = a;

    sqr(a,b);
    b += 1;
    sqrt(b,b);
    x += b;
    log(x,b);  // log(x+sqrt(x^2+1))
}
// =========== end ============




void
exp(const hfloat &a, hfloat &b)
{
    exp_iteration(a,b);
}
// =========== end ============


void
cosh(const hfloat &a, hfloat &b)
{
    exp(a,b);

    hfloat x(b.prec());  // jjnote: temporary hfloat
    inv(b,x);
    b += x;
    b /= 2;
}
// =========== end ============


void
sinh(const hfloat &a, hfloat &b)
{
    exp(a,b);

    hfloat x(b.prec());  // jjnote: temporary hfloat
    inv(b,x);
    b -= x;
    b /= 2;
}
// =========== end ============
