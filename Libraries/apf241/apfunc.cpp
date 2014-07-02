#include <cmath>
#include "ap.h"


using namespace std;


#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


// Overloaded apfloat functions


// Constants needed for log & exp
apfloat Readypi;
apfloat PiA, PiB, PiJ, Pione, Pitwo, Pifive, Pisix;
apfloat ReadyT;
apfloat ReadyQ;
apfloat ReadyP;
apfloat Readyinvroot;
size_t  Readypiterms;
rawtype ReadypiBase;
apfloat Logbase;
rawtype LogbaseBase;

inline size_t min (size_t a, size_t b)
{
    return (a < b ? a : b);
}

inline size_t max (size_t a, size_t b)
{
    return (a > b ? a : b);
}


// Positive integer power
// Algorithm improvements by Bernd Kellner
apfloat pow (apfloat base, unsigned long exp)
{
    apfloat r;
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

apfloat pow (apfloat base, unsigned exp)
{
    return pow (base, (unsigned long) exp);
}

// Integer power
apfloat pow (apfloat base, long exp)
{
    if (exp < 0)
        return invroot (pow (base, (unsigned long) -exp), 1);
    else
        return pow (base, (unsigned long) exp);
}

apfloat pow (apfloat base, int exp)
{
    if (exp < 0)
        return invroot (pow (base, (unsigned long) -exp), 1);
    else
        return pow (base, (unsigned long) exp);
}

// Square root
apfloat sqrt (apfloat x)
{
    if (!x.sign ())
        return apfloat (new apstruct);          // Avoid division by zero
    else
        return x * invroot (x, 2);
}

// Cube root
apfloat cbrt (apfloat x)
{
    if (!x.sign ())
        return apfloat (new apstruct);          // Avoid division by zero
    else
        return x * invroot (x * x, 3);
}

// Positive integer root
apfloat root (apfloat x, unsigned n)
{
    if (!x.sign ())
        return apfloat (new apstruct);          // Avoid division by zero
    else
        return 1 / invroot (x, n);
}

// Inverse positive integer root
apfloat invroot (apfloat u, unsigned n, size_t destprec, apfloat initguess, size_t initprec)
{
    size_t prec, minprec, maxprec, doubledigits, fprec;
    int k, f;
    long p, r;
    apfloat one = 1, d = n, x;

    if (!n) return 1;

    assert (u.sign ());                         // Infinity

    if (!(n & 1))
        assert (u.sign () > 0);                 // Complex result

    if (destprec == (size_t) DEFAULT) destprec = u.prec ();

    // Approximate accuracy of a double
    doubledigits = (size_t) (log (MAX_PRECISE_DOUBLE) / log ((double) Basedigit));

    // Initial guess accuracy
    fprec = max (doubledigits, 2 * Basedigits);

    if (!initguess.ap)
    {
        p = u.ap->exp / (long) n;
        r = u.ap->exp - p * (long) n;

        x = u;
        x.prec (fprec);
        x.exp (Basedigits * r);         // Allow exponents in exess of doubles'

        // No initial guess, calculate it from u
        x = apfloat (pow (ap2double (x.ap), -1.0 / (double) n), fprec);
        x.exp (x.exp () - p * Basedigits);

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
            x.prec (minprec + 3 * Basedigits);
            while (prec < minprec)
            {
                x += x * (one - u * pow (x, n)) / d;
                prec *= 2;
            }
            prec = minprec;
        }
    }
    else
    {
        // Take initial guess
        x = initguess;

        if (initprec == (size_t) DEFAULT)
            prec = initguess.prec ();
        else
            prec = initprec;
    }

    // Check where the precising iteration should be done
    for (k = 0, maxprec = prec; maxprec < destprec; k++, maxprec <<= 1);
    for (f = k, minprec = prec; f; f--, minprec <<= 1)
        if (minprec >= 2 * Basedigits && (minprec - 2 * Basedigits) << f >= destprec)
            break;

    // Newton's iteration
    while (k--)
    {
        apfloat t;

        prec *= 2;
        x.prec (min (prec, destprec));

        t = one - u * pow (x, n);
        if (k < f) t.prec (prec / 2);

        if (n > 1)
            x += x * t / d;
        else
            x += x * t;

        // Precising iteration
        if (k == f)
        {
            if (n > 1)
                x += x * (one - u * pow (x, n)) / d;
            else
                x += x * (one - u * pow (x, n));
        }
    }

    x.prec (destprec);

    return x;
}

