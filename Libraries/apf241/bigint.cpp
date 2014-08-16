#include "ap.h"


// The bigint functions
// Bigints are simply arrays of unsigned integers, they can be seen as
// base-2^32 numbers. Arithmetic on them is quite fast.
// The least significant word is stored first.

// Adds n words from s to d, returns overflow carry bit
rawtype bigadd (rawtype *d, rawtype *s, size_t n, size_t c)
{
    size_t t;
    rawtype r, b = 0;

    for (t = 0; t < n; t++)
    {
        r = *d + b;

        if (r < *d) b = 1;              // Bug found by Alexis Wilke
        else b = 0;

        r += *s;

        if (r < *s) b = 1;

        *d = r;

        d++;
        s++;
    }

    for (t = 0; b && t < c; t++)
    {
        if (++(*d)) b = 0;

        d++;
    }

    return b;
}

// Subtracts n words s from d, returns subtract carry bit (1)
rawtype bigsub (rawtype *d, rawtype *s, size_t n, size_t c)
{
    size_t t;
    rawtype r, b = 0;

    for (t = 0; t < n; t++)
    {
        r = *d - b;

        if (r > *d) b = 1;              // Bug found by Alexis Wilke
        else b = 0;

        *d = r - *s;

        if (*d > r) b = 1;

        d++;
        s++;
    }

    for (t = 0; b && t < c; t++)
    {
        if (--(*d) != (rawtype) -1) b = 0;

        d++;
    }

    return b;
}

// Multiplicates n words in s by f, stores result in d, returns overflow word
rawtype bigmul (rawtype *d, rawtype *s, rawtype f, size_t n)
{
    size_t t;
    rawtype b = 0;
    unsigned long long r;

    for (t = 0; t < n; t++)
    {
        r = (unsigned long long) *s * f + b;

        *d = r;

        b = r >> 32;

        d++;
        s++;
    }

    return b;
}

// Divides n words in s by f, stores result in d, returns remainder
rawtype bigdiv (rawtype *d, rawtype *s, rawtype f, size_t n)
{
    size_t t;
    rawtype b;
    unsigned long long r;

    if (!n) return 0;

    d += n;
    s += n;

    if ((b = *(s - 1)) < f)
    {
        d--;
        s--;
        n--;
        *d = 0;
    }
    else b = 0;

    for (t = 0; t < n; t++)
    {
        d--;
        s--;

        r = ((unsigned long long) b << 32) + *s;

        *d = r / f;

        b = (rawtype) r - *d * f;                               // b = r % f;
    }

    return b;
}

// Shifts s right one bit to d, returns carry bit
int bigshr (rawtype *d, rawtype *s, size_t n)
{
    size_t t;
    rawtype tmp;
    int b = 0;

    if (!n) return 0;

    d += n;
    s += n;

    for (t = 0; t < n; t++)
    {
        d--;
        s--;

        tmp = (*s >> 1) + (b ? 0x80000000 : 0);
        b = *s & 1;
        *d = tmp;                               // Works also if d = s
    }

    return b;
}

// Compares n words, returns -1 if d < s, 1 if d > s, 0 if d == s
int bigcmp (rawtype *d, rawtype *s, size_t n)
{
    size_t t;

    d += n - 1;
    s += n - 1;

    for (t = 0; t < n; t++)
    {
        if (*d < *s) return -1;
        if (*d > *s) return 1;

        d--;
        s--;
    }

    return 0;
}
