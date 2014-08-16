#include "ap.h"


// Un-optimized basic fnt functions

void fnt (modint data[], modint pr, int isign, size_t nn, int s)
{
    size_t m, i, j, istep, mmax;
    modint w, z, a, b;

    if (nn < 2) return;

    if (isign > 0)
        w = pow (pr, modint::modulus - 1 - (modint::modulus - 1) / nn);
    else
        w = pow (pr, (modint::modulus - 1) / nn);

    mmax = nn >> 1;
    while (mmax)
    {
        istep = mmax << 1;

        // Optimize first step when z = 1

        for (i = 0; i < nn; i += istep)
        {
            j = i + mmax;
            a = data[i];
            b = data[j];
            data[i] = a + b;
            data[j] = a - b;
        }
        z = w;

        for (m = 1; m < mmax; m++)
        {
            for (i = m; i < nn; i += istep)
            {
                j = i + mmax;
                a = data[i];
                b = data[j];
                data[i] = a + b;
                data[j] = z * (a - b);
            }
            z *= w;
        }
        w *= w;
        mmax >>= 1;
    }

    if (s) scramble (data, nn);
}


void ifnt (modint data[], modint pr, int isign, size_t nn, int s)
{
    size_t m, i, j, istep, mmax;
    modint w, wt, wr, wtemp;

    if (nn < 2) return;

    if (isign > 0)
        w = pow (pr, modint::modulus - 1 - (modint::modulus - 1) / nn);
    else
        w = pow (pr, (modint::modulus - 1) / nn);

    if (s) scramble (data, nn);

    mmax = 1;
    while (nn > mmax)
    {
        istep = mmax << 1;
        wr = wt = pow (w, nn / istep);

        // Optimize first step when wr = 1

        for (i = 0; i < nn; i += istep)
        {
            j = i + mmax;
            wtemp = data[j];
            data[j] = data[i] - wtemp;
            data[i] += wtemp;
        }

        for (m = 1; m < mmax; m++)
        {
            for (i = m; i < nn; i += istep)
            {
                j = i + mmax;
                wtemp = wr * data[j];
                data[j] = data[i] - wtemp;
                data[i] += wtemp;
            }
            wr *= wt;
        }
        mmax = istep;
    }
}
