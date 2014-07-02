#include "ap.h"


// Optimized transposition routines

// Move a b x b block from s to d, d width = nd , s width = ns
void moveblock (modint d[], modint s[], size_t b, size_t nd, size_t ns)
{
    size_t j, k;

    for (j = 0; j < b; j++)
    {
        for (k = 0; k < b; k++)
            d[k] = s[k];

        d += nd;
        s += ns;
    }
}

// Transpose two b x b blocks of matrix with width nn
// data1 is accessed in columns, data2 in rows
void transpose2blocks (modint data1[], modint data2[], size_t b, size_t nn)
{
    size_t j, k;
    modint tmp, *p1, *p2;

    for (j = 0, p1 = data2; j < b; j++, p1 += nn)
        for (k = 0, p2 = data1 + j; k < b; k++, p2 += nn)
        {
            tmp = p1[k];
            p1[k] = *p2;
            *p2 = tmp;
        }
}

// Transpose a b x b block of matrix with width nn
void transposeblock (modint data[], size_t b, size_t nn)
{
    size_t j, k;
    modint tmp, *p1, *p2;

    for (j = 0, p1 = data; j < b; j++, p1 += nn)
        for (k = j + 1, p2 = data + k * nn + j; k < b; k++, p2 += nn)
        {
            tmp = p1[k];
            p1[k] = *p2;
            *p2 = tmp;
        }
}

// Transpose a _square_ n1 x n1 block of n1 x n2 matrix in b x b blocks
void transposesquare (modint data[], size_t n1, size_t n2)
{
    size_t j, k, b;
    modint tmp, *p1, *p2;

    if (n1 <= Cacheburstblocksize || n1 <= Cacheblocksize)
        transposeblock (data, n1, n2);
    else if (n1 * n2 <= Cachetreshold)
    {
        b = Cacheburstblocksize;

        for (j = 0, p1 = data; j < n1; j += b, p1 += b * n2)
        {
            transposeblock (p1 + j, b, n2);
            for (k = j + b, p2 = data + k * n2 + j; k < n1; k += b, p2 += b * n2)
                transpose2blocks (p1 + k, p2, b, n2);
        }
    }
    else
    {
        b = Cacheblocksize;

        modint *tmp1 = new modint[b * b];
        modint *tmp2 = new modint[b * b];

        for (j = 0, p1 = data; j < n1; j += b, p1 += b * n2)
        {
            moveblock (tmp1, p1 + j, b, b, n2);
            transposeblock (tmp1, b, b);
            moveblock (p1 + j, tmp1, b, n2, b);

            for (k = j + b, p2 = data + k * n2 + j; k < n1; k += b, p2 += b * n2)
            {
                moveblock (tmp1, p1 + k, b, b, n2);
                transposeblock (tmp1, b, b);

                moveblock (tmp2, p2, b, b, n2);
                transposeblock (tmp2, b, b);

                moveblock (p1 + k, tmp2, b, n2, b);
                moveblock (p2, tmp1, b, n2, b);
            }
        }

        delete[] tmp2;
        delete[] tmp1;
    }
}

// Permute the rows of matrix to correct order, must be n2 = 2*n1
void permutewidetotall (modint data[], size_t n1, size_t n2)
{
    size_t j, k, o, m;

    if (n2 < 4) return;

    modint *d = new modint[n1];
    int *r = new int[n2];

    for (j = 0; j < n2; j++) r[j] = 0;

    j = 1;
    do
    {
        o = m = j;

        moveraw (d, data + n1 * m, n1);

        r[m] = 1;

        m = (m < n1 ? 2 * m : 2 * (m - n1) + 1);

        while (m != j)
        {
            r[m] = 1;

            moveraw (data + n1 * o, data + n1 * m, n1);

            o = m;
            m = (m < n1 ? 2 * m : 2 * (m - n1) + 1);
        };

        moveraw (data + n1 * o, d, n1);

        while (r[j]) j++;
    } while (j < n2 - 1);

    delete[] r;
    delete[] d;
}

// Permute the rows of matrix to correct order, must be n1 = 2*n2
void permutetalltowide (modint data[], size_t n1, size_t n2)
{
    size_t j, k, o, m;

    if (n1 < 4) return;

    modint *d = new modint[n2];
    int *r = new int[n1];

    for (j = 0; j < n1; j++) r[j] = 0;

    j = 1;
    do
    {
        o = m = j;

        moveraw (d, data + n2 * m, n2);

        r[m] = 1;

        m = (m & 1 ? m / 2 + n2 : m / 2);

        while (m != j)
        {
            r[m] = 1;

            moveraw (data + n2 * o, data + n2 * m, n2);

            o = m;
            m = (m & 1 ? m / 2 + n2 : m / 2);
        };

        moveraw (data + n2 * o, d, n2);

        while (r[j]) j++;
    } while (j < n1 - 1);

    delete[] r;
    delete[] d;
}

// Transpose a n1 x n2 matrix. Must be n1 = n2, n1 = 2*n2 or n2 = 2*n1
void transpose (modint data[], size_t n1, size_t n2)
{
    if (n1 == n2)
    {
        // simply transpose

        transposesquare (data, n1, n1);
    }
    else if (n2 == 2 * n1)
    {
        // first transpose two n1 x n1 blocks
        transposesquare (data, n1, n2);
        transposesquare (data + n1, n1, n2);

        // then permute the rows to correct order
        permutewidetotall (data, n1, n2);
    }
    else if (n1 == 2 * n2)
    {
        // first permute the rows to correct order
        permutetalltowide (data, n1, n2);

        // then transpose two n2 x n2 blocks
        transposesquare (data, n2, n1);
        transposesquare (data + n2, n2, n1);
    }
}
