#include "ap.h"


// Functions to perform bit-reverse ordering of data

size_t permute (size_t n, size_t nn)
{
    size_t p = 1;

    do
    {
        p += p + (n & 1);
        n >>= 1;
    } while (p < nn);

    return p - nn;
}

void scramble (modint data[], size_t nn)
{
    size_t i, j;
    modint tmp;

    for (i = 0; i < nn; i++)
    {
        j = permute (i, nn);
        if (j < i)
        {
            tmp = data[i];
            data[i] = data[j];
            data[j] = tmp;
        }
    }
}

void initscrambletable (size_t ptable[], size_t nn)
{
    size_t i, j, k;

    for (i = k = 0; i < nn; i++)
    {
        j = permute (i, nn);
        if (j < i)
        {
            ptable[k] = i;
            ptable[k + 1] = j;
            k += 2;
        }
    }

    ptable[k] = ptable[k + 1] = 0;      // Table end marker
}

void tablescramble (modint data[], size_t ptable[])
{
    size_t i, j, k = 0;
    modint tmp;

    while ((i = ptable[k]) != (j = ptable[k + 1]))
    {
        tmp = data[i];
        data[i] = data[j];
        data[j] = tmp;
        k += 2;
    }
}
