#include <cmath>
#include "ap.h"
#include "apcplx.h"


using namespace std;


#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Overloaded mathematical functions

inline size_t min (size_t a, size_t b)
{
    return (a < b ? a : b);
}

inline size_t max (size_t a, size_t b)
{
    return (a > b ? a : b);
}


// Absolute value
apfloat abs (apcomplex z)
{
    return sqrt (norm (z));
}

// Positive integer power
// Algorithm improvements by Bernd Kellner
apcomplex pow (apcomplex base, unsigned long exp)
{
    apcomplex r;
    int b2pow = 0;

    if (!exp) return 1;

    while (!(exp & 1))
    {
        b2pow++;
        exp >>= 1;
    }
    r = base;

    while (exp >>= 1)
    {
        base *= base;
        if (exp & 1) r *= base;
    }

    while (b2pow--)
        r *= r;

    return r;
}

apcomplex pow (apcomplex base, unsigned exp)
{
    return pow (base, (unsigned long) exp);
}

// Integer power
apcomplex pow (apcomplex base, long exp)
{
    if (exp < 0)
        return 1 / pow (base, (unsigned long) -exp);
    else
        return pow (base, (unsigned long) exp);
}

apcomplex pow (apcomplex base, int exp)
{
    if (exp < 0)
        return 1 / pow (base, (unsigned long) -exp);
    else
        return pow (base, (unsigned long) exp);
}

// Square root
apcomplex sqrt (apcomplex z)
{
    if (!z.re.sign () && !z.im.sign ())
        return apfloat (new apstruct);          // Avoid division by zero
    else
        return z * invroot (z, 2);
}

// Cube root
apcomplex cbrt (apcomplex z)
{
    if (!z.re.sign () && !z.im.sign ())
        return apfloat (new apstruct);          // Avoid division by zero
    else
        return z * invroot (z * z, 3);
}

