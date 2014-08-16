#include "ap.h"


// Optimized "six-step" fnt function using table lookups for the powers of W

void tablesixstepfnt (modint data[], modint pr, int isign, size_t nn, int t)
{
    size_t n1, n2, j, k;
    modint w, tmp, tmp2, *p1, *p2;

    if (nn < 2) return;

    for (n1 = 1, n2 = 0; n1 < nn; n1 <<= 1, n2++);
    n1 = n2 >> 1;
    n2 -= n1;

    n1 = 1 << n1;
    n2 = 1 << n2;

    // n2 >= n1

    modint *wtable = new modint[n2];
    size_t *ptable = new size_t[n2];

    if (isign > 0)
        w = pow (pr, modint::modulus - 1 - (modint::modulus - 1) / nn);
    else
        w = pow (pr, (modint::modulus - 1) / nn);

    // treat the input data as a n1 x n2 matrix

    // first transpose the matrix

    if (t & 1) transpose (data, n1, n2);

    // then do n2 transforms of length n1

    // init tables

    tmp = pow (w, nn / n1);
    tmp2 = 1;
    for (k = 0; k < n1; k++)
    {
        wtable[k] = tmp2;
        tmp2 *= tmp;
    }

    initscrambletable (ptable, n1);

    for (k = 0, p1 = data; k < n2; k++, p1 += n1)
        tablefnt (p1, wtable, ptable, n1);

    // transpose the matrix

    transpose (data, n2, n1);

    // then multiply the matrix A_ij by exp(isign * -2 pi i j k / nn)

    tmp = w;
    for (j = 1, p1 = data + n2; j < n1; j++, p1 += n2)
    {
        tmp2 = pow (tmp, j);
        p1[j] *= tmp2;
        for (k = j + 1, p2 = p1 + n2 + j; k < n1; k++, p2 += n2)
        {
            tmp2 *= tmp;
            p1[k] *= tmp2;
            *p2 *= tmp2;
        }
        for (; k < n2; k++)
        {
            tmp2 *= tmp;
            p1[k] *= tmp2;
        }
        tmp *= w;
    }

    // then do n1 transforms of length n2

    // init table

    if (n2 != n1)
    {
        tmp = pow (w, nn / n2);
        tmp2 = 1;
        for (k = 0; k < n2; k++)
        {
            wtable[k] = tmp2;
            tmp2 *= tmp;
        }

        initscrambletable (ptable, n2);
    }

    for (k = 0, p1 = data; k < n1; k++, p1 += n2)
        tablefnt (p1, wtable, ptable, n2);

    // last transpose the matrix

    if (t & 2) transpose (data, n1, n2);

    delete[] ptable;
    delete[] wtable;
}

void itablesixstepfnt (modint data[], modint pr, int isign, size_t nn, int t)
{
    size_t n1, n2, j, k;
    modint w, tmp, tmp2, *p1, *p2;

    if (nn < 2) return;

    for (n1 = 1, n2 = 0; n1 < nn; n1 <<= 1, n2++);
    n1 = n2 >> 1;
    n2 -= n1;

    n1 = 1 << n1;
    n2 = 1 << n2;

    // n2 >= n1

    modint *wtable = new modint[n2];
    size_t *ptable = new size_t[n2];

    if (isign > 0)
        w = pow (pr, modint::modulus - 1 - (modint::modulus - 1) / nn);
    else
        w = pow (pr, (modint::modulus - 1) / nn);

    // treat the input data as a n1 x n2 matrix

    // first transpose the matrix

    if (t & 1) transpose (data, n1, n2);

    // then do n2 transforms of length n1

    // init table

    tmp = pow (w, nn / n1);
    tmp2 = 1;
    for (k = 0; k < n1; k++)
    {
        wtable[k] = tmp2;
        tmp2 *= tmp;
    }

    initscrambletable (ptable, n1);

    for (k = 0, p1 = data; k < n2; k++, p1 += n1)
        itablefnt (p1, wtable, ptable, n1);

    // transpose the matrix

    transpose (data, n2, n1);

    // then multiply the matrix A_ij by exp(isign * -2 pi i j k / nn)

    tmp = w;
    for (j = 1, p1 = data + n2; j < n1; j++, p1 += n2)
    {
        tmp2 = pow (tmp, j);
        p1[j] *= tmp2;
        for (k = j + 1, p2 = p1 + n2 + j; k < n1; k++, p2 += n2)
        {
            tmp2 *= tmp;
            p1[k] *= tmp2;
            *p2 *= tmp2;
        }
        for (; k < n2; k++)
        {
            tmp2 *= tmp;
            p1[k] *= tmp2;
        }
        tmp *= w;
    }

    // then do n1 transforms of length n2

    // init table

    if (n2 != n1)
    {
        tmp = pow (w, nn / n2);
        tmp2 = 1;
        for (k = 0; k < n2; k++)
        {
            wtable[k] = tmp2;
            tmp2 *= tmp;
        }

        initscrambletable (ptable, n2);
    }

    for (k = 0, p1 = data; k < n1; k++, p1 += n2)
        itablefnt (p1, wtable, ptable, n2);

    // last transpose the matrix

    if (t & 2) transpose (data, n1, n2);

    delete[] ptable;
    delete[] wtable;
}
