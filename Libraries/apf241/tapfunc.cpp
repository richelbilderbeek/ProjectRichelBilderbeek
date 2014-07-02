#include "ap.h"
#include "tapfloat.h"


// Overloaded tapfloat functions

// Positive integer power
apfloat pow (tapfloat base, unsigned long exp)
{
    int d = 0;
    apfloat b, r;

    if (!exp) return 1;

    if (!(exp & 1))
    {
        b = base * base;
        exp >>= 1;
        d = 1;
    }
    else
    {
        b = 1 * base;
    }

    while (!(exp & 1))
    {
        b *= b;
        exp >>= 1;
        d = 1;
    }
    r = b;

   if (exp >> 1 && d) base = transform (b);

    while (exp >>= 1)
    {
        b = base * base;
        base = transform (b);
        if (exp & 1) r = r * base;
    }

    return r;
}

apfloat pow (tapfloat base, unsigned exp)
{
    return pow (base, (unsigned long) exp);
}

// Integer power
apfloat pow (tapfloat base, long exp)
{
    if (exp < 0)
        return invroot (pow (base, (unsigned long) -exp), 1);
    else
        return pow (base, (unsigned long) exp);
}

apfloat pow (tapfloat base, int exp)
{
    if (exp < 0)
        return invroot (pow (base, (unsigned long) -exp), 1);
    else
        return pow (base, (unsigned long) exp);
}
