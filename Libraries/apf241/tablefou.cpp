#include "ap.h"


// Basic "four-step" fnt algorithms using table lookups

void tablefourstepfnt (modint data[], modint pr, int isign, size_t nn)
{
    size_t n1, n2, j, k, m, o;
    modint w, tmp, tmp2, *p1, *p2;

    if (nn < 2) return;

    for (n1 = 1, n2 = 0; n1 < nn; n1 <<= 1, n2++);
    n1 = n2 >> 1;
    n2 -= n1;

    n1 = 1 << n1;
    n2 = 1 << n2;

    // n2 >= n1

    modint *d = new modint[n2];
    modint *table = new modint[n2];

    if (isign > 0)
        w = pow (pr, modint::modulus - 1 - (modint::modulus - 1) / nn);
    else
        w = pow (pr, (modint::modulus - 1) / nn);

    // treat the input data as a n1 x n2 matrix

    // first do n2 transforms of length n1

    // init table

    tmp = pow (w, nn / n1);
    tmp2 = 1;
    for (k = 0; k < n1; k++)
    {
        table[k] = tmp2;
        tmp2 *= tmp;
    }

    for (k = 0, p1 = data; k < n2; k++, p1++)
    {
        for (j = 0, m = 0; j < n1; j++, m += n2)
            d[j] = p1[m];

        tablefnt (d, table, 0, n1, 0);

        for (j = 0, m = 0; j < n1; j++, m += n2)
            p1[m] = d[j];
    }

    // scramble all rows

    for (k = 0; k < n1; k++)
    {
        j = permute (k, n1);
        if (j < k)
            swapraw (data + n2 * k, data + n2 * j, n2);
    }

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

    // transpose the matrix

    transpose (data, n1, n2);

    // last do n1 transforms of length n2

    // init table

    if (n2 != n1)
    {
        tmp = pow (w, nn / n2);
        tmp2 = 1;
        for (k = 0; k < n2; k++)
        {
            table[k] = tmp2;
            tmp2 *= tmp;
        }
    }

    for (k = 0, p1 = data; k < n1; k++, p1++)
    {
        for (j = 0, m = 0; j < n2; j++, m += n1)
            d[j] = p1[m];

        tablefnt (d, table, 0, n2, 0);

        for (j = 0, m = 0; j < n2; j++, m += n1)
            p1[m] = d[j];
    }

    // scramble all rows

    for (k = 0; k < n2; k++)
    {
        j = permute (k, n2);
        if (j < k)
            swapraw (data + n1 * k, data + n1 * j, n1);
    }

    delete[] table;
    delete[] d;
}

void itablefourstepfnt (modint data[], modint pr, int isign, size_t nn)
{
    size_t n1, n2, j, k, m, o;
    modint w, tmp, tmp2, *p1, *p2;

    if (nn < 2) return;

    for (n1 = 1, n2 = 0; n1 < nn; n1 <<= 1, n2++);
    n1 = n2 >> 1;
    n2 -= n1;

    n1 = 1 << n1;
    n2 = 1 << n2;

    // n2 >= n1

    modint *d = new modint[n2];
    modint *table = new modint[n2];

    if (isign > 0)
        w = pow (pr, modint::modulus - 1 - (modint::modulus - 1) / nn);
    else
        w = pow (pr, (modint::modulus - 1) / nn);

    // treat the input data as a n1 x n2 matrix

    // first do n2 transforms of length n1

    // init table

    tmp = pow (w, nn / n1);
    tmp2 = 1;
    for (k = 0; k < n1; k++)
    {
        table[k] = tmp2;
        tmp2 *= tmp;
    }

    // scramble all rows

    for (k = 0; k < n1; k++)
    {
        j = permute (k, n1);
        if (j < k)
            swapraw (data + n2 * k, data + n2 * j, n2);
    }

    for (k = 0, p1 = data; k < n2; k++, p1++)
    {
        for (j = 0, m = 0; j < n1; j++, m += n2)
            d[j] = p1[m];

        itablefnt (d, table, 0, n1, 0);

        for (j = 0, m = 0; j < n1; j++, m += n2)
            p1[m] = d[j];
    }

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

    // transpose the matrix

    transpose (data, n1, n2);

    // last do n1 transforms of length n2

    // init table

    if (n2 != n1)
    {
        tmp = pow (w, nn / n2);
        tmp2 = 1;
        for (k = 0; k < n2; k++)
        {
            table[k] = tmp2;
            tmp2 *= tmp;
        }
    }

    // scramble all rows

    for (k = 0; k < n2; k++)
    {
        j = permute (k, n2);
        if (j < k)
            swapraw (data + n1 * k, data + n1 * j, n1);
    }

    for (k = 0, p1 = data; k < n1; k++, p1++)
    {
        for (j = 0, m = 0; j < n2; j++, m += n1)
            d[j] = p1[m];

        itablefnt (d, table, 0, n2, 0);

        for (j = 0, m = 0; j < n2; j++, m += n1)
            p1[m] = d[j];
    }

    delete[] table;
    delete[] d;
}
