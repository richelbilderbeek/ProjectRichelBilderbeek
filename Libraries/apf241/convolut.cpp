#include "ap.h"


using namespace std;


// Linear multiplication in the number theoretic domain
// Assume that ds1 will be in memory if possible
void multiplyinplace (apstruct *ds1, apstruct *s2)
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
            buf1[t] *= buf2[t];

        ds1->putdata ();
        s2->cleardata ();
    }
}

// Linear squaring in the number theoretic domain
// Assume that ds will be in memory if possible
void squareinplace (apstruct *ds)
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
            buf[t] *= buf[t];

        ds->putdata ();
    }
}

// Convolution of the mantissas in s1 and s2
// Use sizes s1size and s2size correspondingly
// Result size is rsize
// Transform length is n
// *i = 1 if right shift occurred, otherwise 0
apstruct *convolution (apstruct *s1, apstruct *s2, size_t rsize, size_t s1size, size_t s2size, size_t n, int *i)
{
    int location = (n > Maxblocksize ? DISK : MEMORY);

    apstruct *tmp1;
    apstruct *tmp2;
    apstruct *tmp3;
    apstruct *tmp4;

    if (MAXTRANSFORMLENGTH)
        assert (n <= MAXTRANSFORMLENGTH);           // Otherwise it won't work

    setmodulus (moduli[2]);

    tmp2 = new apstruct (*s2, s2size, location, n);

    if (location != MEMORY)
    {
        fstream &fs = tmp2->openstream ();
        tabletwopassfnttrans (fs, primitiveroots[2], 1, n);
        tmp2->closestream ();
    }
    else
    {
        modint *data = tmp2->getdata (0, n);
        tablesixstepfnttrans (data, primitiveroots[2], 1, n);
        tmp2->putdata ();
        tmp2->relocate (DEFAULT);
    }

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

    multiplyinplace (tmp1, tmp2);

    delete tmp2;

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

    tmp3 = new apstruct (*s2, s2size, location, n);

    if (location != MEMORY)
    {
        fstream &fs = tmp3->openstream ();
        tabletwopassfnttrans (fs, primitiveroots[1], 1, n);
        tmp3->closestream ();
    }
    else
    {
        modint *data = tmp3->getdata (0, n);
        tablesixstepfnttrans (data, primitiveroots[1], 1, n);
        tmp3->putdata ();
        tmp3->relocate (DEFAULT);
    }

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

    multiplyinplace (tmp2, tmp3);

    delete tmp3;

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

    tmp4 = new apstruct (*s2, s2size, location, n);

    if (location != MEMORY)
    {
        fstream &fs = tmp4->openstream ();
        tabletwopassfnttrans (fs, primitiveroots[0], 1, n);
        tmp4->closestream ();
    }
    else
    {
        modint *data = tmp4->getdata (0, n);
        tablesixstepfnttrans (data, primitiveroots[0], 1, n);
        tmp4->putdata ();
        tmp4->relocate (DEFAULT);
    }

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

    multiplyinplace (tmp3, tmp4);

    delete tmp4;

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

// Autoconvolution of the mantissa in s
// Use size ssize for s
// Result size is rsize
// Transform length is n
// *i = 1 if right shift occurred, otherwise 0
apstruct *autoconvolution (apstruct *s, size_t rsize, size_t ssize, size_t n, int *i)
{
    int location = (n > Maxblocksize ? DISK : MEMORY);

    apstruct *tmp1;
    apstruct *tmp2;
    apstruct *tmp3;

    if (MAXTRANSFORMLENGTH)
        assert (n <= MAXTRANSFORMLENGTH);           // Otherwise it won't work

    setmodulus (moduli[2]);

    tmp1 = new apstruct (*s, ssize, location, n);

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

    tmp2 = new apstruct (*s, ssize, location, n);

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

    tmp3 = new apstruct (*s, ssize, location, n);

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
