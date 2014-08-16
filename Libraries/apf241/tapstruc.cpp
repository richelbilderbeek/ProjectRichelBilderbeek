#include "ap.h"
#include "tapfloat.h"


using namespace std;


inline size_t min (size_t a, size_t b)
{
    return (a < b ? a : b);
}

inline size_t max (size_t a, size_t b)
{
    return (a > b ? a : b);
}


// Do the transform modulo moduli[m]
// Size of s is ssize
// Transform length is n
apstruct *transform (apstruct *s, int m, size_t ssize, size_t n)
{
    int location = (n > Maxblocksize ? DISK : MEMORY);

    apstruct *tmp;

    if (MAXTRANSFORMLENGTH)
        assert (n <= MAXTRANSFORMLENGTH);       // Otherwise it won't work

    setmodulus (moduli[m]);

    tmp = new apstruct (*s, ssize, location, n);

    if (location != MEMORY)
    {
        fstream &fs = tmp->openstream ();
        tabletwopassfnttrans (fs, primitiveroots[m], 1, n);
        tmp->closestream ();
    }
    else
    {
        modint *data = tmp->getdata (0, n);
        tablesixstepfnttrans (data, primitiveroots[m], 1, n);
        tmp->putdata ();
    }

    tmp->relocate (DEFAULT);

    return tmp;
}


// Convolution of the mantissa in s1 and the transforms t1, t2, t3
// Use size s1size for s1
// Result size is rsize
// Transform length is n
// *i = 1 if right shift occurred, otherwise 0
apstruct *convolution (apstruct *s1, apstruct *t1, apstruct *t2, apstruct *t3, size_t rsize, size_t s1size, size_t n, int *i)
{
    int location = (n > Maxblocksize ? DISK : MEMORY);

    apstruct *tmp1;
    apstruct *tmp2;
    apstruct *tmp3;

    if (MAXTRANSFORMLENGTH)
        assert (n <= MAXTRANSFORMLENGTH);           // Otherwise it won't work

    assert (n == t1->size);             // Transform lengths must be same
    assert (n == t2->size);             // Transform lengths must be same
    assert (n == t3->size);             // Transform lengths must be same

    setmodulus (moduli[2]);

    tmp1 = new apstruct (*s1, s1size, location, n);

    if (location != MEMORY)
    {
        fstream &fs = tmp1->openstream ();
        tabletwopassfnttrans (fs, primitiveroots[2], 1, n);
        tmp1->closestream ();
    }
    else
    {
        modint *data = tmp1->getdata (0, n);
        tablesixstepfnttrans (data, primitiveroots[2], 1, n);
        tmp1->putdata ();
    }

    multiplyinplace (tmp1, t3);

    if (location != MEMORY)
    {
        fstream &fs = tmp1->openstream ();
        itabletwopassfnttrans (fs, primitiveroots[2], -1, n);
        tmp1->closestream ();
    }
    else
    {
        modint *data = tmp1->getdata (0, n);
        itablesixstepfnttrans (data, primitiveroots[2], -1, n);
        tmp1->putdata ();
        tmp1->relocate (DEFAULT);
    }

    setmodulus (moduli[1]);

    tmp2 = new apstruct (*s1, s1size, location, n);

    if (location != MEMORY)
    {
        fstream &fs = tmp2->openstream ();
        tabletwopassfnttrans (fs, primitiveroots[1], 1, n);
        tmp2->closestream ();
    }
    else
    {
        modint *data = tmp2->getdata (0, n);
        tablesixstepfnttrans (data, primitiveroots[1], 1, n);
        tmp2->putdata ();
    }

    multiplyinplace (tmp2, t2);

    if (location != MEMORY)
    {
        fstream &fs = tmp2->openstream ();
        itabletwopassfnttrans (fs, primitiveroots[1], -1, n);
        tmp2->closestream ();
    }
    else
    {
        modint *data = tmp2->getdata (0, n);
        itablesixstepfnttrans (data, primitiveroots[1], -1, n);
        tmp2->putdata ();
        tmp2->relocate (DEFAULT);
    }

    setmodulus (moduli[0]);

    tmp3 = new apstruct (*s1, s1size, location, n);

    if (location != MEMORY)
    {
        fstream &fs = tmp3->openstream ();
        tabletwopassfnttrans (fs, primitiveroots[0], 1, n);
        tmp3->closestream ();
    }
    else
    {
        modint *data = tmp3->getdata (0, n);
        tablesixstepfnttrans (data, primitiveroots[0], 1, n);
        tmp3->putdata ();
    }

    multiplyinplace (tmp3, t1);

    if (location != MEMORY)
    {
        fstream &fs = tmp3->openstream ();
        itabletwopassfnttrans (fs, primitiveroots[0], -1, n);
        tmp3->closestream ();
    }
    else
    {
        modint *data = tmp3->getdata (0, n);
        itablesixstepfnttrans (data, primitiveroots[0], -1, n);
        tmp3->putdata ();
    }

    *i = carrycrt (tmp3, tmp2, tmp1, rsize);

    delete tmp1;
    delete tmp2;

    // Return value can remain in memory

    return tmp3;
}