// Inverse positive integer root
apcomplex invroot (apcomplex u, unsigned n)
{
    size_t prec, minprec, maxprec, destprec = u.prec (), doubledigits, fprec;
    int k, f;
    long p, r1, r2, expdiff;
    apfloat one = 1, d = n;
    apfloat x, y;
    apcomplex z;
    double r, i, m, a, dx, dy;

    if (!n) return 1;

    assert (u.re.sign () || u.im.sign ());      // Infinity

    // Approximate accuracy of a double
    doubledigits = (size_t) (log (MAX_PRECISE_DOUBLE) / log ((double) Basedigit));

    // Initial guess accuracy
    fprec = max (doubledigits, 2 * Basedigits);

    expdiff = u.re.exp () - u.im.exp ();

    if (labs (expdiff) <= Basedigits)
    {
        x = u.re;
        y = u.im;

        x.exp (expdiff);
        y.exp (0);

        dx = fabs (ap2double (x.ap));
        dy = fabs (ap2double (y.ap));
    }

    // Calculate initial guess from u
    if (!u.im.sign () ||
        (u.re.sign () && (expdiff > Basedigits ||
                          expdiff >= 0 && dx >= dy * sqrt (MAX_PRECISE_DOUBLE))))
    {
        // Re z >> Im z
        apcomplex t;

        p = u.re.ap->exp / (long) n;
        r1 = u.re.ap->exp - p * (long) n;

        x = u.re;
        x.prec (fprec);
        y = u.im;
        y.prec (fprec);
        t = apcomplex (0, y / (d * x));

        x.exp (Basedigits * r1);        // Allow exponents in exess of doubles'

        if ((m = ap2double (x.ap)) >= 0.0)
        {
            r = pow (m, -1.0 / (double) n);
            i = 0.0;
        }
        else
        {
            m = pow (-m, -1.0 / (double) n);
            a = (y.sign () >= 0 ? -M_PI : M_PI) / (double) n;
            r = m * cos (a);
            i = m * sin (a);
        }

        x = apfloat (r, fprec);
        y = apfloat (i, fprec);
        x.exp (x.exp () - p * Basedigits);
        y.exp (y.exp () - p * Basedigits);
        z = apcomplex (x, y);
        z -= z * t;                     // Must not be real
    }
    else if (!u.re.sign () ||
             (u.im.sign () && (expdiff < -Basedigits ||
                               expdiff <= 0 && dy >= dx * sqrt (MAX_PRECISE_DOUBLE))))
    {
        // Im z >> Re z
        apcomplex t;

        p = u.im.ap->exp / (long) n;
        r1 = u.im.ap->exp - p * (long) n;

        x = u.re;
        x.prec (fprec);
        y = u.im;
        y.prec (fprec);
        t = apcomplex (0, x / (d * y));

        y.exp (Basedigits * r1);        // Allow exponents in exess of doubles'

        if ((m = ap2double (y.ap)) >= 0.0)
        {
            m = pow (m, -1.0 / (double) n);
            a = -M_PI / (double) (2 * n);
        }
        else
        {
            m = pow (-m, -1.0 / (double) n);
            a = M_PI / (double) (2 * n);
        }

        r = m * cos (a);
        i = m * sin (a);

        x = apfloat (r, fprec);
        y = apfloat (i, fprec);
        x.exp (x.exp () - p * Basedigits);
        y.exp (y.exp () - p * Basedigits);
        z = apcomplex (x, y);
        z += z * t;                     // Must not be pure imaginary
    }
    else
    {
        // Im z and Re z approximately the same

        p = u.re.ap->exp / (long) n;
        r1 = u.re.ap->exp - p * (long) n;
        r2 = u.im.ap->exp - p * (long) n;

        x = u.re;
        x.prec (fprec);
        x.exp (Basedigits * r1);        // Allow exponents in exess of doubles'

        y = u.im;
        y.prec (fprec);
        y.exp (Basedigits * r2);        // Allow exponents in exess of doubles'

        r = ap2double (x.ap);
        i = ap2double (y.ap);
        m = pow (r * r + i * i, -1.0 / (double) (2 * n));
        a = -atan2 (i, r) / (double) n;

        r = m * cos (a);
        i = m * sin (a);

        x = apfloat (r, fprec);
        y = apfloat (i, fprec);
        x.exp (x.exp () - p * Basedigits);
        y.exp (y.exp () - p * Basedigits);
        z = apcomplex (x, y);
    }

    prec = min (doubledigits, Basedigits);

    // Check if a factor of 3 should be used in length
    maxprec = rnd23up (destprec / Basedigits);
    if (maxprec != (maxprec & -maxprec))
        minprec = 3 * Basedigits;
    else
        minprec = Basedigits;

    // Highly ineffective unless precision is 2^n * Basedigits (or 3*2^n)
    if (prec < minprec)
    {
        z.re.prec (minprec + 3 * Basedigits);
        z.im.prec (minprec + 3 * Basedigits);
        while (prec < minprec)
        {
            z += z * (one - u * pow (z, n)) / d;
            prec *= 2;
        }
        prec = minprec;
    }

    // Check where the precising iteration should be done
    for (k = 0, maxprec = prec; maxprec < destprec; k++, maxprec <<= 1);
    for (f = k, minprec = prec; f; f--, minprec <<= 1)
        if (minprec >= 2 * Basedigits && (minprec - 2 * Basedigits) << f >= destprec)
            break;

    // Newton's iteration
    while (k--)
    {
        apcomplex t;

        prec *= 2;
        z.re.prec (min (prec, destprec));
        z.im.prec (min (prec, destprec));

        t = one - u * pow (z, n);
        if (k < f)
        {
            t.re.prec (prec / 2);
            t.im.prec (prec / 2);
        }

        if (n > 1)
            z += z * t / d;
        else
            z += z * t;

        // Precising iteration
        if (k == f)
        {
            if (n > 1)
                z += z * (one - u * pow (z, n)) / d;
            else
                z += z * (one - u * pow (z, n));
        }
    }

    z.re.prec (destprec);
    z.im.prec (destprec);

    return z;
}

