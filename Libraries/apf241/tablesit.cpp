#include "ap.h"


inline size_t min (size_t a, size_t b)
{
    return (a < b ? a : b);
}

// The "six-step" fnt, but doesn't transpose or scramble (for convolution only)

void tablesixstepfnttrans2 (modint data[], modint pr, int isign, size_t nn)
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
    size_t *ptable = new size_t[n1];

    if (isign > 0)
        w = pow (pr, modint::modulus - 1 - (modint::modulus - 1) / nn);
    else
        w = pow (pr, (modint::modulus - 1) / nn);

    // treat the input data as a n1 x n2 matrix

    // first transpose the matrix

    transpose (data, n1, n2);

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

    // last do n1 transforms of length n2

    // init table

    if (n2 != n1)
    {
        // n2 = 2 * n1
        for (k = n1; k--;)
            wtable[2 * k] = wtable[k];
        tmp = pow (w, nn / n2);
        tmp2 = tmp;
        tmp *= tmp;
        for (k = 1; k < n2; k += 2)
        {
            wtable[k] = tmp2;
            tmp2 *= tmp;
        }
    }

    for (k = 0, p1 = data; k < n1; k++, p1 += n2)
        tablefnt (p1, wtable, 0, n2, 0);

    delete[] ptable;
    delete[] wtable;
}

// 3-point WFTA
inline void fnt3 (modint &x0, modint &x1, modint &x2, modint &w1, modint &w2)
{
    modint t;

    t = x1 + x2;
    x2 = x1 - x2;
    x0 += t;
    t *= w1;
    x2 *= w2;
    t += x0;
    x1 = t + x2;
    x2 = t - x2;
}

void tablesixstepfnttrans (modint data[], modint pr, int isign, size_t nn)
{
    size_t n2 = (nn & -nn), j, k, s;
    modint w, ww, w1, w2, w3, *p1, *p2, *p3, tmp, tmp2, *d;

    if (nn < 2) return;

    if (nn == n2)
    {
        // Transform length is a power of two
        tablesixstepfnttrans2 (data, pr, isign, nn);
        return;
    }

    // Transform length is three times a power of two

    if (isign > 0)
        w = pow (pr, modint::modulus - 1 - (modint::modulus - 1) / nn);
    else
        w = pow (pr, (modint::modulus - 1) / nn);

    ww = w * w;

    w3 = pow (w, n2);                   // 3rd root of unity
    w1 = -modint (3) / modint (2);
    w2 = w3 + modint (1) / modint (2);

    s = min (n2, Cachemaxblocksize / 4);
    d = new modint[3 * s];

    tmp = tmp2 = 1;
    for (k = 0; k < n2; k += s)
    {
        p1 = d;
        p2 = p1 + s;
        p3 = p2 + s;
        moveraw (p1, data + k, s);                      // Cache in
        moveraw (p2, data + k + n2, s);
        moveraw (p3, data + k + 2 * n2, s);
        for (j = 0; j < s; j++, p1++, p2++, p3++)
        {
            fnt3 (*p1, *p2, *p3, w1, w2);               // Transform columns
            *p2 *= tmp;                                 // Multiply
            *p3 *= tmp2;
            tmp *= w;
            tmp2 *= ww;
        }
        p1 = d;
        p2 = p1 + s;
        p3 = p2 + s;
        moveraw (data + k, p1, s);                      // Cache out
        moveraw (data + k + n2, p2, s);
        moveraw (data + k + 2 * n2, p3, s);
    }

    delete[] d;

    tablesixstepfnttrans2 (data, pr, isign, n2);        // Transform rows
    tablesixstepfnttrans2 (data + n2, pr, isign, n2);
    tablesixstepfnttrans2 (data + 2 * n2, pr, isign, n2);
}

