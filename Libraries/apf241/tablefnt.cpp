#include "ap.h"


// Optimized fnt using table lookup for the powers of W

void tablefnt (modint data[], modint wtable[], size_t ptable[], size_t nn, int s)
{
    size_t m, i, j, istep, mmax, t, r;
    modint a, b;

    if (nn < 2) return;

    r = 1;
    mmax = nn >> 1;
    while (mmax)
    {
        istep = mmax << 1;

        // Optimize first step when wr = 1

        for (i = 0; i < nn; i += istep)
        {
            j = i + mmax;
            a = data[i];
            b = data[j];
            data[i] = a + b;
            data[j] = a - b;
        }
        t = r;

        for (m = 1; m < mmax; m++)
        {
            for (i = m; i < nn; i += istep)
            {
                j = i + mmax;
                a = data[i];
                b = data[j];
                data[i] = a + b;
                data[j] = wtable[t] * (a - b);
            }
            t += r;
        }
        r <<= 1;
        mmax >>= 1;
    }

    if (s) tablescramble (data, ptable);
}


void itablefnt (modint data[], modint wtable[], size_t ptable[], size_t nn, int s)
{
    size_t m, i, j, istep, mmax, t, r;
    modint wtemp;

    if (nn < 2) return;

    if (s) tablescramble (data, ptable);

    r = nn;
    mmax = 1;
    while (nn > mmax)
    {
        istep = mmax << 1;
        r >>= 1;

        // Optimize first step when w = 1

        for (i = 0; i < nn; i += istep)
        {
            j = i + mmax;
            wtemp = data[j];
            data[j] = data[i] - wtemp;
            data[i] += wtemp;
        }

        t = r;

        for (m = 1; m < mmax; m++)
        {
            for (i = m; i < nn; i += istep)
            {
                j = i + mmax;
                wtemp = wtable[t] * data[j];
                data[j] = data[i] - wtemp;
                data[i] += wtemp;
            }
            t += r;
        }
        mmax = istep;
    }
}