// Arithmetic-geometric mean
apcomplex agm (apcomplex a, apcomplex b)
{
    apcomplex t;
    size_t prec = 0, destprec = min (a.prec (), b.prec ());

    if ((!a.re.sign () && !a.im.sign ()) || (!b.re.sign () && !b.im.sign ()))   // Would not converge quadratically
        return apfloat (new apstruct);      // Zero

    // Precision must be at least 2 * Basedigits
    if (destprec <= Basedigits)
    {
        destprec = 2 * Basedigits;
        a.re.prec (max (a.re.prec (), destprec));
        a.im.prec (max (a.im.prec (), destprec));
        b.re.prec (max (b.re.prec (), destprec));
        b.im.prec (max (b.im.prec (), destprec));
    }

    // First check convergence
    while (prec < Basedigits * Blocksize && 2 * prec < destprec)
    {
        t = (a + b) / 2;
        b = sqrt (a * b);
        a = t;

        // Conserve precision in case of accumulating round-off errors
        a.re.prec (max (a.re.prec (), destprec));
        a.im.prec (max (a.im.prec (), destprec));
        b.re.prec (max (b.re.prec (), destprec));
        b.im.prec (max (b.im.prec (), destprec));

        prec = Basedigits * min (apeq (a.re.ap, b.re.ap), apeq (a.im.ap, b.im.ap));
    }

    // Now we know quadratic convergence
    while (2 * prec <= destprec)
    {
        t = (a + b) / 2;
        b = sqrt (a * b);
        a = t;

        // Conserve precision in case of accumulating round-off errors
        a.re.prec (max (a.re.prec (), destprec));
        a.im.prec (max (a.im.prec (), destprec));
        b.re.prec (max (b.re.prec (), destprec));
        b.im.prec (max (b.im.prec (), destprec));

        prec *= 2;
    }

    return (a + b) / 2;
}

// Raw logarithm, regardless of z
// Doesn't work for really big z, but is faster if used alone for small numbers
apcomplex rawlog (apcomplex z)
{
    size_t destprec = z.prec ();
    long n = destprec / 2 + 2 * Basedigits;     // Rough estimate
    apfloat e, agme;
    apcomplex agmez;

    assert (z.re.sign () || z.im.sign ());              // Infinity

    e = apfloat (1, destprec);
    e.exp (e.exp () - n);
    z.re.exp (z.re.exp () - n);
    z.im.exp (z.im.exp () - n);

    agme = agm (1, e);
    agmez = agm (apcomplex (1), z);

    checkpi (destprec);

    return Readypi * (agmez - agme) / (2 * agme * agmez);
}

// Calculate the log using 1 / Base <= |z| < 1 and the log addition formula
// because the agm converges badly for really big z
apcomplex log (apcomplex z)
{
    size_t destprec = z.prec ();
    long tmpexp;
    apfloat t;

    if (!z.re.sign ())
        tmpexp = z.im.exp ();
    else if (!z.im.sign ())
        tmpexp = z.re.exp ();
    else
    {
        tmpexp = z.re.exp ();
        if (z.im.exp () > tmpexp) tmpexp = z.im.exp ();
    }

    checklogconst (destprec);

    z.re.exp (z.re.exp () - tmpexp);
    z.im.exp (z.im.exp () - tmpexp);

    t = Logbase;
    t.prec (destprec + Basedigits);

    return rawlog (z) + tmpexp * t;
}

// Check for flip of sign of the imaginary part near +-pi
void checkimsign (apcomplex x, apcomplex *y, apfloat twopi)
{
    double dx, dy;

    dx = ap2double (x.im.ap);
    dy = ap2double (y->im.ap);

    if (M_PI - fabs (dx) <= 1.0 / sqrt (MAX_PRECISE_DOUBLE) &&
        M_PI - fabs (dy) <= 1.0 / sqrt (MAX_PRECISE_DOUBLE) &&
        dx * dy < 0.0)
    {
        // Both imaginary parts are near +-pi and of opposite sign
        if (y->im.sign () < 0)
            y->im += twopi;
        else
            y->im -= twopi;
    }
}

// Calculate needed precision for Readypi
size_t piprec (apcomplex *z)
{
    size_t prec;

    prec = z->im.prec ();

    if (prec != INFINITE)
    {
        prec -= z->im.exp () - Basedigits;
        if ((long) prec < Basedigits)
            prec = Basedigits;
    }

    if (prec == INFINITE)
        prec = z->prec ();

    return prec;
}

