#include "ap.h"


// The "six-step" ntt using wfta, but doesn't transpose or scramble (for convolution only)
void sixstepwftatrans (modint data[], modint *w[], modint pr, int isign, int n1, int n2)
{
    int j, k;
    modint wt, tmp, tmp2, *p1, *p2;

    if (isign > 0)
        wt = pow (pr, modint::modulus - 1 - (modint::modulus - 1) / (n1 * n2));
    else
        wt = pow (pr, (modint::modulus - 1) / (n1 * n2));

    modint *b = new modint[n1];

    // treat the input data as a n1 x n2 matrix

    // first do n2 transforms of length n1 in columns

    for (k = 0, p1 = data; k < n2; k++, p1++)
    {
        for (j = 0, p2 = p1; j < n1; j++, p2 += n2)
            b[j] = *p2;

        wfta (b, w, n1);

        for (j = 0, p2 = p1; j < n1; j++, p2 += n2)
            *p2 = b[j];
    }

    // then multiply the matrix A_ij by exp(isign * -2 pi i j k / nn)

    tmp = wt;
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
        tmp *= wt;
    }

    // last do n1 transforms of length n2 in rows

    for (k = 0, p1 = data; k < n1; k++, p1 += n2)
        wfta (p1, w, n2);

    delete[] b;
}

void isixstepwftatrans (modint data[], modint *w[], modint pr, int isign, int n1, int n2)
{
    int j, k;
    modint wt, tmp, tmp2, *p1, *p2;

    if (isign > 0)
        wt = pow (pr, modint::modulus - 1 - (modint::modulus - 1) / (n1 * n2));
    else
        wt = pow (pr, (modint::modulus - 1) / (n1 * n2));

    modint *b = new modint[n1];

    // treat the input data as a n1 x n2 matrix

    // first do n1 transforms of length n2 in rows

    for (k = 0, p1 = data; k < n1; k++, p1 += n2)
        wfta (p1, w, n2);

    // then multiply the matrix A_ij by exp(isign * -2 pi i j k / nn)

    tmp = wt;
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
        tmp *= wt;
    }

    // last do n2 transforms of length n1 in columns

    for (k = 0, p1 = data; k < n2; k++, p1++)
    {
        for (j = 0, p2 = p1; j < n1; j++, p2 += n2)
            b[j] = *p2;

        wfta (b, w, n1);

        for (j = 0, p2 = p1; j < n1; j++, p2 += n2)
            *p2 = b[j];
    }

    delete[] b;
}