// Convolution of the transforms in s1, s2, s3 and t1, t2, t3
// Result size is rsize
// Transform length is n
// *i = 1 if right shift occurred, otherwise 0
apstruct *convolution (apstruct *s1, apstruct *s2, apstruct *s3, apstruct *t1, apstruct *t2, apstruct *t3, size_t rsize, size_t n, int *i)
{
    int location = (n > Maxblocksize ? DISK : MEMORY);

    apstruct *tmp1;
    apstruct *tmp2;
    apstruct *tmp3;

    if (MAXTRANSFORMLENGTH)
        assert (n <= MAXTRANSFORMLENGTH);           // Otherwise it won't work

    assert (n == s1->size);             // Transform lengths must be same
    assert (n == s2->size);             // Transform lengths must be same
    assert (n == s3->size);             // Transform lengths must be same
    assert (n == t1->size);             // Transform lengths must be same
    assert (n == t2->size);             // Transform lengths must be same
    assert (n == t3->size);             // Transform lengths must be same

    setmodulus (moduli[2]);

    tmp1 = new apstruct (*s3, s3->size, location, n);

    multiplyinplace (tmp1, t3);

    if (location != MEMORY)
    {
        fstream &fs = tmp1->openstream ();
        itabletwopassfnttrans (fs, primitiveroots[2], -1, n);
        tmp1->closestream ();
    }
    else
    {
        modint *data = tmp1->getdata (0, n);
        itablesixstepfnttrans (data, primitiveroots[2], -1, n);
        tmp1->putdata ();
        tmp1->relocate (DEFAULT);
    }

    setmodulus (moduli[1]);

    tmp2 = new apstruct (*s2, s2->size, location, n);

    multiplyinplace (tmp2, t2);

    if (location != MEMORY)
    {
        fstream &fs = tmp2->openstream ();
        itabletwopassfnttrans (fs, primitiveroots[1], -1, n);
        tmp2->closestream ();
    }
    else
    {
        modint *data = tmp2->getdata (0, n);
        itablesixstepfnttrans (data, primitiveroots[1], -1, n);
        tmp2->putdata ();
        tmp2->relocate (DEFAULT);
    }

    setmodulus (moduli[0]);

    tmp3 = new apstruct (*s1, s1->size, location, n);

    multiplyinplace (tmp3, t1);

    if (location != MEMORY)
    {
        fstream &fs = tmp3->openstream ();
        itabletwopassfnttrans (fs, primitiveroots[0], -1, n);
        tmp3->closestream ();
    }
    else
    {
        modint *data = tmp3->getdata (0, n);
        itablesixstepfnttrans (data, primitiveroots[0], -1, n);
        tmp3->putdata ();
    }

    *i = carrycrt (tmp3, tmp2, tmp1, rsize);

    delete tmp1;
    delete tmp2;

    // Return value can remain in memory

    return tmp3;
}

// Autoconvolution of the transform in t1, t2, t3
// Result size is rsize
// Transform length is n
// *i = 1 if right shift occurred, otherwise 0
apstruct *autoconvolution (apstruct *t1, apstruct *t2, apstruct *t3, size_t rsize, size_t n, int *i)
{
    int location = (n > Maxblocksize ? DISK : MEMORY);

    apstruct *tmp1;
    apstruct *tmp2;
    apstruct *tmp3;

    if (MAXTRANSFORMLENGTH)
        assert (n <= MAXTRANSFORMLENGTH);           // Otherwise it won't work

    assert (n == t1->size);             // Transform lengths must be same
    assert (n == t2->size);             // Transform lengths must be same
    assert (n == t3->size);             // Transform lengths must be same

    setmodulus (moduli[2]);

    tmp1 = new apstruct (*t3, t3->size, location, n);

    squareinplace (tmp1);

    if (location != MEMORY)
    {
        fstream &fs = tmp1->openstream ();
        itabletwopassfnttrans (fs, primitiveroots[2], -1, n);
        tmp1->closestream ();
    }
    else
    {
        modint *data = tmp1->getdata (0, n);
        itablesixstepfnttrans (data, primitiveroots[2], -1, n);
        tmp1->putdata ();
        tmp1->relocate (DEFAULT);
    }

    setmodulus (moduli[1]);

    tmp2 = new apstruct (*t2, t2->size, location, n);

    squareinplace (tmp2);

    if (location != MEMORY)
    {
        fstream &fs = tmp2->openstream ();
        itabletwopassfnttrans (fs, primitiveroots[1], -1, n);
        tmp2->closestream ();
    }
    else
    {
        modint *data = tmp2->getdata (0, n);
        itablesixstepfnttrans (data, primitiveroots[1], -1, n);
        tmp2->putdata ();
        tmp2->relocate (DEFAULT);
    }

    setmodulus (moduli[0]);

    tmp3 = new apstruct (*t1, t1->size, location, n);

    squareinplace (tmp3);

    if (location != MEMORY)
    {
        fstream &fs = tmp3->openstream ();
        itabletwopassfnttrans (fs, primitiveroots[0], -1, n);
        tmp3->closestream ();
    }
    else
    {
        modint *data = tmp3->getdata (0, n);
        itablesixstepfnttrans (data, primitiveroots[0], -1, n);
        tmp3->putdata ();
    }

    *i = carrycrt (tmp3, tmp2, tmp1, rsize);

    delete tmp1;
    delete tmp2;

    // Return value can remain in memory

    return tmp3;
}