// Floor function
apfloat floor (apfloat x)
{
    if (x.sign () >= 0)
        return apfloat (apabsfloor (x.ap));
    else
        return apfloat (apabsceil (x.ap));
}

// Ceiling function
apfloat ceil (apfloat x)
{
    if (x.sign () >= 0)
        return apfloat (apabsceil (x.ap));
    else
        return apfloat (apabsfloor (x.ap));
}

// Splits x to integer and fractional parts
apfloat modf (apfloat x, apfloat *ipart)
{
    *ipart = apfloat (apabsfloor (x.ap));

    return x - *ipart;
}

// Returns x modulo y, where 0 <= result < y
apfloat fmod (apfloat x, apfloat y)
{
    size_t s, destprec;
    apfloat t, a, b, tx, ty;

    if (!y.sign ())
        return 0;                   // By definition

    a = abs (x);
    b = abs (y);

    if (a < b)
        return x;                   // abs (x) < abs (y)
    else if (x.prec () <= x.exp () - y.exp ())
        return 0;                   // Degenerate case; not enough precision to make any sense
    else
        s = x.exp () - y.exp () + 3 * Basedigits;   // Some extra precision

    tx = x;
    ty = y;

    tx.prec (s);
    ty.prec (s);

    t = tx / ty;                    // Approximate division
    t = apfloat (apabsfloor (t.ap));

    tx = x;
    ty = y;

    destprec = min (y.prec () == INFINITE ? INFINITE : y.prec () + x.exp () - y.exp (), x.prec ());

    tx.prec (destprec);
    ty.prec (destprec);

    a = abs (tx) - abs (t * ty);
    b = abs (ty);

    if (a >= b)                     // Fix division round-off error
        a -= b;
    else if (a < 0)                 // Fix division round-off error
        a += b;

    t = x.sign () * a;

    return t;
}

// Absolute value
apfloat abs (apfloat x)
{
    if (x.sign () >= 0)
        return x;
    else
        return -x;
}

// Calculates pi to destprec digits using the Chudnovskys' binary splitting algorithm
// Uses previously calculated terms (if such exist) to improve the precision of the calculation
apfloat pi_a (size_t n)
{
    apfloat v = PiA + PiB * n;

    v.sign (1 - 2 * (n & 1));

    return v;
}

apfloat pi_p (size_t n)
{
    apfloat f = n, sixf = Pisix * f;

    if (!n)
        return Pione;
    else
        return apfloat (sixf - Pione) * (Pitwo * f - Pione) * (sixf - Pifive);
}

apfloat pi_q (size_t n)
{
    apfloat f = n;

    if (!n)
        return Pione;
    else
        return PiJ * f * f * f;
}

void pi_r (size_t N1, size_t N2, apfloat *T, apfloat *Q, apfloat *P)
{
    switch (N2 - N1)
    {
        case 0:
        {
            assert (N1 != N2);

            break;
        }
        case 1:
        {
            apfloat p0 = pi_p (N1);

            *T = pi_a (N1) * p0;
            *Q = pi_q (N1);
            *P = p0;

            break;
        }
        case 2:
        {
            apfloat p0 = pi_p (N1), p01 = p0 * pi_p (N1 + 1),
                    q1 = pi_q (N1 + 1);

            *T = q1 * pi_a (N1) * p0 +
                 pi_a (N1 + 1) * p01;
            *Q = pi_q (N1) * q1;
            *P = p01;

            break;
        }
        case 3:
        {
            apfloat p0 = pi_p (N1), p01 = p0 * pi_p (N1 + 1), p012 = p01 * pi_p (N1 + 2),
                    q2 = pi_q (N1 + 2), q12 = pi_q (N1 + 1) * q2;

            *T = q12 * pi_a (N1) * p0 +
                 q2 * pi_a (N1 + 1) * p01 +
                 pi_a (N1 + 2) * p012;
            *Q = pi_q (N1) * q12;
            *P = p012;

            break;
        }
        case 4:
        {
            apfloat p0 = pi_p (N1), p01 = p0 * pi_p (N1 + 1), p012 = p01 * pi_p (N1 + 2), p0123 = p012 * pi_p (N1 + 3),
                    q3 = pi_q (N1 + 3), q23 = pi_q (N1 + 2) * q3, q123 = pi_q (N1 + 1) * q23;

            *T = q123 * pi_a (N1) * p0 +
                 q23 * pi_a (N1 + 1) * p01 +
                 q3 * pi_a (N1 + 2) * p012 +
                 pi_a (N1 + 3) * p0123;
            *Q = pi_q (N1) * q123;
            *P = p0123;

            break;
        }
        default:
        {
            size_t Nm = (N1 + N2) / 2;
            apfloat RT, RQ, RP;

            pi_r (N1, Nm, T, Q, P);
            pi_r (Nm, N2, &RT, &RQ, &RP);

            *T = RQ * *T + *P * RT;
            *Q = *Q * RQ;
            *P = *P * RP;
        }
    }
}

