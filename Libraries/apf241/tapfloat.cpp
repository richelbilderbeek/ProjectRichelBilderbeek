#include "ap.h"
#include "tapfloat.h"


tapfloat::tapfloat (const tapfloat &d)
{
    ap1 = d.ap1;
    ap2 = d.ap2;
    ap3 = d.ap3;

    if (ap1)
        ap1->nlinks++;
    if (ap2)
        ap2->nlinks++;
    if (ap3)
        ap3->nlinks++;
}

tapfloat::~tapfloat ()
{
    if (ap1)
        if (!(--(ap1->nlinks)))
           delete ap1;

    if (ap2)
        if (!(--(ap2->nlinks)))
           delete ap2;

    if (ap3)
        if (!(--(ap3->nlinks)))
           delete ap3;
}

void tapfloat::unique (void)
{
    if (ap1)
        if (ap1->nlinks > 1)
        {
            ap1->nlinks--;
            ap1 = new apstruct (*ap1);
        }

    if (ap2)
        if (ap2->nlinks > 1)
        {
            ap2->nlinks--;
            ap2 = new apstruct (*ap2);
        }

    if (ap3)
        if (ap3->nlinks > 1)
        {
            ap3->nlinks--;
            ap3 = new apstruct (*ap3);
        }
}

// Definitions of compound-assignment operator member functions

tapfloat &tapfloat::operator+= (const tapfloat &d)
{
    *this = *this + d;

    return *this;
}

tapfloat &tapfloat::operator= (const tapfloat &d)
{
    if (ap1 != d.ap1)
    {
        if (ap1)
            if (!(--(ap1->nlinks)))
                delete ap1;

        ap1 = d.ap1;
        if (ap1)
            ap1->nlinks++;
    }

    if (ap2 != d.ap2)
    {
        if (ap2)
            if (!(--(ap2->nlinks)))
                delete ap2;

        ap2 = d.ap2;
        if (ap2)
            ap2->nlinks++;
    }

    if (ap3 != d.ap3)
    {
        if (ap3)
            if (!(--(ap3->nlinks)))
                delete ap3;

        ap3 = d.ap3;
        if (ap3)
            ap3->nlinks++;
    }

    return *this;
}


// Definitions of non-member binary operator functions

tapfloat operator+ (const tapfloat &d1, const tapfloat &d2)
{
    return tapfloat (tapadd (d1.ap1, d2.ap1, 0), tapadd (d1.ap2, d2.ap2, 1), tapadd (d1.ap3, d2.ap3, 2));
}

apfloat operator* (const apfloat &d1, const tapfloat &d2)
{
    return apfloat (tapmul (d1.ap, d2.ap1, d2.ap2, d2.ap3));
}

apfloat operator* (const tapfloat &d1, const apfloat &d2)
{
    return apfloat (tapmul (d2.ap, d1.ap1, d1.ap2, d1.ap3));
}

apfloat operator* (const tapfloat &d1, const tapfloat &d2)
{
    return apfloat (tapmul (d1.ap1, d1.ap2, d1.ap3, d2.ap1, d2.ap2, d2.ap3));
}

tapfloat transform (apfloat x, size_t ssize, size_t padsize)
{
    if (ssize == (size_t) DEFAULT)
        ssize = x.ap->size;

    if (padsize == (size_t) DEFAULT)
        padsize = rnd23up (ssize * 2);
    else
        padsize = rnd23up (padsize);

    assert (ssize <= padsize);

    return tapfloat (transform (x.ap, 0, ssize, padsize), transform (x.ap, 1, ssize, padsize), transform (x.ap, 2, ssize, padsize));
}
