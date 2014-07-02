#include <fstream>
#include <cstdio>
#include "ap.h"


using namespace std;


// Optimized "two-pass" mass storage fnt functions

void tabletwopassfnt (fstream &in, modint pr, int isign, size_t nn)
{
    size_t n1, n2, j, k, m, b, s1, s2;
    modint w, tmp, tmp2, *p1, *p2;

    if (nn < 2) return;

    fstream out (filename (fno), ios::in | ios::out | ios::BIN | ios::trunc);

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

    // first do n2 transforms of length n1
    // by fetching n1 x b blocks in memory

    b = Maxblocksize / n1;
    if (b > n1) b = n1;

    modint *data = new modint[(nn < Maxblocksize ? nn : Maxblocksize)];

    // init tables

    tmp = pow (w, nn / n1);
    tmp2 = 1;
    for (k = 0; k < n1; k++)
    {
        wtable[k] = tmp2;
        tmp2 *= tmp;
    }

    initscrambletable (ptable, n1);

    tmp = 1;
    for (k = 0, s1 = 0; k < n2; k += b, s1 += b)
    {
        // read the data from the input file in b x b blocks

        for (j = 0, p1 = data, s2 = s1; j < n1; j += b, p1 += b)
        {
            for (m = 0, p2 = p1; m < b; m++, p2 += n1, s2 += n2)
            {
                in.seekg (sizeof (modint) * s2);
                in.read ((char *) p2, sizeof (modint) * b);
            }

            // transpose the b x b block

            transposesquare (p1, b, n1);
        }

        // do b transforms of size n1

        for (j = 0, p1 = data; j < b; j++, p1 += n1)
            tablefnt (p1, wtable, ptable, n1);

        // then multiply the matrix A_ij by exp(isign * -2 pi i j k / nn)

        for (j = 0, p1 = data; j < b; j++, p1 += n1)
        {
            tmp2 = tmp;
            for (m = 1; m < n1; m++, tmp2 *= tmp)
                p1[m] *= tmp2;
            tmp *= w;
        }

        // write the data to the scratch file

        out.write ((char *) data, sizeof (modint) * b * n1);
    }

    // then do n1 transforms of length n2
    // by fetching n2 x b blocks in memory

    b = Maxblocksize / n2;
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

        initscrambletable (ptable, n2);
    }

    for (k = 0, s1 = 0; k < n1; k += b, s1 += b)
    {
        // read the data from the input file in b x b blocks

        for (j = 0, p1 = data, s2 = s1; j < n2; j += b, p1 += b)
        {
            for (m = 0, p2 = p1; m < b; m++, p2 += n2, s2 += n1)
            {
                out.seekg (sizeof (modint) * s2);
                out.read ((char *) p2, sizeof (modint) * b);
            }

            // transpose the b x b block

            transposesquare (p1, b, n2);
        }

        // do b transforms of size n2

        for (j = 0, p1 = data; j < b; j++, p1 += n2)
            tablefnt (p1, wtable, ptable, n2);

        // write the data to the original file

        for (j = 0, p1 = data, s2 = s1; j < n2; j += b, p1 += b)
        {
            // transpose the b x b block

            transposesquare (p1, b, n2);

            for (m = 0, p2 = p1; m < b; m++, p2 += n2, s2 += n1)
            {
                in.seekp (sizeof (modint) * s2);
                in.write ((char *) p2, sizeof (modint) * b);
            }
        }
    }

    out.close ();

    remove (filename (fno));

    delete[] ptable;
    delete[] wtable;
    delete[] data;
}

void itabletwopassfnt (fstream &in, modint pr, int isign, size_t nn)
{
    size_t n1, n2, j, k, m, b, s1, s2;
    modint w, tmp, tmp2, *p1, *p2;

    if (nn < 2) return;

    fstream out (filename (fno), ios::in | ios::out | ios::BIN | ios::trunc);

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

    // first do n2 transforms of length n1
    // by fetching n1 x b blocks in memory

    b = Maxblocksize / n1;
    if (b > n1) b = n1;

    modint *data = new modint[(nn < Maxblocksize ? nn : Maxblocksize)];

    // init tables

    tmp = pow (w, nn / n1);
    tmp2 = 1;
    for (k = 0; k < n1; k++)
    {
        wtable[k] = tmp2;
        tmp2 *= tmp;
    }

    initscrambletable (ptable, n1);

    tmp = 1;
    for (k = 0, s1 = 0; k < n2; k += b, s1 += b)
    {
        // read the data from the input file in b x b blocks

        for (j = 0, p1 = data, s2 = s1; j < n1; j += b, p1 += b)
        {
            for (m = 0, p2 = p1; m < b; m++, p2 += n1, s2 += n2)
            {
                in.seekg (sizeof (modint) * s2);
                in.read ((char *) p2, sizeof (modint) * b);
            }

            // transpose the b x b block

            transposesquare (p1, b, n1);
        }

        // do b transforms of size n1

        for (j = 0, p1 = data; j < b; j++, p1 += n1)
            itablefnt (p1, wtable, ptable, n1);

        // then multiply the matrix A_ij by exp(isign * -2 pi i j k / nn)

        for (j = 0, p1 = data; j < b; j++, p1 += n1)
        {
            tmp2 = tmp;
            for (m = 1; m < n1; m++, tmp2 *= tmp)
                p1[m] *= tmp2;
            tmp *= w;
        }

        // write the data to the scratch file

        out.write ((char *) data, sizeof (modint) * b * n1);
    }

    // then do n1 transforms of length n2
    // by fetching n2 x b blocks in memory

    b = Maxblocksize / n2;
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

        initscrambletable (ptable, n2);
    }

    for (k = 0, s1 = 0; k < n1; k += b, s1 += b)
    {
        // read the data from the input file in b x b blocks

        for (j = 0, p1 = data, s2 = s1; j < n2; j += b, p1 += b)
        {
            for (m = 0, p2 = p1; m < b; m++, p2 += n2, s2 += n1)
            {
                out.seekg (sizeof (modint) * s2);
                out.read ((char *) p2, sizeof (modint) * b);
            }

            // transpose the b x b block

            transposesquare (p1, b, n2);
        }

        // do b transforms of size n2

        for (j = 0, p1 = data; j < b; j++, p1 += n2)
            itablefnt (p1, wtable, ptable, n2);

        // write the data to the original file

        for (j = 0, p1 = data, s2 = s1; j < n2; j += b, p1 += b)
        {
            // transpose the b x b block

            transposesquare (p1, b, n2);

            for (m = 0, p2 = p1; m < b; m++, p2 += n2, s2 += n1)
            {
                in.seekp (sizeof (modint) * s2);
                in.write ((char *) p2, sizeof (modint) * b);
            }
        }
    }

    out.close ();

    remove (filename (fno));

    delete[] ptable;
    delete[] wtable;
    delete[] data;
}
