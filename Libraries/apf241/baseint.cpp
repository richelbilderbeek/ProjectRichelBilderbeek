#include "ap.h"


// The baseint functions
// Baseints are basically bigints, but the base is not the rawtype maximum, but Base

// Adds n words from s to d, returns overflow carry bit
rawtype baseadd (rawtype *dest, rawtype *src1, rawtype *src2, size_t len, rawtype carry)
{
    size_t t;

    for (t = len; t--;)
    {
        dest[t] = src1[t];
        bigadd (dest + t, &carry, 1);
        if ((src2 && bigadd (dest + t, src2 + t, 1) != 0) ||
            bigcmp (dest + t, &Base, 1) >= 0)
        {
            bigsub (dest + t, &Base, 1);
            carry = 1;
        }
        else
        {
            carry = 0;
        }
    }

    return carry;
}

// Subtracts n words s from d, returns subtract carry bit (1)
rawtype basesub (rawtype *dest, rawtype *src1, rawtype *src2, size_t len, rawtype carry)
{
    size_t t;
    rawtype tmp;

    for (t = len; t--;)
    {
        dest[t] = (src1 ? src1[t] : 0);
        tmp = (src2 ? src2[t] : 0);
        bigadd (&tmp, &carry, 1);
        if (bigsub (dest + t, &tmp, 1) != 0)
        {
            bigadd (dest + t, &Base, 1);
            carry = 1;
        }
        else
        {
            carry = 0;
        }
    }

    return carry;
}

// Multiplicates n words in s by f, adds s2, stores result to d, returns overflow word
rawtype basemuladd (rawtype *dest, rawtype *src1, rawtype *src2, rawtype src3, size_t len, rawtype carry)
{
    size_t t;
    rawtype tmp[2], tmpcarry[2];

    tmpcarry[0] = carry;
    tmpcarry[1] = 0;

    for (t = len; t--;)
    {
        tmp[1] = bigmul (tmp, src1 + t, src3, 1);
        bigadd (tmp, tmpcarry, 1, 1);
        if (src2) bigadd (tmp, src2 + t, 1, 1);
        dest[t] = bigdiv (tmpcarry, tmp, Base, 2);
    }

    return tmpcarry[0];
}

// Divides n words in s by f, stores result in d, returns remainder
rawtype basediv (rawtype *dest, rawtype *src1, rawtype src2, size_t len, rawtype carry)
{
    size_t t;
    rawtype tmp[2];

    for (t = 0; t < len; t++)
    {
        tmp[1] = bigmul (tmp, &carry, Base, 1);
        if (src1) bigadd (tmp, src1 + t, 1, 1);
        carry = bigdiv (tmp, tmp, src2, 2);
        dest[t] = tmp[0];
    }

    return carry;
}