void itablesixstepfnttrans2 (modint data[], modint pr, int isign, size_t nn, size_t e)
{
    size_t n1, n2, j, k;
    modint w, tmp, tmp2, *p1, *p2, inn;

    if (nn < 2) return;

    for (n1 = 1, n2 = 0; n1 < nn; n1 <<= 1, n2++);
    n1 = n2 >> 1;
    n2 -= n1;

    n1 = 1 << n1;
    n2 = 1 << n2;

    // n2 >= n1

    modint *wtable = new modint[n2];
    size_t *ptable = new size_t[n1];

    if (isign > 0)
        w = pow (pr, modint::modulus - 1 - (modint::modulus - 1) / nn);
    else
        w = pow (pr, (modint::modulus - 1) / nn);

    // treat the input data as a n1 x n2 matrix

    // first do n1 transforms of length n2

    // init table

    tmp = pow (w, nn / n2);
    tmp2 = 1;
    for (k = 0; k < n2; k++)
    {
        wtable[k] = tmp2;
        tmp2 *= tmp;
    }

    for (k = 0, p1 = data; k < n1; k++, p1 += n2)
        itablefnt (p1, wtable, 0, n2, 0);

    // then multiply the matrix A_ij by exp(isign * -2 pi i j k / nn) / nn

    tmp = 1;
    inn = modint (1) / modint (nn * e);
    for (j = 0, p1 = data; j < n1; j++, p1 += n2)
    {
        tmp2 = pow (tmp, j) * inn;
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

    // transpose the matrix

    transpose (data, n1, n2);

    // then do n2 transforms of length n1

    // init table

    if (n2 != n1)
        // n2 = 2 * n1
        for (k = 0; k < n1; k++)
            wtable[k] = wtable[2 * k];

    initscrambletable (ptable, n1);

    for (k = 0, p1 = data; k < n2; k++, p1 += n1)
        itablefnt (p1, wtable, ptable, n1);

    // last transpose the matrix

    transpose (data, n2, n1);

    delete[] ptable;
    delete[] wtable;
}

void itablesixstepfnttrans (modint data[], modint pr, int isign, size_t nn)
{
    size_t n2 = (nn & -nn), j, k, s;
    modint w, ww, w1, w2, w3, *p1, *p2, *p3, tmp, tmp2, *d;

    if (nn < 2) return;

    if (nn == n2)
    {
        // Transform length is a power of two
        itablesixstepfnttrans2 (data, pr, isign, nn);
        return;
    }

    // Transform length is three times a power of two

    if (isign > 0)
        w = pow (pr, modint::modulus - 1 - (modint::modulus - 1) / nn);
    else
        w = pow (pr, (modint::modulus - 1) / nn);

    itablesixstepfnttrans2 (data, pr, isign, n2, 3);    // Transform rows
    itablesixstepfnttrans2 (data + n2, pr, isign, n2, 3);
    itablesixstepfnttrans2 (data + 2 * n2, pr, isign, n2, 3);

    ww = w * w;

    w3 = pow (w, n2);                   // 3rd root of unity
    w1 = -modint (3) / modint (2);
    w2 = w3 + modint (1) / modint (2);

    s = min (n2, Cachemaxblocksize / 4);
    d = new modint[3 * s];

    tmp = tmp2 = 1;
    for (k = 0; k < n2; k += s)
    {
        p1 = d;
        p2 = p1 + s;
        p3 = p2 + s;
        moveraw (p1, data + k, s);                      // Cache in
        moveraw (p2, data + k + n2, s);
        moveraw (p3, data + k + 2 * n2, s);
        for (j = 0; j < s; j++, p1++, p2++, p3++)
        {
            *p2 *= tmp;                                 // Multiply
            *p3 *= tmp2;
            tmp *= w;
            tmp2 *= ww;
            fnt3 (*p1, *p2, *p3, w1, w2);               // Transform columns
        }
        p1 = d;
        p2 = p1 + s;
        p3 = p2 + s;
        moveraw (data + k, p1, s);                      // Cache out
        moveraw (data + k + n2, p2, s);
        moveraw (data + k + 2 * n2, p3, s);
    }

    delete[] d;
}
