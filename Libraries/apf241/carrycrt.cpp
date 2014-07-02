#include "ap.h"


// Carry & Chinese Remainder Theorem for fnt-multiplication (and square)
// Returns 1 if right shift ocurred
// Assume that ds1 will be in memory if possible

int carrycrt (apstruct *ds1, apstruct *s2, apstruct *s3, size_t rsize)  // Low to high
{
    size_t l, t, p = rsize, r;
    rawtype m01[2], m02[2], m12[2], mm[3], s[3], x[3], c[3] = {0};
    modint *buf1, *buf2, *buf3;
    modint t0, t1, t2, y0, y1, y2;
    rawtype carry, tmp1, tmp2;

    setmodulus (moduli[0]);
    t0 = modint (1) / (modint (moduli[1]) * moduli[2]);

    //Now moduli[0] is larger than moduli[1], so special care must be taken
    setmodulus (moduli[1]);
    tmp1 = moduli[0];
    while (tmp1 >= modint::modulus) tmp1 -= modint::modulus;
    t1 = modint (1) / (modint (tmp1) * moduli[2]);

    //Now moduli[0] and moduli[1] are larger than moduli[2] again
    setmodulus (moduli[2]);
    tmp1 = moduli[0];
    while (tmp1 >= modint::modulus) tmp1 -= modint::modulus;
    tmp2 = moduli[1];
    while (tmp2 >= modint::modulus) tmp2 -= modint::modulus;
    t2 = modint (1) / (modint (tmp1) * tmp2);

    m01[0] = moduli[0];
    m01[1] = bigmul (m01, m01, moduli[1], 1);

    m02[0] = moduli[0];
    m02[1] = bigmul (m02, m02, moduli[2], 1);

    m12[0] = moduli[1];
    m12[1] = bigmul (m12, m12, moduli[2], 1);

    mm[2] = bigmul (mm, m01, moduli[2], 2);

    while (p)
    {
        l = (p < Blocksize ? p : Blocksize);
        p -= l;
        buf1 = ds1->getdata (p, l);
        buf2 = s2->getdata (p, l);
        buf3 = s3->getdata (p, l);

        for (t = l; t--;)
        {
            setmodulus (moduli[0]);
            y0 = t0 * buf1[t];

            s[2] = bigmul (s, m12, y0, 2);

            setmodulus (moduli[1]);
            y1 = t1 * buf2[t];

            x[2] = bigmul (x, m02, y1, 2);

            setmodulus (moduli[2]);
            y2 = t2 * buf3[t];

            if (bigadd (s, x, 3) != 0 ||
                bigcmp (s, mm, 3) >= 0)
                bigsub (s, mm, 3);

            x[2] = bigmul (x, m01, y2, 2);

            if (bigadd (s, x, 3) != 0 ||
                bigcmp (s, mm, 3) >= 0)
                bigsub (s, mm, 3);

            bigadd (c, s, 3);

            buf1[t] = bigdiv (c, c, Base, 3);
        }
        s3->cleardata ();
        s2->cleardata ();
        ds1->putdata ();
    }

    carry = c[0];

    if (carry != 0)
    {
        p = ds1->size;
        r = 0;

        tmp1 = carry;

        while (p)
        {
            l = (p < Maxblocksize ? p : Maxblocksize);
            p -= l;
            buf1 = ds1->getdata (r, l);
            r += l;
            for (t = 0; t < l; t++)
            {
                tmp2 = buf1[t];
                buf1[t] = tmp1;
                tmp1 = tmp2;
            }
            ds1->putdata ();
        }

        return 1;
    }

    return 0;
}
