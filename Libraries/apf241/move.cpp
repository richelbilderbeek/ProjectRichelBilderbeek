#include "ap.h"


// Optimized routines for moving big blocks of data

void moveraw (void *d, void *s, size_t n)
{
    rawtype *dd, *ss;

    dd = (rawtype *) d;
    ss = (rawtype *) s;

    while (n--)
        *(dd++) = *(ss++);
}

void swapraw (void *d, void *s, size_t n)
{
    rawtype tmp, *dd, *ss;

    dd = (rawtype *) d;
    ss = (rawtype *) s;

    while (n--)
    {
        tmp = *dd;
        *(dd++) = *ss;
        *(ss++) = tmp;
    }
}