apfloat pi (size_t destprec, apfloat *LT, apfloat *LQ, apfloat *LP, apfloat *iroot, size_t *terms)
{
    size_t n;
    apfloat p;

    Pione = 1;
    Pitwo = 2;
    Pifive = 5;
    Pisix = 6;

    PiA = 13591409;
    PiB = 545140134;
    PiJ = 101568000; PiJ *= 107701824;       // J = 10939058860032000

    // Performing the calculation of T, Q and P to infinite precision
    // to make possible to use them later for further calculations

    n = (size_t) (destprec * log ((double) Basedigit) / 32.65445004177);

    if (terms)
    {
        if (*terms)
        {
            apfloat RT, RQ, RP;

            if (*terms != n + 1)
            {
                pi_r (*terms, n + 1, &RT, &RQ, &RP);

                *LT = RQ * *LT + *LP * RT;
                *LQ = *LQ * RQ;
                *LP = *LP * RP;

                *terms = n + 1;
            }

            *iroot = invroot (apfloat (640320, destprec), 2, destprec, *iroot);
            p = invroot (*iroot * *LT, 1) * 53360 * *LQ;
        }
        else
        {
            pi_r (0, n + 1, LT, LQ, LP);

            *terms = n + 1;

            *iroot = invroot (apfloat (640320, destprec), 2);
            p = invroot (*iroot * *LT, 1) * 53360 * *LQ;
        }
    }
    else
    {
        apfloat T, Q, P;

        pi_r (0, n + 1, &T, &Q, &P);

        p = invroot (invroot (apfloat (640320, destprec), 2) * T, 1) * 53360 * Q;
    }

    return p;
}

// Arithmetic-geometric mean
apfloat agm (apfloat a, apfloat b)
{
    apfloat t;
    size_t prec = 0, destprec = min (a.prec (), b.prec ());

    if (!a.sign () || !b.sign ())           // Would not converge quadratically
        return apfloat (new apstruct);      // Zero

    // Precision must be at least 2 * Basedigits
    if (destprec <= Basedigits)
    {
        destprec = 2 * Basedigits;
        a.prec (max (a.prec (), destprec));
        b.prec (max (b.prec (), destprec));
    }

    // First check convergence
    while (prec < Basedigits * Blocksize && 2 * prec < destprec)
    {
        t = (a + b) / 2;
        b = sqrt (a * b);
        a = t;

        // Conserve precision in case of accumulating round-off errors
        a.prec (max (a.prec (), destprec));
        b.prec (max (b.prec (), destprec));

        prec = Basedigits * apeq (a.ap, b.ap);
    }

    // Now we know quadratic convergence
    while (2 * prec <= destprec)
    {
        t = (a + b) / 2;
        b = sqrt (a * b);
        a = t;

        // Conserve precision in case of accumulating round-off errors
        a.prec (max (a.prec (), destprec));
        b.prec (max (b.prec (), destprec));

        prec *= 2;
    }

    return (a + b) / 2;
}

// Natural logarithm, calculated using the arithmetic-geometric mean
// See the Borweins' book for the formula

// Check precalculated pi precision
void checkpi (size_t destprec)
{
    if (!Readypi.ap || ReadypiBase != Base)
    {
        Readypiterms = 0;
        Readypi = pi (destprec, &ReadyT, &ReadyQ, &ReadyP, &Readyinvroot, &Readypiterms);
        ReadypiBase = Base;
    }
    else if (Readypi.prec () < destprec)
    {
        Readypi = pi (destprec, &ReadyT, &ReadyQ, &ReadyP, &Readyinvroot, &Readypiterms);
    }
}

// Raw logarithm, regardless of x
// Doesn't work for really big x, but is faster if used alone for small numbers
apfloat rawlog (apfloat x)
{
    size_t destprec = x.prec ();
    long n = destprec / 2 + 2 * Basedigits;     // Rough estimate
    apfloat e, agme, agmex;

    assert (x.sign () > 0);                     // Must be real logarithm

    e = apfloat (1, destprec);
    e.exp (e.exp () - n);
    x.exp (x.exp () - n);

    agme = agm (1, e);
    agmex = agm (1, x);

    checkpi (destprec);

    return Readypi * (agmex - agme) / (2 * agme * agmex);
}