// Exponent function, calculated using Newton's iteration for the inverse of log
apcomplex exp (apcomplex u)
{
    size_t prec, minprec, maxprec, destprec = u.prec (), pprec = piprec (&u), doubledigits, fprec;
    int k, f;
    double d;
    apfloat x, y, twopi;
    apcomplex z, t;

    if (!u.re.sign () && !u.im.sign ()) return apcomplex (1);

    checkpi (pprec);

    twopi = Readypi;
    twopi.prec (pprec);
    twopi += twopi;

    // Approximate accuracy of a double
    doubledigits = (size_t) (log (MAX_PRECISE_DOUBLE) / log ((double) Basedigit));

    // Initial guess accuracy
    fprec = max (doubledigits, 2 * Basedigits);

    // First handle the real part
    if (!u.re.sign ())
    {
        x = 1;
    }
    else if (u.re.exp () < -Basedigits)
    {
        // Taylor series: exp(x) = 1 + x + x^2/2 + ...

        x = u.re;
        x.prec (doubledigits);
        x += 1;
    }
    else
    {
        // Approximate starting value for iteration
        double i, f;

        // If u.re is too big, an overflow will occur (somewhere)
        d = ap2double (u.re.ap);
        i = floor (d);
        f = d - i;

        d = i / log ((double) Base);

        x = apfloat (exp (f) * pow ((double) Base, d - floor (d)), fprec);
        x.exp (x.exp () + Basedigits * (long) floor (d));
    }

    // Then handle the imaginary part
    u.im = fmod (u.im, twopi);
    if (u.im > Readypi)
        u.im -= twopi;
    else if (u.im <= -Readypi)
        u.im += twopi;

    // Re-calculate destination precision as u.im may have changed considerably
    destprec = min (destprec, piprec (&u));
    destprec = min (destprec, pprec);
    checklogconst (destprec);

    d = ap2double (u.im.ap);

    if (fabs (d) <= 1.0 / sqrt (MAX_PRECISE_DOUBLE))
    {
        // Taylor series: exp(z) = 1 + z + z^2/2 + ...

        y = u.im;
        y.prec (doubledigits);
        z = apcomplex (1, y);
    }
    else if (M_PI - fabs (d) <= 1.0 / sqrt (MAX_PRECISE_DOUBLE))
    {
        // exp(z + i*pi) = exp(z)*exp(i*pi) = -exp(z)
        // exp(z - i*pi) = exp(z)/exp(i*pi) = -exp(z)
        // Taylor series: exp(z) = 1 + z + z^2/2 + ...

        y = u.im;

        if (y.sign () < 0)
            y = y + Readypi;
        else
            y = y - Readypi;

        y.sign (-y.sign ());
        y.prec (doubledigits);

        z = apcomplex (-1, y);
    }
    else
    {
        // Approximate starting value for iteration

        z = apcomplex (apfloat (cos (d), fprec), apfloat (sin (d), fprec));
    }

    z *= x;

    prec = min (doubledigits, Basedigits);

    // Check if a factor of 3 should be used in length
    maxprec = rnd23up (destprec / Basedigits);
    if (maxprec != (maxprec & -maxprec))
        minprec = 3 * Basedigits;
    else
        minprec = Basedigits;

    // Highly ineffective unless precision is 2^n * Basedigits (or 3*2^n)
    if (prec < minprec)
    {
        z.re.prec (minprec + 3 * Basedigits);
        z.im.prec (minprec + 3 * Basedigits);
        while (prec < minprec)
        {
            t = log (z);
            checkimsign (u, &t, twopi);

            z += z * (u - t);
            prec *= 2;
        }
        prec = minprec;
    }

    // Check where the precising iteration should be done
    for (k = 0, maxprec = prec; maxprec < destprec; k++, maxprec <<= 1);
    for (f = k, minprec = prec; f; f--, minprec <<= 1)
        if (minprec >= 3 * Basedigits && (minprec - 3 * Basedigits) << f >= destprec)
            break;

    // Newton's iteration
    while (k--)
    {
        prec *= 2;
        // Complex log needs a bit extra precision for convergence
        z.re.prec (max (4 * Basedigits, min (prec, destprec)));
        z.im.prec (max (4 * Basedigits, min (prec, destprec)));

        t = log (z);
        checkimsign (u, &t, twopi);

        t = u - t;
        if (k < f)
        {
            t.re.prec (prec / 2);
            t.im.prec (prec / 2);
        }

        z += z * t;

        // Precising iteration
        if (k == f)
        {
            t = log (z);
            checkimsign (u, &t, twopi);

            z += z * (u - t);
        }
    }

    z.re.prec (destprec);
    z.im.prec (destprec);

    return z;
}

// Arbitrary power, calculated using log and exp
apcomplex pow (apcomplex z, apcomplex w)
{
    size_t destprec = min (z.prec (), w.prec ());

    checklogconst (destprec);

    z.re.prec (destprec);
    z.im.prec (destprec);

    return exp (w * log (z));
}

