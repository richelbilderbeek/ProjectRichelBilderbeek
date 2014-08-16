#include <fstream>
#include "ap.h"


using namespace std;


inline size_t min (size_t a, size_t b)
{
    return (a < b ? a : b);
}

inline size_t rnd2down2 (size_t x)
{
    size_t x2 = (x & -x);

    return (x2 < x ? x - x2 : x);
}

// The "two-pass" mass storage fnt, but doesn't transpose or scramble
// (for convolution only)
void tabletwopassfnttrans2 (fstream &in, modint pr, int isign, size_t nn, size_t o)
{
    size_t n1, n2, j, k, m, b, s1, s2, maxblocksize2 = rnd2down2 (Maxblocksize);
    modint w, tmp, tmp2, *p1, *p2;

    if (nn < 2) return;

    for (n1 = 1, n2 = 0; n1 < nn; n1 <<= 1, n2++);
    n1 = n2 >> 1;
    n2 -= n1;

    n1 = 1 << n1;
    n2 = 1 << n2;

    // n2 >= n1

    modint *wtable = new modint[n2];

    if (isign > 0)
        w = pow (pr, modint::modulus - 1 - (modint::modulus - 1) / nn);
    else
        w = pow (pr, (modint::modulus - 1) / nn);

    // treat the input data as a n1 x n2 matrix

    // first do n2 transforms of length n1 in columns
    // by fetching n1 x b blocks in memory

    b = min (n1, maxblocksize2 / n1);

    modint *data = new modint[min (nn, maxblocksize2)];

    // init tables

    tmp = pow (w, nn / n1);
    tmp2 = 1;
    for (k = 0; k < n1; k++)
    {
        wtable[k] = tmp2;
        tmp2 *= tmp;
    }

    for (k = 0, s1 = 0; k < n2; k += b, s1 += b)
    {
        // read the data from the input file in b x b blocks

        for (j = 0, p1 = data, s2 = s1; j < n1; j += b, p1 += b)
        {
            for (m = 0, p2 = p1; m < b; m++, p2 += n1, s2 += n2)
            {
                in.seekg (sizeof (modint) * (s2 + o));
                in.read ((char *) p2, sizeof (modint) * b);
            }

            // transpose the b x b block

            transposesquare (p1, b, n1);
        }

        // do b transforms of size n1

        for (j = 0, p1 = data; j < b; j++, p1 += n1)
            tablefnt (p1, wtable, 0, n1, 0);

        // write the data back to the same location

        for (j = 0, p1 = data, s2 = s1; j < n1; j += b, p1 += b)
        {
            // transpose the b x b block

            transposesquare (p1, b, n1);

            for (m = 0, p2 = p1; m < b; m++, p2 += n1, s2 += n2)
            {
                in.seekp (sizeof (modint) * (s2 + o));
                in.write ((char *) p2, sizeof (modint) * b);
            }
        }
    }

    // then do n1 transforms of length n2 in rows
    // by fetching b x n2 blocks in memory

    b = maxblocksize2 / n2;
    if (b > n1) b = n1;

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
    }

    for (k = 0, s1 = 0; k < n1; k += b, s1 += b)
    {
        // read the data from the input file in b x n2 blocks

        in.seekg (sizeof (modint) * (s1 * n2 + o));
        in.read ((char *) data, sizeof (modint) * b * n2);


        for (j = 0, p1 = data; j < b; j++, p1 += n2)
        {
            // multiply the matrix A_ij by exp(isign * -2 pi i j k / nn)

            tmp2 = tmp = pow (w, permute (k + j, n1));
            for (m = 1; m < n2; m++, tmp2 *= tmp)
                p1[m] *= tmp2;

            // do b transforms of size n2

            tablefnt (p1, wtable, 0, n2, 0);
        }

        // write the data back to the same location

        in.seekp (sizeof (modint) * (s1 * n2 + o));
        in.write ((char *) data, sizeof (modint) * b * n2);
    }

    delete[] wtable;
    delete[] data;
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

