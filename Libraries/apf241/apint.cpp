#include "ap.h"
#include "apint.h"


using namespace std;


extern rawtype INVALID;
extern char chartable[];
extern rawtype valuetable[];
void buffercheck (size_t *t, apstruct *ap, modint **data);

apint operator/ (const apint &d1, const apint &d2)
{
    size_t s;
    apfloat t, a, b, tx, ty;

    assert (d2.sign ());

    a = abs (d1.val);
    b = abs (d2.val);

    if (a < b)
        return 0;                   // abs (d1) < abs (d2)
    else
        s = d1.exp () - d2.exp () + 3 * Basedigits;     // Some extra precision

    tx = d1.val;
    ty = d2.val;

    tx.prec (s);
    ty.prec (s);

    t = tx / ty;                    // Approximate division
    t = apfloat (apabsfloor (t.ap));

    a = a - abs (t * d2.val);

    if (a >= b)                     // Fix division round-off error
        t += d1.sign () * d2.sign();
    else if (a < 0)                 // Fix division round-off error
        t -= d1.sign () * d2.sign();

    return t;
}

apint operator% (const apint &d1, const apint &d2)
{
    return fmod (d1.val, d2.val);
}

// Input an apint from a stream
istream &operator>> (istream &str, apint &d)
{
    size_t t = 0, r = 0, e;
    int sign = 1;
    bool nonzero = false, gotsign = false;
    size_t count = 0, leadzeros = 0, size = 0, zerosize = 0;
    long exp = 0;
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

        // Valid digit?

        digit = valuetable[(unsigned char) c];
        if (digit >= Basedigit || digit == INVALID)
        {
            str.putback (c);

            break;            // Stop at first invalid character
        }

        // Integer part

        if (c == chartable[0])
        {
            if (!nonzero)
            {
                leadzeros++;
                count++;

                continue;           // Skip leading zeros
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
        d.val = apfloat (new apstruct);         // It's zero
        return str;
    }

    // Last base unit

    if (r && val != 0)
    {
        buffercheck (&t, ap, &data);

        if (size)                               // Not first base unit
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

    if (count < leadzeros + Basedigits)
    {
        // One integer base unit
        e = 0;
        exp = 1;
    }
    else
    {
        // More than 1 integer base unit
        exp = count - leadzeros;
        e = exp % Basedigits;
        exp = exp / Basedigits;
    }

    ap->sign = sign;
    ap->exp = exp;

    // Calculate actual size (ignoring leading and trailing zeros)

    size -= zerosize;
    ap->resize (size);                  // Set actual size, removing trailing zeros

    if (e)
        d.val = apfloat (ap) * pow (apfloat ((int) Basedigit), e);
    else
        d.val = apfloat (ap);

    return str;
}

// Increment and decrement operators by Adam Pawlowski

apint &apint::operator++ ()
{
    *this = *this + apint (1);

    return *this;
}

apint &apint::operator-- ()
{
    *this = *this - apint (1);

    return *this;
}

apint apint::operator++ (int d)
{
    apint tmp = *this;
    ++(*this);

    return tmp;
}

apint apint::operator-- (int d)
{
    apint tmp = *this;
    --(*this);

    return tmp;
}
