#include "nrrand.h"

#include <cmath>
/************************************************************
RANDOM NUMBER GENERATOR WRAPPER OBJECT
************************************************************/
// constructor
NRrand::NRrand()
{
    normflag = true;
}
// setter for seed
void NRrand::set_seed(long seed)
{
    X.set_seed(seed);
}
// returns a uniform random number in (0,1)
double NRrand::d01()
{
    return X.d01();
}
// returns an integer between 0 and max
long NRrand::i0(long max)
{
    return (long(floor(d01()*(max+1))));
}
// returns normal deviates
double NRrand::norm()
{
    if (normflag)
    {
        double r2 = 2;
        double xx;double yy;
        while (r2>1)
        {
            xx=2.0*d01()-1.0;
            yy=2.0*d01()-1.0;
            r2=(xx*xx)+(yy*yy);
        }
        double fac=sqrt(-2.0*log(r2)/r2);
        lastresult = xx*fac;
        double result = yy*fac;
        normflag = false;
        return result;
    }
    else
    {
        normflag = true;
        return lastresult;
    }
}