// Check log constants' precision
void checklogconst (size_t destprec)
{
    checkpi (destprec);

    if (!Logbase.ap || Logbase.prec () < destprec || LogbaseBase != Base)
    {
        int t;
        modint *data = new modint[1];
        rawtype f;

        f = 1;
        for (t = 0; t < Basedigits - 1; t++)
            f *= Basedigit;                     // base is Basedigit^-1

        data[0] = f;

        apfloat base = apfloat (new apstruct (1, 0, (destprec + Basedigits - 1) / Basedigits, 1, data));

        Logbase = rawlog (base);
        Logbase.sign (-Logbase.sign ());
        LogbaseBase = Base;
    }
}

// Calculate the log using 1 / Base <= x < 1 and the log addition formula
// because the agm converges badly for really big x
apfloat log (apfloat x)
{
    size_t destprec = x.prec ();
    long tmpexp = x.exp ();
    apfloat t;

    checklogconst (destprec);

    x.exp (0);

    t = Logbase;
    t.prec (destprec + Basedigits);

    return rawlog (x) + tmpexp * t;
}

// Exponent function, calculated using Newton's iteration for the inverse of log
apfloat exp (apfloat u)
{
    size_t prec, minprec, maxprec, destprec = u.prec (), doubledigits;
    int k, f;
    apfloat x;

    if (!u.sign ()) return 1;

    checklogconst (destprec);

    // Approximate accuracy of a double
    doubledigits = (size_t) (log (MAX_PRECISE_DOUBLE) / log ((double) Basedigit));

    if (u.exp () < -Basedigits)
    {
        // Taylor series: exp(x) = 1 + x + x^2/2 + ...

        x = u;
        x.prec (-u.exp () + 1);
        x += 1;
        prec = -2 * u.exp ();

        // Highly ineffective unless precision is 2^n * Basedigits
        // Round down to nearest power of two
        prec = Basedigits * (size_t) pow (2.0, floor (log ((double) prec / Basedigits) / log (2.0)));
        x.prec (prec);
    }
    else
    {
        // Approximate starting value for iteration

        double d, i, f;

        // If u is too big, an overflow will occur (somewhere)
        d = ap2double (u.ap);
        i = floor (d);
        f = d - i;

        d = i / log ((double) Base);

        x = exp (f) * pow ((double) Base, d - floor (d));
        x.exp (x.exp () + Basedigits * (long) floor (d));

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
            x.prec (minprec + 3 * Basedigits);
            while (prec < minprec)
            {
                x += x * (u - log (x));
                prec *= 2;
            }
            prec = minprec;
        }
    }

    // Check where the precising iteration should be done
    for (k = 0, maxprec = prec; maxprec < destprec; k++, maxprec <<= 1);
    for (f = k, minprec = prec; f; f--, minprec <<= 1)
        if (minprec >= 3 * Basedigits && (minprec - 3 * Basedigits) << f >= destprec)
            break;

    // Newton's iteration
    while (k--)
    {
        apfloat t;

        prec *= 2;
        x.prec (min (prec, destprec));

        t = u - log (x);
        if (k < f) t.prec (prec / 2);

        x += x * t;

        // Precising iteration
        if (k == f)
            x += x * (u - log (x));
    }

    x.prec (destprec);

    return x;
}

// Arbitrary power, calculated using log and exp
apfloat pow (apfloat x, apfloat y)
{
    size_t destprec = min (x.prec (), y.prec ());

    checklogconst (destprec);

    x.prec (destprec);
    y.prec (destprec);

    return exp (y * log (x));
}

// Hyperbolic functions and their inverses, use log and exp

apfloat acosh (apfloat x)
{
    if (x.sign () >= 0)
        return log (x + sqrt (x * x - 1));
    else
        return -log (x - sqrt (x * x - 1));
}

apfloat asinh (apfloat x)
{
    if (x.sign () >= 0)
        return log (sqrt (x * x + 1) + x);
    else
        return -log (sqrt (x * x + 1) - x);
}

apfloat atanh (apfloat x)
{
    return log ((1 + x) / (1 - x)) / 2;
}

apfloat cosh (apfloat x)
{
    apfloat y = exp (x);

    return (y + 1 / y) / 2;
}

apfloat sinh (apfloat x)
{
    apfloat y = exp (x);

    return (y - 1 / y) / 2;
}

apfloat tanh (apfloat x)
{
    apfloat y = exp (2 * x);

    return (y - 1) / (y + 1);
}
