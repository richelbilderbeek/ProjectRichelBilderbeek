#include "ap.h"


// Un-optimized "six-step" algorithm and inverse

void sixstepfnt (modint data[], modint pr, int isign, size_t nn)
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

    // treat the input data as a n1 x n2 matrix

    // first transpose the matrix

    transpose (data, n1, n2);

    // then do n2 transforms of length n1

    for (k = 0, p1 = data; k < n2; k++, p1 += n1)
        fnt (p1, pr, isign, n1);

    // transpose the matrix

    transpose (data, n2, n1);

    // then multiply the matrix A_ij by exp(isign * -2 pi i j k / nn)

    if (isign > 0)
        w = pow (pr, modint::modulus - 1 - (modint::modulus - 1) / nn);
    else
        w = pow (pr, (modint::modulus - 1) / nn);

    tmp = w;
    for (j = 1, p1 = data + n2; j < n1; j++, p1 += n2)
    {
        tmp2 = tmp;
        for (k = 1; k < n2; k++, tmp2 *= tmp)
            p1[k] *= tmp2;
        tmp *= w;
    }

    // then do n1 transforms of length n2

    for (k = 0, p1 = data; k < n1; k++, p1 += n2)
        fnt (p1, pr, isign, n2);

    // last transpose the matrix

    transpose (data, n1, n2);
}

void isixstepfnt (modint data[], modint pr, int isign, size_t nn)
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

    // treat the input data as a n1 x n2 matrix

    // first transpose the matrix

    transpose (data, n1, n2);

    // then do n2 transforms of length n1

    for (k = 0, p1 = data; k < n2; k++, p1 += n1)
        ifnt (p1, pr, isign, n1);

    // transpose the matrix

    transpose (data, n2, n1);

    // then multiply the matrix A_ij by exp(isign * -2 pi i j k / nn)

    if (isign > 0)
        w = pow (pr, modint::modulus - 1 - (modint::modulus - 1) / nn);
    else
        w = pow (pr, (modint::modulus - 1) / nn);

    tmp = w;
    for (j = 1, p1 = data + n2; j < n1; j++, p1 += n2)
    {
        tmp2 = tmp;
        for (k = 1; k < n2; k++, tmp2 *= tmp)
            p1[k] *= tmp2;
        tmp *= w;
    }

    // then do n1 transforms of length n2

    for (k = 0, p1 = data; k < n1; k++, p1 += n2)
        ifnt (p1, pr, isign, n2);

    // last transpose the matrix

    transpose (data, n1, n2);
}