apcomplex pow (apcomplex z, apfloat y)
{
    size_t destprec = min (z.prec (), y.prec ());

    checklogconst (destprec);

    z.re.prec (destprec);
    z.im.prec (destprec);

    return exp (y * log (z));
}

apcomplex pow (apfloat x, apcomplex w)
{
    size_t destprec = min (x.prec (), w.prec ());

    checklogconst (destprec);

    x.prec (destprec);

    return exp (w * log (x));
}


// Trigonometric and hyperbolic functions and their inverses

apcomplex acos (apcomplex z)
{
    apcomplex i = apcomplex (0, 1), w;

    if (z.re.sign () >= 0)
        w = i * log (z + sqrt (z * z - 1));
    else
        w = -i * log (z - sqrt (z * z - 1));

    if (z.re.sign () * z.im.sign () >= 0)
        return -w;
    else
        return w;
}

apcomplex acosh (apcomplex z)
{
    apcomplex w;

    if (z.re.sign () >= 0)
        return log (z + sqrt (z * z - 1));
    else
        return log (z - sqrt (z * z - 1));
}

apcomplex asin (apcomplex z)
{
    apcomplex i = apcomplex (0, 1);

    if (z.im.sign () >= 0)
        return i * log (sqrt (1 - z * z) - i * z);
    else
        return -i * log (i * z + sqrt (1 - z * z));
}

apcomplex asinh (apcomplex z)
{
    if (z.re.sign () >= 0)
        return log (sqrt (z * z + 1) + z);
    else
        return -log (sqrt (z * z + 1) - z);
}

apcomplex atan (apcomplex z)
{
    apcomplex i = apcomplex (0, 1);

    return log ((i + z) / (i - z)) * i / 2;
}

apcomplex atanh (apcomplex z)
{
    return log ((1 + z) / (1 - z)) / 2;
}

apcomplex cos (apcomplex z)
{
    apcomplex i = apcomplex (0, 1);
    apcomplex w = exp (i * z);

    return (w + 1 / w) / 2;
}

apcomplex cosh (apcomplex z)
{
    apcomplex w = exp (z);

    return (w + 1 / w) / 2;
}

apcomplex sin (apcomplex z)
{
    apcomplex i = apcomplex (0, 1);
    apcomplex w = exp (i * z);

    return (1 / w - w) * i / 2;
}

apcomplex sinh (apcomplex z)
{
    apcomplex w = exp (z);

    return (w - 1 / w) / 2;
}

apcomplex tan (apcomplex z)
{
    apcomplex i = apcomplex (0, 1);
    apcomplex w = exp (2 * i * z);

    return i * (1 - w) / (1 + w);
}

apcomplex tanh (apcomplex z)
{
    apcomplex w = exp (2 * z);

    return (w - 1) / (w + 1);
}


// Real trigonometric and hyperbolic functions and their inverses
// use complex functions

apfloat acos (apfloat x)
{
    apcomplex i = apcomplex (0, 1);

    return imag (log (x + i * sqrt (1 - x * x)));
}

apfloat asin (apfloat x)
{
    apcomplex i = apcomplex (0, 1);

    return -imag (log (sqrt (1 - x * x) - i * x));
}

apfloat atan (apfloat x)
{
    apcomplex i = apcomplex (0, 1);

    return imag (log ((i - x) / (i + x))) / 2;
}

apfloat atan2 (apfloat x, apfloat y)
{
    long tmpexp;
    apfloat t;

    if (!x.sign ())
    {
        assert (y.sign ());

        checkpi (y.prec ());

        t = Readypi;
        t.prec (y.prec ());

        return y.sign () * t / 2;
    }
    else if (!y.sign ())
    {
        if (x.sign () > 0) return 0;

        checkpi (x.prec ());

        t = Readypi;
        t.prec (x.prec ());

        return t;
    }
    else
    {
        tmpexp = x.exp ();
        if (y.exp () > tmpexp) tmpexp = y.exp ();
    }

    x.exp (x.exp () - tmpexp);
    y.exp (y.exp () - tmpexp);

    return imag (rawlog (apcomplex (x, y)));
}

apfloat cos (apfloat x)
{
    return real (exp (apcomplex (0, x)));
}

apfloat sin (apfloat x)
{
    return imag (exp (apcomplex (0, x)));
}

apfloat tan (apfloat x)
{
    apcomplex w = exp (apcomplex (0, x));

    return imag (w) / real (w);
}
