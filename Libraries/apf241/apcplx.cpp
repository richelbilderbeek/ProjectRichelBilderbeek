#include "ap.h"
#include "apcplx.h"


using namespace std;


inline size_t min (size_t a, size_t b)
{
    return (a < b ? a : b);
}

inline size_t max (size_t a, size_t b)
{
    return (a > b ? a : b);
}


// More complicated apcomplex operators

size_t apcomplex::prec (void) const
{
    if (!re.sign () || !im.sign ())
        return min (re.prec (), im.prec ());

    if (re.prec () == INFINITE && im.prec () == INFINITE)
        return INFINITE;

    if (re.exp () >= im.exp ())
        return min (re.prec (), im.prec () + re.exp () - im.exp ());
    else
        return min (im.prec (), re.prec () + im.exp () - re.exp ());
}

void apcomplex::prec (size_t newprec)
{
    if (!re.sign () || !im.sign () || newprec == INFINITE)
    {
       re.prec (newprec);
       im.prec (newprec);

       return;
    }

    if (re.exp () >= im.exp ())
    {
        re.prec (newprec);
        im.prec (newprec - (re.exp () - im.exp ()));
    }
    else
    {
        re.prec (newprec - (im.exp () - re.exp ()));
        im.prec (newprec);
    }
}

apcomplex operator* (const apcomplex &z1, const apcomplex &z2)
{
    /*
    apfloat m1, m2, m3;

    // Only three multiplications
    m1 = z1.re * z2.re;
    m2 = z1.im * z2.im;
    m3 = (z1.im - z1.re) * (z2.re - z2.im);

    return apcomplex (m1 - m2, m3 + m1 + m2);
    */

    return apcomplex (z1.re * z2.re - z1.im * z2.im, z1.im * z2.re + z1.re * z2.im);
}

apcomplex operator/ (const apcomplex &z1, const apfloat &d2)
{
    size_t prec;
    apfloat t;

    if (d2.ap->size == 1) return apcomplex (z1.re / d2, z1.im / d2);    // Short

    prec = min (z1.prec (), d2.prec ());

    t = d2;
    t.prec (prec);

    t = invroot (t, 1);

    return apcomplex (z1.re * t, z1.im * t);
}

apcomplex operator/ (const apfloat &d1, const apcomplex &z2)
{
    return d1 * conj (z2) / norm (z2);
}

apcomplex operator/ (const apcomplex &z1, const apcomplex &z2)
{
    /*
    apfloat m1, m2, m3;

    // Only three multiplications
    m1 = z1.re * z2.re;
    m2 = z1.im * z2.im;
    m3 = (z1.im - z1.re) * (z2.re + z2.im);

    return apcomplex (m1 + m2, m3 + m1 - m2) / norm (z2);
    */

    return apcomplex (z1.re * z2.re + z1.im * z2.im, z1.im * z2.re - z1.re * z2.im) / norm (z2);
}

ostream &operator<< (ostream &str, const apcomplex &z)
{
    if (apfloat::prettyprint)
        str << '(' << pretty << z.re << ',' << pretty << z.im << ')';
    else
        str << '(' << z.re << ',' << z.im << ')';

    return str;
}

istream &operator>> (istream &str, apcomplex &z)
{
    char c;
    apcomplex t;

    if (str >> c && c != '(')
    {
        str.putback (c);
        str >> t.re;
        t.im = 0;
    }
    else if (str >> t.re >> c && c != ',')
    {
        if (c == ')')
        {
            t.im = 0;
        }
        else
        {
            str.putback (c);
            str.clear (ios::failbit);
        }
    }
    else if (str >> t.im >> c && c != ')')
    {
        str.putback (c);
        str.clear (ios::failbit);
    }

    if (!str.fail ())
        z = t;

    return str;
}
