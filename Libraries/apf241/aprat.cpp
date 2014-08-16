#include "ap.h"
#include "aprat.h"


using namespace std;


bool aprational::autoreduce = true;


inline size_t max (size_t a, size_t b)
{
    return (a > b ? a : b);
}

// More complicated aprational operators

ostream &operator<< (ostream &str, const aprational &r)
{
    str << r.nom << '/' << r.den;

    return str;
}

istream &operator>> (istream &str, aprational &r)
{
    char c;
    aprational t;

    if (str >> t.nom)
    {
        if (str >> c && c != '/')
        {
            str.putback (c);
            t.den = 1;
        }
        else
        {
            str >> t.den;
        }
    }

    if (!str.fail ())
        r = t;

    return str;
}

void aprational::reduce (void)
{
    apint g = gcd (nom, den);

    nom /= g;
    den /= g;
}

apfloat aprational::approx (size_t prec)
{
    apfloat n, d;

    if (prec == (size_t) DEFAULT)
        prec = Basedigits * max (nom.val.ap->size, den.val.ap->size);

    n = nom.val;
    d = den.val;

    n.prec (prec + 3 * Basedigits);
    d.prec (prec + 3 * Basedigits);

    n = n / d;

    n.prec (prec);

    return n;
}
