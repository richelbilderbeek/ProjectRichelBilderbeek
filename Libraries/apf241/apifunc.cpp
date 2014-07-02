#include "ap.h"
#include "apint.h"


// Overloaded apint functions


// Positive integer power
// Algorithm improvements by Bernd Kellner
apint pow (apint base, unsigned long exp)
{
    apint r = base;
    int b2pow = 0;

    if (!exp) return 1;

    while (!(exp & 1))
    {
        b2pow++;
        exp >>= 1;
    }

    while (exp >>= 1)
    {
        base *= base;
        if (exp & 1) r *= base;
    }

    while (b2pow--)
        r *= r;

    return r;
}

apint pow (apint base, unsigned exp)
{
    return pow (base, (unsigned long) exp);
}

// Integer power
apint pow (apint base, long exp)
{
    if (exp < 0)
        return 0;
    else
        return pow (base, (unsigned long) exp);
}

apint pow (apint base, int exp)
{
    if (exp < 0)
        return 0;
    else
        return pow (base, (unsigned long) exp);
}

// Absolute value
apint abs (apint x)
{
    if (x.sign () >= 0)
        return x;
    else
        return -x;
}

// Quotient and remainder
apdiv_t div (apint numer, apint denom)
{
    size_t s;
    apfloat q, r, a, b, tx, ty;
    apdiv_t v;

    assert (denom.sign ());

    a = abs (numer.val);
    b = abs (denom.val);

    if (a < b)
    {
        v.quot = 0;
        v.rem = numer;

        return v;                   // abs (numer) < abs (denom)
    }
    else
        s = numer.exp () - denom.exp () + 3 * Basedigits;   // Some extra precision

    tx = numer.val;
    ty = denom.val;

    tx.prec (s);
    ty.prec (s);

    q = tx / ty;                    // Approximate division
    q = apfloat (apabsfloor (q.ap));

    a = abs (numer) - abs (q * denom);

    if (a >= b)                     // Fix division round-off error
    {
        q += numer.sign () * denom.sign();
        a -= b;
    }
    else if (a < 0)                 // Fix division round-off error
    {
        q -= numer.sign () * denom.sign();
        a += b;
    }

    r = numer.sign () * a;

    v.quot = q;
    v.rem = r;

    return v;
}

// Factorial, or n * (n+1) * (n+2) * ... * m
apint factorial (unsigned long n, unsigned long m)
{
    if (n > m)
        return factorial (m, n);
    else if (m == 0)
        return 1;
    else if (n == m)
        return n;
    else
        return factorial (n, (n + m) / 2) * factorial ((n + m) / 2 + 1, m);
}

// Greatest common divisor
apint gcd (apint a, apint b)
{
    while (b.sign ())
    {
        apint r = a % b;
        a = b;
        b = r;
    }

    return abs (a);
}

// Least common multiple
apint lcm (apint a, apint b)
{
    return a * b / gcd (a, b);
}

// Integer power modulo a modulus

// The multiplication assumes x < m, y < m, invm.prec () = 2 * m.exp () + 3 * Basedigits
apint modmul (apint x, apint y, apint m, apfloat invm = apfloat ())
{
    if (!invm.ap)
    {
        return x * y % m;
    }
    else
    {
        apint t, a, b;

        if (!m.sign ())
            return 0;                   // By definition

        x *= y;

        a = abs (x);
        b = abs (m);

        if (a < b)
            return x;                   // abs (x) < abs (m)

        t.val = x * invm;               // Approximate division
        t.val = apfloat (apabsfloor (t.val.ap));

        a = a - abs (t * m);

        if (a >= b)                     // Fix division round-off error
            a -= b;
        else if (a < 0)                 // Fix division round-off error
            a += b;

        t = x.sign () * a;

        return t;
    }
}

apint powmod (apint base, apint exp, apint modulus)
{
    int divbits = 0, i;
    apint r = 1, m, b2 = 1;
    apdiv_t v, s;
    apfloat invm;

    v.quot = exp;

    if (!exp.sign ()) return 1;

    if (!modulus.sign ())
        return 0;                       // By definition

    invm = invroot (modulus.val, 1, 2 * modulus.exp () + 3 * Basedigits);   // Some extra precision
    base %= modulus;

    while ((m = b2 + b2).exp () == Basedigits)
    {
        b2 = m;
        divbits++;
    }

    while ((v = div (v.quot, b2)).quot.sign ())
    {
        for (i = 0; i < divbits; i++)
        {
            if ((s = div (v.rem, 2)).rem.sign ()) r = modmul (r, base, modulus, invm);
            base = modmul (base, base, modulus, invm);
            v.rem = s.quot;
        }
    }

    while (v.rem.sign ())
    {
        if ((s = div (v.rem, 2)).rem.sign ()) r = modmul (r, base, modulus, invm);
        v.rem = s.quot;
        if ((v.rem.sign ())) base = modmul (base, base, modulus, invm);
    }

    return r;
}
