#include <iomanip>
#include <sstream>
#include <cstring>
#include <cmath>
#include "ap.h"


using namespace std;


const int Maxint = (unsigned) -1 >> 1;
const unsigned Maxunsigned = (unsigned) -1;
const long Maxlong = (unsigned long) -1 >> 1;
const unsigned long Maxunsignedlong = (unsigned long) -1;

rawtype INVALID = 256;

// Numeric value to character, up to base 36
char chartable[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8',
                    '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q',
                    'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

// Character to numeric value, up to base 36
rawtype valuetable[] = {INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID,
                        INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID,
                        INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID,
                        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID,
                        INVALID, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
                        25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, INVALID, INVALID, INVALID, INVALID, INVALID,
                        INVALID, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
                        25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, INVALID, INVALID, INVALID, INVALID, INVALID,
                        INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID,
                        INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID,
                        INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID,
                        INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID,
                        INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID,
                        INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID,
                        INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID,
                        INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID};

// Characters used in exponent notation (do not mix with e.g. hex digits)
const char Expchar[2] = {'e', 'E'};

// Construct an apfloat from an integer
apfloat::apfloat (int value, size_t prec, int location)
{
    int sign;
    size_t t, size;
    long exp;
    modint tmpdata[3], *data;

    if (value > 0)
    {
        sign = 1;
    }
    else if (value < 0)
    {
        sign = -1;
        value = -value;
    }
    else
    {
        ap = new apstruct;
        return;
    }

    if (Base <= Maxint)
    {
        for (size = 0; size < 3 && value > 0; size++)
        {
            tmpdata[2 - size] = (rawtype) (value % (int) Base);
            value /= (int) Base;
        }
    }
    else
    {
        size = 1;                               // Nonzero
        tmpdata[2] = (rawtype) value;
    }

    exp = size;

    if (prec != INFINITE)
    {
        prec = (prec + Basedigits - 1) / Basedigits;
        if (prec < size)
            size = prec;
    }

    while ((rawtype) tmpdata[3 - exp + size - 1] == 0) size--;

    data = new modint[size];

    for (t = 0; t < size; t++)
        data[t] = tmpdata[t + 3 - exp];

    ap = new apstruct (sign, exp, prec, size, data, location);
}

// Construct an apfloat from an unsigned integer
apfloat::apfloat (unsigned value, size_t prec, int location)
{
    int sign;
    size_t t, size;
    long exp;
    modint tmpdata[3], *data;

    if (value > 0)
    {
        sign = 1;
    }
    else
    {
        ap = new apstruct;
        return;
    }

    if (Base <= Maxunsigned)
    {
        for (size = 0; size < 3 && value > 0; size++)
        {
            tmpdata[2 - size] = (rawtype) (value % (unsigned) Base);
            value /= (unsigned) Base;
        }
    }
    else
    {
        size = 1;                               // Nonzero
        tmpdata[2] = (rawtype) value;
    }

    exp = size;

    if (prec != INFINITE)
    {
        prec = (prec + Basedigits - 1) / Basedigits;
        if (prec < size)
            size = prec;
    }

    while ((rawtype) tmpdata[3 - exp + size - 1] == 0) size--;

    data = new modint[size];

    for (t = 0; t < size; t++)
        data[t] = tmpdata[t + 3 - exp];

    ap = new apstruct (sign, exp, prec, size, data, location);
}

// Construct an apfloat from a long integer
apfloat::apfloat (long value, size_t prec, int location)
{
    int sign;
    size_t t, size;
    long exp;
    modint tmpdata[3], *data;

    if (value > 0)
    {
        sign = 1;
    }
    else if (value < 0)
    {
        sign = -1;
        value = -value;
    }
    else
    {
        ap = new apstruct;
        return;
    }

    if (Base <= Maxlong)
    {
        for (size = 0; size < 3 && value > 0; size++)
        {
            tmpdata[2 - size] = (rawtype) (value % (long) Base);
            value /= (long) Base;
        }
    }
    else
    {
        size = 1;                               // Nonzero
        tmpdata[2] = (rawtype) value;
    }

    exp = size;

    if (prec != INFINITE)
    {
        prec = (prec + Basedigits - 1) / Basedigits;
        if (prec < size)
            size = prec;
    }

    while ((rawtype) tmpdata[3 - exp + size - 1] == 0) size--;

    data = new modint[size];

    for (t = 0; t < size; t++)
        data[t] = tmpdata[t + 3 - exp];

    ap = new apstruct (sign, exp, prec, size, data, location);
}

// Construct an apfloat from an unsigned long integer
apfloat::apfloat (unsigned long value, size_t prec, int location)
{
    int sign;
    size_t t, size;
    long exp;
    modint tmpdata[3], *data;

    if (value > 0)
    {
        sign = 1;
    }
    else
    {
        ap = new apstruct;
        return;
    }

    if (Base <= Maxunsignedlong)
    {
        for (size = 0; size < 3 && value > 0; size++)
        {
            tmpdata[2 - size] = (rawtype) (value % (unsigned long) Base);
            value /= (unsigned long) Base;
        }
    }
    else
    {
        size = 1;                               // Nonzero
        tmpdata[2] = (rawtype) value;
    }

    exp = size;

    if (prec != INFINITE)
    {
        prec = (prec + Basedigits - 1) / Basedigits;
        if (prec < size)
            size = prec;
    }

    while ((rawtype) tmpdata[3 - exp + size - 1] == 0) size--;

    data = new modint[size];

    for (t = 0; t < size; t++)
        data[t] = tmpdata[t + 3 - exp];

    ap = new apstruct (sign, exp, prec, size, data, location);
}

// Construct an apfloat from a double
apfloat::apfloat (double value, size_t prec, int location)
{
    int sign;
    size_t t, size;
    long exp;
    double tmp;
    modint tmpdata[4], *data;

    if (value > 0.0)
    {
        sign = 1;
    }
    else if (value < 0.0)
    {
        sign = -1;
        value = -value;
    }
    else
    {
        ap = new apstruct;
        return;
    }

    exp = (long) floor (log (value) / log ((double) Base));

    // Avoid overflow in intermediate value
    if (exp > 0)
    {
        value *= pow ((double) Base, (double) -exp);
    }
    else if (exp < 0)
    {
        value *= pow ((double) Base, (double) (-exp - 4));
        value *= pow ((double) Base, (double) 4);
    }

    exp++;

    for (size = 0; size < 4 && value > 0.0; size++)
    {
        tmp = floor (value);
        tmpdata[size] = (rawtype) tmp;
        value -= tmp;
        value *= Base;
    }

    if (prec == (size_t) DEFAULT)
    {
        // Approximate accuracy of a double
        size_t doubledigits = (size_t) (log (MAX_PRECISE_DOUBLE) / log ((double) Basedigit));

        prec = (doubledigits - (size_t) (log ((double) (rawtype) tmpdata[0]) / log ((double) Basedigit)) + 2 * Basedigits - 1) / Basedigits;
    }
    else
    {
        if (prec != INFINITE)
            prec = (prec + Basedigits - 1) / Basedigits;
    }

    if (prec < size)
        size = prec;

    while ((rawtype) tmpdata[size - 1] == 0) size--;

    data = new modint[size];

    for (t = 0; t < size; t++)
        data[t] = tmpdata[t];

    ap = new apstruct (sign, exp, prec, size, data, location);
}

// Construct an apfloat from a character string
apfloat::apfloat (char *valuestring, size_t prec, int location)
{
    size_t t, r, l, e, d;
    int sign = 1, dot = 0;
    bool nonzero = false;
    size_t intsize = 0, fracsize = 0, leadzeros = 0, size = 0, lastzeros = 0;
    long exp = 0;
    unsigned long tmpexp;
    rawtype val, digit;
    modint *data;
    char c;

    // First scan the size of the number, integer and fractional parts
    // and exponent

    // Sign & whitespace

    for (t = 0; (c = valuestring[t]) != '\0'; t++)
        if (c == '-')
            sign = -sign;
        else if (c != '+' && c != ' ')
            break;

    valuestring += t;

    // Integer part

    for (intsize = 0; (c = valuestring[intsize]) != '\0'; intsize++)
        if (c == '.' || c == Expchar[0] || c == Expchar[1])
            break;
        else if (c == chartable[0])
        {
            if (!nonzero) leadzeros++;
            lastzeros++;
        }
        else
        {
            lastzeros = 0;
            nonzero = true;
        }

    // Fractional part

    if (c == '.')
    {
        dot = 1;
        for (fracsize = 1 + intsize; (c = valuestring[fracsize]) != '\0'; fracsize++)
            if (c == Expchar[0] || c == Expchar[1])
                break;
            else if (c == chartable[0])
            {
                if (!nonzero) leadzeros++;
                lastzeros++;
            }
            else
            {
                lastzeros = 0;
                nonzero = true;
            }
        fracsize -= 1 + intsize;
    }

    // Exponent, always in base 10

    if (c == Expchar[0] || c == Expchar[1])
    {
        istringstream s (valuestring + intsize + dot + fracsize + 1);
        s >> dec >> exp;
    }

    if (!nonzero)
    {
        ap = new apstruct;              // It's zero
        return;
    }

    exp += intsize - leadzeros;
    tmpexp = exp;
    tmpexp += (Maxlong / Basedigits) * Basedigits;

    // Align exponent

    e = tmpexp % Basedigits;
    t = (e ? Basedigits - e : e);

    // Fracional part only or both integer and fractional part

    if (leadzeros >= intsize)
    {
        valuestring += leadzeros + 1;
        l = intsize + fracsize - leadzeros - lastzeros;
        size = (l + t + Basedigits - 1) / Basedigits;
    }
    else
    {
        valuestring += leadzeros;
        l = intsize + fracsize - leadzeros - lastzeros + dot;
        size = (l - dot + t + Basedigits - 1) / Basedigits;
    }

    if (prec == (size_t) DEFAULT)
        prec = size;
    else
    {
        if (prec != INFINITE)
            prec = (prec + Basedigits - 1) / Basedigits;
        if (prec < size)
            size = prec;
    }

    data = new modint[size];

    if (!e) e = Basedigits;

    // Get the actual data

    val = 0;
    for (t = 0, r = 0, d = 0; t < l && d < size; t++)
    {
        if ((c = valuestring[t]) == '.') continue;
        digit = valuetable[(unsigned char) c];
        if (digit == INVALID) digit = 0;        // Ignore invalid characters
        val = val * Basedigit + digit;
        if (++r == e)
        {
            r = 0;
            data[d++] = val;
            val = 0;
            e = Basedigits;
        }
    }

    // Last base unit

    if (r && d < size)
    {
        for (t = r; t < e; t++) val *= Basedigit;
        data[d++] = val;
    }

    exp = (exp >= 0 ? (exp + Basedigits - 1) / Basedigits : exp / Basedigits);

    ap = new apstruct (sign, exp, prec, size, data, location);
}

apfloat::apfloat (const apfloat &d)
{
    ap = d.ap;

    if (!ap) return;

    ap->nlinks++;
}

apfloat::~apfloat ()
{
    if (!ap) return;

    if (!(--(ap->nlinks)))
        delete ap;
}

int apfloat::sign (void) const
{
    if (ap) return ap->sign;
    else return 0;
}

void apfloat::sign (int newsign)
{
    if (!ap) return;

    if (ap->sign == newsign) return;

    unique ();

    ap->sign = newsign;
}

long apfloat::exp (void) const
{
    if (ap) return ap->exp * Basedigits;
    else return 0;
}

void apfloat::exp (long newexp)
{
    if (!ap) return;
    if (!ap->sign) return;              // Zero is zero

    newexp /= Basedigits;

    if (ap->exp == newexp) return;

    unique ();

    ap->exp = newexp;
}

size_t apfloat::prec (void) const
{
    if (ap)
    {
        if (ap->prec == INFINITE)
            return INFINITE;
        else
            return ap->prec * Basedigits;
    }
    else return 0;
}

void apfloat::prec (size_t newprec)
{
    if (!ap) return;
    if (!ap->sign) return;              // Zero is zero

    if (newprec != INFINITE)
        newprec = (newprec + Basedigits - 1) / Basedigits;

    if (ap->prec == newprec) return;

    if (ap->nlinks > 1)
    {
        ap->nlinks--;

        if (newprec < ap->size)
            ap = new apstruct (*ap, newprec - lastzeros (ap, newprec));
        else
            ap = new apstruct (*ap);
    }
    else
    {
        if (newprec < ap->size)
            ap->resize (newprec - lastzeros (ap, newprec));
    }

    ap->prec = newprec;
}

int apfloat::location (void) const
{
    if (ap) return ap->location;
    else return 0;
}

void apfloat::location (int newlocation)
{
    if (!ap) return;

    if (ap->location == newlocation) return;

    unique ();

    ap->relocate (newlocation);
}

void apfloat::unique (void)
{
    if (!ap) return;

    if (ap->nlinks > 1)
    {
        ap->nlinks--;
        ap = new apstruct (*ap);
    }
}

apfloat apfloat::operator+ () const
{
    return *this;
}

apfloat apfloat::operator- () const
{
    apstruct *m = new apstruct (*ap);

    m->sign = -m->sign;

    return apfloat (m);
}


// Definitions of compound-assignment operator member functions

apfloat &apfloat::operator++ ()
{
    *this = *this + apfloat (1);

    return *this;
}

apfloat &apfloat::operator-- ()
{
    *this = *this - apfloat (1);

    return *this;
}

// Post-increment operators by Adam Pawlowski

apfloat apfloat::operator++ (int d)
{
    apfloat tmp = *this;
    ++(*this);

    return tmp;
}

apfloat apfloat::operator-- (int d)
{
    apfloat tmp = *this;
    --(*this);

    return tmp;
}

apfloat &apfloat::operator= (const apfloat &d)
{
    if (ap != d.ap)
    {
        if (ap)
            if (!(--(ap->nlinks)))
                delete ap;

        ap = d.ap;
        if (ap)
            ap->nlinks++;
    }
    return *this;
}


// Definitions of non-member binary operator functions

apfloat operator+ (const apfloat &d1, const apfloat &d2)
{
    return apfloat (apaddsub (d1.ap, d2.ap, 0));
}

apfloat operator- (const apfloat &d1, const apfloat &d2)
{
    return apfloat (apaddsub (d1.ap, d2.ap, 1));
}

apfloat operator* (const apfloat &d1, const apfloat &d2)
{
    assert (d1.ap);
    assert (d2.ap);

    if (d1.ap->size <= 1) return apfloat (apmulshort (d2.ap, d1.ap));
    else if (d2.ap->size <= 1) return apfloat (apmulshort (d1.ap, d2.ap));
    else if (d1.ap->size <= USE_N2_MUL && d1.ap->size <= d2.ap->size) return apfloat (apmulmedium (d2.ap, d1.ap));
    else if (d2.ap->size <= USE_N2_MUL) return apfloat (apmulmedium (d1.ap, d2.ap));
    else return apfloat (apmul (d1.ap, d2.ap));
}

apfloat operator/ (const apfloat &d1, const apfloat &d2)
{
    assert (d1.ap);
    assert (d2.ap);

    if (d2.ap->size <= 1) return apfloat (apdivshort (d1.ap, d2.ap));
    else return d1 * invroot (d2, 1, (d1.prec () < d2.prec () ? d1.prec () : d2.prec ()));
}

bool operator== (const apfloat &d1, const apfloat &d2)
{
    return apcmp (d1.ap, d2.ap) == 0;
}

bool operator!= (const apfloat &d1, const apfloat &d2)
{
    return apcmp (d1.ap, d2.ap) != 0;
}

bool operator>= (const apfloat &d1, const apfloat &d2)
{
    return apcmp (d1.ap, d2.ap) >= 0;
}

bool operator<= (const apfloat &d1, const apfloat &d2)
{
    return apcmp (d1.ap, d2.ap) <= 0;
}

bool operator> (const apfloat &d1, const apfloat &d2)
{
    return apcmp (d1.ap, d2.ap) > 0;
}

bool operator< (const apfloat &d1, const apfloat &d2)
{
    return apcmp (d1.ap, d2.ap) < 0;
}

ostream &pretty (ostream &str)
{
    apfloat::prettyprint = true;

    return str;
}

// Output a base unit in arbitrary base
void baseout (ostream &str, rawtype x, int zerofill = 0)
{
    size_t t;
    char tmp[65];

    tmp[Basedigits] = '\0';

    for (t = Basedigits; t && x > 0;)
        tmp[--t] = chartable[(int) bigdiv (&x, &x, Basedigit, 1)];

    if (zerofill)
    {
        while (t--)
            tmp[t] = chartable[0];
        str << tmp;
    }
    else
    {
        str << (tmp + t);
    }
}

// Output an apfloat to a stream
ostream &operator<< (ostream &str, const apfloat &d)
{
    int f;
    size_t t, p, l, r;
    long e = d.ap->exp;
    modint *data;

    assert (d.ap);

    f = d.ap->sign;
    if (f != 1)
    {
        if (f == -1)
            str << "-";
        else
        {
            str << chartable[0];
            apfloat::prettyprint = false;
            return str;
        }
    }
    f = 0;

    if (apfloat::prettyprint)
    {
        if (e <= 0)
        {
            str << chartable[0] << '.';
            for (; e; e++)
                for (t = Basedigits; t--;)
                    str << chartable[0];
            e--;
            f = 1;
        }
    }
    else
    {
        str << chartable[0] << '.';
        e = -1;
        f = 1;
    }

    p = (d.ap->prec < d.ap->size ? d.ap->prec : d.ap->size);
    r = 0;

    while (p)
    {
        l = (p < Maxblocksize ? p : Maxblocksize);
        p -= l;
        data = d.ap->getdata (r, l);
        r += l;
        for (t = 0; t < l; t++)
        {
            if (!e) str << '.';
            e--;
            baseout (str, (rawtype) data[t], f);
            f = 1;
        }
        d.ap->cleardata ();
    }

    for (; e > 0; e--)
        for (t = Basedigits; t--;)
            str << chartable[0];

    if (!apfloat::prettyprint)
        str << Expchar[0] << d.ap->exp * Basedigits;

    apfloat::prettyprint = false;

    return str;
}

// Flush output buffer if full
void buffercheck (size_t *t, apstruct *ap, modint **data)
{
    if (*t == Memorytreshold)
    {
        if (ap->location == MEMORY)
        {
            // Memory buffer full, relocate to disk since we don't know input size
            ap->relocate (DISK);                    // This does delete[] data
            *data = new modint[Memorytreshold];     // New disk write buffer
        }
        else
        {
            // Flush buffer to disk
            fstream &fs = ap->openstream ();
            fs.seekp (0, ios::end);
            fs.write ((char *) *data, sizeof (modint) * *t);
            assert (fs.good ());
            ap->closestream ();
        }

        *t = 0;
    }
}

// Input an apfloat from a stream
istream &operator>> (istream &str, apfloat &d)
{
    size_t t = 0, r = 0, l, e;
    int sign = 1;
    bool nonzero = false, gotsign = false, gotdot = false, gotexp = false;
    size_t count = 0, intcount = 0, leadzeros = 0, size = 0, zerosize = 0;
    long exp = 0;
    unsigned long tmpexp;
    rawtype val = 0, digit;
    modint *data;
    apstruct *ap;
    char c;

    data = new modint[Memorytreshold];      // Allocate max memory since we don't know input size
    ap = new apstruct (sign, exp, INFINITE, Memorytreshold, data, MEMORY);

    // Whitespace

    str >> ws;

    while ((c = str.get ()) != EOF)
    {
        // Sign

        if (c == '-' && !gotsign)
        {
            sign = -sign;
            gotsign = true;

            continue;
        }
        else if (c == '+' && !gotsign)
        {
            gotsign = true;

            continue;
        }

        // Dot

        if (c == '.' && !gotdot)
        {
            gotdot = true;
            intcount = count;

            if (!size && nonzero)
            {
                // Optimized one base unit integer part
                data[t++] = val;
                size++;
                r = 0;
                val = 0;
            }

            continue;
        }

        // Exponent, always in base 10

        if ((c == Expchar[0] || c == Expchar[1]) && !gotexp)
        {
            gotexp = true;
            if (!(str >> dec >> exp))
                size = 0;               // Error inputting exponent

            break;
        }

        // Valid digit?

        digit = valuetable[(unsigned char) c];
        if (digit >= Basedigit || digit == INVALID)
        {
            str.putback (c);

            break;            // Stop at first invalid character
        }

        // Integer or fractional part

        if (c == chartable[0])
        {
            if (!nonzero)
            {
                leadzeros++;

                if (!gotdot)
                {
                    count++;
                    continue;           // Skip leading zeros before decimal point
                }
            }
        }
        else
        {
            nonzero = true;
        }

        // Get the actual data

        val = val * Basedigit + valuetable[(unsigned char) c];
        if (++r == Basedigits)
        {
            if (nonzero)
            {
                buffercheck (&t, ap, &data);

                data[t++] = val;
                size++;

                if (val == 0)
                    zerosize++;
                else
                    zerosize = 0;
            }

            r = 0;
            val = 0;
        }

        count++;
    }

    if (!count)
    {
        delete ap;                              // No valid input
        str.clear (ios::failbit);
        return str;
    }

    if (!nonzero)
    {
        delete ap;
        d = apfloat (new apstruct);             // It's zero
        return str;
    }

    if (!gotdot)
        intcount = count;

    // Last base unit

    if (r && val != 0)
    {
        buffercheck (&t, ap, &data);

        if (size || intcount <= leadzeros)      // Not first integer part base unit
            for (; r < Basedigits; r++)
                val *= Basedigit;

        data[t++] = val;
        size++;
        zerosize = 0;
    }

    if (ap->location != MEMORY)
    {
        // Flush buffer to disk
        fstream &fs = ap->openstream ();
        fs.seekp (0, ios::end);
        fs.write ((char *) data, sizeof (modint) * t);
        assert (fs.good ());
        ap->closestream ();

        // Deallocate disk write buffer
        delete[] data;

        // Size is now > Memorytreshold
        // Set the size to the actual size including trailing zeros
        ap->size = size;
    }

    // Align exponent

    t = Maxlong / Basedigits;
    l = t * Basedigits;

    if (intcount <= leadzeros)
    {
        // Fractional part only
        tmpexp = (leadzeros - intcount) / Basedigits;
        e = (exp + l) % Basedigits;
        exp = (exp + l) / Basedigits - t - tmpexp;
    }
    else if (intcount < leadzeros + Basedigits)
    {
        // One integer base unit
        tmpexp = 1;
        e = (exp + l) % Basedigits;
        exp = (exp + l) / Basedigits - t + tmpexp;
    }
    else
    {
        // More than 1 integer base unit
        tmpexp = intcount - leadzeros;
        e = tmpexp % Basedigits;
        tmpexp = tmpexp / Basedigits;
        e += (exp + l) % Basedigits;
        exp = (exp + l) / Basedigits - t + tmpexp;
        if (e >= Basedigits)
        {
            e -= Basedigits;
            exp++;
        }
    }

    ap->sign = sign;
    ap->exp = exp;

    // Calculate actual size (ignoring leading and trailing zeros)

    size -= zerosize;
    ap->resize (size);                  // Set actual size, removing trailing zeros

    if (e)
        d = apfloat (ap) * pow (apfloat ((int) Basedigit), e);
    else
        d = apfloat (ap);

    d.prec (d.ap->size * Basedigits);   // Set precision to the same as size

    return str;
}

// Retrieve an apfloat from disk, essentially deletes the file
void apfloat::swapfrom (const char *filename)
{
    *this = apfloat (apswapfrom (filename));
}

// Store an apfloat to disk, deleting the object from memory
void apfloat::swapto (const char *newfilename)
{
    unique ();

    apswapto (ap, newfilename);

    ap = 0;
}
