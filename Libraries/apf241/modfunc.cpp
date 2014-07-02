#include "ap.h"


// Overloaded modint power
// Uses standard O(log exp) scheme
// For extreme portability this quite slow, so avoid whenever possible
modint pow (modint base, rawtype exp)
{
    modint r;

    if (exp == 0) return 1;

    while (!bigshr (&exp, &exp, 1))
        base *= base;

    r = base;

    while (exp > 0)
    {
        base *= base;
        if (bigshr (&exp, &exp, 1)) r *= base;
    }

    return r;
}