// Add the two transforms
// Assume that ds1 will be in memory if possible
void addinplace (apstruct *ds1, apstruct *s2)
{
    size_t t, p = ds1->size, l, r = 0;
    modint *buf1, *buf2;

    while (p)
    {
        l = (p < Blocksize ? p : Blocksize);
        p -= l;
        buf1 = ds1->getdata (r, l);
        buf2 = s2->getdata (r, l);
        r += l;

        for (t = 0; t < l; t++)
            buf1[t] += buf2[t];

        ds1->putdata ();
        s2->cleardata ();
    }
}

// Add the same transform
// Assume that ds will be in memory if possible
void doubleinplace (apstruct *ds)
{
    size_t t, p = ds->size, l, r = 0;
    modint *buf;

    while (p)
    {
        l = (p < Maxblocksize ? p : Maxblocksize);
        p -= l;
        buf = ds->getdata (r, l);
        r += l;

        for (t = 0; t < l; t++)
            buf[t] += buf[t];

        ds->putdata ();
    }
}

apstruct *tapadd (apstruct *a, apstruct *b, int m)
{
    size_t n = a->size;
    int location = (n > Maxblocksize ? DISK : MEMORY);

    apstruct *tmp;

    assert (n == b->size);              // Transform lengths must be same
    assert (a->sign == b->sign);        // Numbers' signs must be same
    assert (a->exp == b->exp);          // Numbers' exponents must be same

    setmodulus (moduli[m]);

    tmp = new apstruct (*a, a->size, location, n);

    if (a == b)
        doubleinplace (tmp);
    else
        addinplace (tmp, b);

    tmp->relocate (DEFAULT);

    return tmp;
}

apstruct *tapmul (apstruct *a, apstruct *b1, apstruct *b2, apstruct *b3)
{
    int i, sign;
    size_t n, prec, size, rsize;
    apstruct *ap;
    size_t trueasize;

    assert (a);                 // Won't work on uninitialized apfloats
    assert (b1);
    assert (b2);
    assert (b3);

    sign = a->sign * b1->sign;
    if (!sign) return new apstruct;             // Zero

    prec = min (a->prec, b1->prec);
    size = min (prec, a->size + b1->prec);

    trueasize = min (a->size, prec);

    n = b1->size;

    size = min (size, n);

    rsize = min (n, size + 2);

    ap = convolution (a, b1, b2, b3, rsize, trueasize, n, &i);

    size -= lastzeros (ap, size);

    ap->relocate (DEFAULT, size);

    ap->sign = sign;
    ap->prec = prec;
    ap->exp = a->exp + b1->exp - 1 + i;

    return ap;
}

apstruct *tapmul (apstruct *a1, apstruct *a2, apstruct *a3, apstruct *b1, apstruct *b2, apstruct *b3)
{
    int i, sign;
    size_t n, prec, size, rsize;
    apstruct *ap;

    assert (a1);                // Won't work on uninitialized apfloats
    assert (a2);
    assert (a3);
    assert (b1);
    assert (b2);
    assert (b3);

    sign = a1->sign * b1->sign;
    if (!sign) return new apstruct;             // Zero

    prec = min (a1->prec, b1->prec);
    size = min (prec, a1->size);

    n = a1->size;

    rsize = min (n, size + 2);

    if (a1 == b1)
        ap = autoconvolution (a1, a2, a3, rsize, n, &i);
    else
        ap = convolution (a1, a2, a3, b1, b2, b3, rsize, n, &i);

    size -= lastzeros (ap, size);

    ap->relocate (DEFAULT, size);

    ap->sign = sign;
    ap->prec = prec;
    ap->exp = a1->exp + b1->exp - 1 + i;

    return ap;
}