void tabletwopassfnttrans (fstream &in, modint pr, int isign, size_t nn)
{
    size_t n2 = (nn & -nn), j, k, s, maxblocksize2 = rnd2down2 (Maxblocksize);
    modint w, ww, w1, w2, w3, *p1, *p2, *p3, tmp, tmp2, *d;

    if (nn < 2) return;

    if (nn == n2)
    {
        // Transform length is a power of two
        tabletwopassfnttrans2 (in, pr, isign, nn);
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

    s = min (n2, maxblocksize2 / 4);
    d = new modint[3 * s];

    tmp = tmp2 = 1;
    for (k = 0; k < n2; k += s)
    {
        p1 = d;
        p2 = p1 + s;
        p3 = p2 + s;
        in.seekg (sizeof (modint) * k);                 // Read to memory
        in.read ((char *) p1, sizeof (modint) * s);
        in.seekg (sizeof (modint) * (k + n2));
        in.read ((char *) p2, sizeof (modint) * s);
        in.seekg (sizeof (modint) * (k + 2 * n2));
        in.read ((char *) p3, sizeof (modint) * s);
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
        in.seekp (sizeof (modint) * k);                 // Write back to disk
        in.write ((char *) p1, sizeof (modint) * s);
        in.seekp (sizeof (modint) * (k + n2));
        in.write ((char *) p2, sizeof (modint) * s);
        in.seekp (sizeof (modint) * (k + 2 * n2));
        in.write ((char *) p3, sizeof (modint) * s);
    }

    delete[] d;

    if (n2 <= maxblocksize2)
    {
        d = new modint[n2];

        for (j = 0; j < 3; j++)
        {
            in.seekg (sizeof (modint) * j * n2);
            in.read ((char *) d, sizeof (modint) * n2);
            tablesixstepfnttrans2 (d, pr, isign, n2);       // Transform rows
            in.seekp (sizeof (modint) * j * n2);
            in.write ((char *) d, sizeof (modint) * n2);
        }

        delete[] d;
    }
    else
    {
        tabletwopassfnttrans2 (in, pr, isign, n2, 0);       // Transform rows
        tabletwopassfnttrans2 (in, pr, isign, n2, n2);
        tabletwopassfnttrans2 (in, pr, isign, n2, 2 * n2);
    }
}


// The "two-pass" mass storage inverse fnt, but doesn't transpose or scramble
// (for convolution only)
void itabletwopassfnttrans2 (fstream &in, modint pr, int isign, size_t nn, size_t o, size_t e)
{
    size_t n1, n2, j, k, m, b, s1, s2, maxblocksize2 = rnd2down2 (Maxblocksize);
    modint w, tmp, tmp2, *p1, *p2, inn;

    if (nn < 2) return;

    for (n1 = 1, n2 = 0; n1 < nn; n1 <<= 1, n2++);
    n1 = n2 >> 1;
    n2 -= n1;

    n1 = 1 << n1;
    n2 = 1 << n2;

    // n2 >= n1

    modint *wtable = new modint[n2];

    if (isign > 0)
        w = pow (pr, modint::modulus - 1 - (modint::modulus - 1) / nn);
    else
        w = pow (pr, (modint::modulus - 1) / nn);

    // treat the input data as a n1 x n2 matrix

    // first do n1 transforms of length n2 in rows
    // by fetching b x n2 blocks in memory

    b = min (n1, maxblocksize2 / n2);

    modint *data = new modint[min (nn, maxblocksize2)];

    // init table

    tmp = pow (w, nn / n2);
    tmp2 = 1;
    for (k = 0; k < n2; k++)
    {
        wtable[k] = tmp2;
        tmp2 *= tmp;
    }

    inn = modint (1) / modint (nn * e);

    for (k = 0, s1 = 0; k < n1; k += b, s1 += b)
    {
        // read the data from the input file in b x n2 blocks

        in.seekg (sizeof (modint) * (s1 * n2 + o));
        in.read ((char *) data, sizeof (modint) * b * n2);

        // then do b transforms of size n2

        for (j = 0, p1 = data; j < b; j++, p1 += n2)
        {
            itablefnt (p1, wtable, 0, n2, 0);

            // multiply the matrix A_ij by exp(isign * -2 pi i j k / nn)

            tmp = pow (w, permute (k + j, n1));
            tmp2 = inn;
            for (m = 0; m < n2; m++, tmp2 *= tmp)
                p1[m] *= tmp2;
        }

        // write the data back to the same location

        in.seekp (sizeof (modint) * (s1 * n2 + o));
        in.write ((char *) data, sizeof (modint) * b * n2);
    }

    // last do n2 transforms of length n1 in columns
    // by fetching n1 x b blocks in memory

    b = maxblocksize2 / n1;
    if (b > n1) b = n1;

    // init tables

    if (n2 != n1)
    {
        tmp = pow (w, nn / n1);
        tmp2 = 1;
        for (k = 0; k < n1; k++)
        {
            wtable[k] = tmp2;
            tmp2 *= tmp;
        }
    }

    for (k = 0, s1 = 0; k < n2; k += b, s1 += b)
    {
        // read the data from the input file in b x b blocks

        for (j = 0, p1 = data, s2 = s1; j < n1; j += b, p1 += b)
        {
            for (m = 0, p2 = p1; m < b; m++, p2 += n1, s2 += n2)
            {
                in.seekg (sizeof (modint) * (s2 + o));
                in.read ((char *) p2, sizeof (modint) * b);
            }

            // transpose the b x b block

            transposesquare (p1, b, n1);
        }

        // do b transforms of size n1

        for (j = 0, p1 = data; j < b; j++, p1 += n1)
            itablefnt (p1, wtable, 0, n1, 0);

        // write the data back to the same location

        for (j = 0, p1 = data, s2 = s1; j < n1; j += b, p1 += b)
        {
            // transpose the b x b block

            transposesquare (p1, b, n1);

            for (m = 0, p2 = p1; m < b; m++, p2 += n1, s2 += n2)
            {
                in.seekp (sizeof (modint) * (s2 + o));
                in.write ((char *) p2, sizeof (modint) * b);
            }
        }
    }

    delete[] wtable;
    delete[] data;
}

void itabletwopassfnttrans (fstream &in, modint pr, int isign, size_t nn)
{
    size_t n2 = (nn & -nn), j, k, s, maxblocksize2 = rnd2down2 (Maxblocksize);
    modint w, ww, w1, w2, w3, *p1, *p2, *p3, tmp, tmp2, *d;

    if (nn < 2) return;

    if (nn == n2)
    {
        // Transform length is a power of two
        itabletwopassfnttrans2 (in, pr, isign, nn);
        return;
    }

    // Transform length is three times a power of two

    if (isign > 0)
        w = pow (pr, modint::modulus - 1 - (modint::modulus - 1) / nn);
    else
        w = pow (pr, (modint::modulus - 1) / nn);

    if (n2 <= maxblocksize2)
    {
        d = new modint[n2];

        for (j = 0; j < 3; j++)
        {
            in.seekg (sizeof (modint) * j * n2);
            in.read ((char *) d, sizeof (modint) * n2);
            itablesixstepfnttrans2 (d, pr, isign, n2, 3);   // Transform rows
            in.seekp (sizeof (modint) * j * n2);
            in.write ((char *) d, sizeof (modint) * n2);
        }

        delete[] d;
    }
    else
    {
        itabletwopassfnttrans2 (in, pr, isign, n2, 0, 3);   // Transform rows
        itabletwopassfnttrans2 (in, pr, isign, n2, n2, 3);
        itabletwopassfnttrans2 (in, pr, isign, n2, 2 * n2, 3);
    }

    ww = w * w;

    w3 = pow (w, n2);                   // 3rd root of unity
    w1 = -modint (3) / modint (2);
    w2 = w3 + modint (1) / modint (2);

    s = min (n2, maxblocksize2 / 4);
    d = new modint[3 * s];

    tmp = tmp2 = 1;
    for (k = 0; k < n2; k += s)
    {
        p1 = d;
        p2 = p1 + s;
        p3 = p2 + s;
        in.seekg (sizeof (modint) * k);                 // Read to memory
        in.read ((char *) p1, sizeof (modint) * s);
        in.seekg (sizeof (modint) * (k + n2));
        in.read ((char *) p2, sizeof (modint) * s);
        in.seekg (sizeof (modint) * (k + 2 * n2));
        in.read ((char *) p3, sizeof (modint) * s);
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
        in.seekp (sizeof (modint) * k);                 // Write back to disk
        in.write ((char *) p1, sizeof (modint) * s);
        in.seekp (sizeof (modint) * (k + n2));
        in.write ((char *) p2, sizeof (modint) * s);
        in.seekp (sizeof (modint) * (k + 2 * n2));
        in.write ((char *) p3, sizeof (modint) * s);
    }

    delete[] d;
}
