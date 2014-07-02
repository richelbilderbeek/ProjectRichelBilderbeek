#include "ap.h"
#include "aprat.h"


// Overloaded aprational functions

// Positive integer power
// Algorithm improvements by Bernd Kellner
aprational pow (aprational base, unsigned long exp)
{
    aprational r;
    int b2pow = 0;

    if (!exp) return 1;

    while (!(exp & 1))
    {
        b2pow++;
        exp >>= 1;
    }
    r = base;

    while (exp >>= 1)
    {
        base *= base;
        if (exp & 1) r *= base;
    }

    while (b2pow--)
        r *= r;

    return r;
}

aprational pow (aprational base, unsigned exp)
{
    return pow (base, (unsigned long) exp);
}

// Integer power
aprational pow (aprational base, long exp)
{
    if (exp < 0)
        return 1 / pow (base, (unsigned long) -exp);
    else
        return pow (base, (unsigned long) exp);
}

aprational pow (aprational base, int exp)
{
    if (exp < 0)
        return 1 / pow (base, (unsigned long) -exp);
    else
        return pow (base, (unsigned long) exp);
}
