#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <ctime>
#include "ap.h"


using namespace std;


#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#if !defined (CLOCKS_PER_SEC) && defined (CLK_TCK)
#define CLOCKS_PER_SEC CLK_TCK
#endif

// Program for testing the apfloat class, actually calculates pi

void dump (void)
{
    int i;

    cerr << "Ramsize = " << Ramsize << endl;
    cerr << "CacheL1size = " << CacheL1size << endl;
    cerr << "CacheL2size = " << CacheL2size << endl;
    cerr << "Cacheburst = " << Cacheburst << endl;
    cerr << "Maxblocksize = " << Maxblocksize << endl;
    cerr << "Memorytreshold = " << Memorytreshold << endl;
    cerr << "Blocksize = " << Blocksize << endl;
    cerr << "NProcessors = " << NProcessors << endl;
    cerr << "Cachetreshold = " << Cachetreshold << endl;
    cerr << "Cacheburstblocksize = " << Cacheburstblocksize << endl;
    cerr << "Cachemaxblocksize = " << Cachemaxblocksize << endl;
    cerr << "Cacheblocksize = " << Cacheblocksize << endl;
    cerr << "Base = " << setprecision (20) << Base << endl;
    cerr << "Basedigit = " << setprecision (20) << Basedigit << endl;
    cerr << "Basedigits = " << Basedigits << endl;
    cerr << "NBasefactors = " << NBasefactors << endl;
    cerr << "Basefactors = ";

    for (i = 0; i < NBasefactors; i++)
        cerr << Basefactors[i] << (i < NBasefactors - 1 ? ", " : "");

    cerr << endl;
}

size_t rnd2base (size_t x)
{
    size_t r = 1;

    x /= Basedigits;

    if (!x) return 0;

    while (x >>= 1) r <<= 1;

    return r * Basedigits;
}

size_t rnd3base (size_t x)
{
    size_t r = 3, p = 3;

    if (!x) return 0;

    x /= Basedigits;

    while (r <= x)
    {
        p = r;
        r <<= 1;
    }

    return p * Basedigits;
}

double baseprec4 (int k, int r = 4)
{
    return (pow (4.0, (double) k) * sqrt((double) r) * M_PI - log (16.0 * sqrt ((double) r)) - k * log (4.0)) / log ((double) Basedigit);
}

double baseprec2 (int k, int r = 4)
{
    return (pow (2.0, (double) k) * sqrt((double) r) * M_PI - log (16.0 * sqrt ((double) r)) - k * log (2.0)) / log ((double) Basedigit);
}

// Calculates pi using the Borweins' quartic algorithm

apfloat pi4 (size_t destprec)
{
    int maxk = 0, k;
    size_t prec, dprec;
    time_t tt;
    clock_t tc;
    bool h;

    prec = rnd23up (destprec / Basedigits);
    if (prec == (prec & -prec))
        h = false;
    else
        h = true;

    while (baseprec4 (maxk) < destprec) maxk++;

    cerr << "Using the Borweins' quartic iteration" << endl;
    cerr << "Total " << maxk << " iterations" << endl;

    cerr << "Initial values";

    tt = time (0);
    tc = clock ();

    apfloat y = sqrt (apfloat (2, destprec)) - 1;
    apfloat a = 2 - 4 * y;
    apfloat half = apfloat (1, destprec) / 2;
    apfloat z;

    cerr.setf (ios::fixed, ios::floatfield);
    cerr << " took " << setprecision (3) << (clock () - tc) / (double) CLOCKS_PER_SEC << " seconds CPU time, elapsed time " << setprecision (0) << difftime (time (0), tt) << " seconds" << endl;

    for (k = 0; k < maxk; k++)
    {
        cerr << "Iteration " << k + 1;

        tt = time (0);
        tc = clock ();

        if (k < 2)
            z = pow (y, 4);
        else
        {
            z = y;
            prec = destprec + 4 * z.exp ();
            z.prec (prec > 1 ? prec : 1);
            z = pow (z, 4);
        }

        y = 1 - z;

        if (k < 5)
            y = invroot (y, 4);
        else
        {
            if (h)
                prec = rnd3base (-2 * z.exp ());
            else
                prec = rnd2base (-2 * z.exp ());
            z.prec (-z.exp ());
            z = 1 + z / 4;
            z.prec (prec);
            y = invroot (y, 4, y.prec (), z, prec);
        }

        if (k < 5)
            y = (y - 1) / (y + 1);
        else
        {
            apfloat t;

            z = y - 1;
            if (h)
                prec = rnd3base (-2 * z.exp ());
            else
                prec = rnd2base (-2 * z.exp ());
            dprec = z.prec ();
            t = z;
            t.prec (-z.exp ());
            t = half - t / 4;
            t.prec (prec);
            y = z * invroot (y + 1, 1, dprec, t, prec);
        }

        z = pow (y + 1, 2);
        a *= z * z;

        a -= (1UL << (2 * k + 3)) * y * (z - y);

        cerr.setf (ios::fixed, ios::floatfield);
        cerr << " took " << setprecision (3) << (clock () - tc) / (double) CLOCKS_PER_SEC << " seconds CPU time, elapsed time " << setprecision (0) << difftime (time (0), tt) << " seconds" << endl;
    }

    cerr << "Final inverse";

    tt = time (0);
    tc = clock ();

    a = 1 / a;

    cerr.setf (ios::fixed, ios::floatfield);
    cerr << " took " << setprecision (3) << (clock () - tc) / (double) CLOCKS_PER_SEC << " seconds CPU time, elapsed time " << setprecision (0) << difftime (time (0), tt) << " seconds" << endl;

    return a;
}

// Calculates pi using the Gauss-Legendre algorithm

apfloat pi2 (size_t destprec)
{
    int maxk = 0, k;
    size_t prec;
    time_t tt;
    clock_t tc;
    bool h;

    prec = rnd23up (destprec / Basedigits);
    if (prec == (prec & -prec))
        h = false;
    else
        h = true;

    while (baseprec2 (maxk) < destprec) maxk++;

    cerr << "Using the Gauss-Legendre iteration" << endl;
    cerr << "Total " << maxk << " iterations" << endl;

    cerr << "Initial values";

    tt = time (0);
    tc = clock ();

    apfloat b = invroot (apfloat (2, destprec), 2);
    apfloat a = apfloat (1, destprec), y;
    apfloat t = a / 4, g;

    cerr.setf (ios::fixed, ios::floatfield);
    cerr << " took " << setprecision (3) << (clock () - tc) / (double) CLOCKS_PER_SEC << " seconds CPU time, elapsed time " << setprecision (0) << difftime (time (0), tt) << " seconds" << endl;

    for (k = 0; k < maxk; k++)
    {
        cerr << "Iteration " << k + 1;

        tt = time (0);
        tc = clock ();

        y = a;
        a = (a + b) / 2;

        if (k < 6)
        {
            apfloat z = b * y;
            b = 0;              // Save space
            g = invroot (z, 2);
            b = z * g;
            if (h)
                g.prec (rnd3base ((size_t) (200.0 / log ((double) Basedigit))));
            else
                g.prec (rnd2base ((size_t) (200.0 / log ((double) Basedigit))));
        }
        else
        {
            apfloat z = b * y;
            b = 0;              // Save space
            g = invroot (z, 2, destprec, g);
            b = z * g;
            if (h)
                g.prec (rnd3base ((size_t) (200.0 / log ((double) Basedigit)) << k - 5));
            else
                g.prec (rnd2base ((size_t) (200.0 / log ((double) Basedigit)) << k - 5));
        }

        if (k)
            t -= (1UL << k) * pow (y - a, 2);
        else
            t -= pow (y - a, 2);

        cerr.setf (ios::fixed, ios::floatfield);
        cerr << " took " << setprecision (3) << (clock () - tc) / (double) CLOCKS_PER_SEC << " seconds CPU time, elapsed time " << setprecision (0) << difftime (time (0), tt) << " seconds" << endl;
    }

    cerr << "Final value";

    tt = time (0);
    tc = clock ();

    a = pow (a + b, 2) / (4 * t);

    cerr.setf (ios::fixed, ios::floatfield);
    cerr << " took " << setprecision (3) << (clock () - tc) / (double) CLOCKS_PER_SEC << " seconds CPU time, elapsed time " << setprecision (0) << difftime (time (0), tt) << " seconds" << endl;

    return a;
}

// Calculates pi using the binary splitting algorithm of the Chudnovsky brothers
// Code is essentially taken from CLN by Bruno Haible

apfloat A, B, J, one, two, five, six;
size_t maxk, currk, oldpct = 0;

apfloat a (size_t n)
{
    apfloat v = A + B * n;

    v.sign (1 - 2 * (n & 1));

    return v;
}

apfloat p (size_t n)
{
    apfloat f = n, sixf = six * f;

    if (!n)
        return one;
    else
        return (sixf - one) * (two * f - one) * (sixf - five);
}

apfloat q (size_t n)
{
    apfloat f = n;

    if (!n)
        return one;
    else
        return J * f * f * f;
}

void r (size_t N1, size_t N2, apfloat *T, apfloat *Q, apfloat *P)
{
    size_t pct;

    switch (N2 - N1)
    {
        case 0:
        {
            assert (N1 != N2);

            break;
        }
        case 1:
        {
            apfloat p0 = p (N1);

            *T = a (N1) * p0;
            *Q = q (N1);
            if (P) *P = p0;

            currk += 1;

            break;
        }
        case 2:
        {
            apfloat p0 = p (N1), p01 = p0 * p (N1 + 1),
                    q1 = q (N1 + 1);

            *T = q1 * a (N1) * p0 +
                 a (N1 + 1) * p01;
            *Q = q (N1) * q1;
            if (P) *P = p01;

            currk += 4;

            break;
        }
        case 3:
        {
            apfloat p0 = p (N1), p01 = p0 * p (N1 + 1), p012 = p01 * p (N1 + 2),
                    q2 = q (N1 + 2), q12 = q (N1 + 1) * q2;

            *T = q12 * a (N1) * p0 +
                 q2 * a (N1 + 1) * p01 +
                 a (N1 + 2) * p012;
            *Q = q (N1) * q12;
            if (P) *P = p012;

            currk += 8;

            break;
        }
        case 4:
        {
            apfloat p0 = p (N1), p01 = p0 * p (N1 + 1), p012 = p01 * p (N1 + 2), p0123 = p012 * p (N1 + 3),
                    q3 = q (N1 + 3), q23 = q (N1 + 2) * q3, q123 = q (N1 + 1) * q23;

            *T = q123 * a (N1) * p0 +
                 q23 * a (N1 + 1) * p01 +
                 q3 * a (N1 + 2) * p012 +
                 a (N1 + 3) * p0123;
            *Q = q (N1) * q123;
            if (P) *P = p0123;

            currk += 12;

            break;
        }
        default:
        {
            size_t Nm = (N1 + N2) / 2;
            apfloat LT, LQ, LP, RT, RQ, RP;

            r (N1, Nm, &LT, &LQ, &LP);
            r (Nm, N2, &RT, &RQ, (P ? &RP : 0));

            *T = RQ * LT + LP * RT;
            *Q = LQ * RQ;
            if (P) *P = LP * RP;

            currk += N2 - N1;
        }
    }

    pct = (size_t) (100.0 * currk / maxk);

    if (pct != oldpct)
    {
        cerr << pct << "% complete\r";
        cerr.flush ();

        oldpct = pct;
    }
}

apfloat pib (size_t destprec)
{
    size_t n;
    time_t tt;
    clock_t tc;
    apfloat T, Q, a;

    cerr << "Using the Chudnovsky brothers' binary splitting algorithm" << endl;

    A = 13591409;
    B = 545140134;
    J = 101568000; J *= 107701824;       // J = 10939058860032000

    one = 1;
    two = 2;
    five = 5;
    six = 6;

    A.prec (destprec);
    B.prec (destprec);
    J.prec (destprec);

    one.prec (destprec);
    two.prec (destprec);
    five.prec (destprec);
    six.prec (destprec);

    n = (size_t) (destprec * log ((double) Basedigit) / 32.65445004177);
    maxk = (size_t) (n * (log ((double) n) / log (2.0) + 1));
    currk = 0;

    tt = time (0);
    tc = clock ();

    r (0, n + 1, &T, &Q, 0);

    cerr.setf (ios::fixed, ios::floatfield);
    cerr << "100% complete, took " << setprecision (3) << (clock () - tc) / (double) CLOCKS_PER_SEC << " seconds CPU time, elapsed time " << setprecision (0) << difftime (time (0), tt) << " seconds" << endl;

    cerr << "Final value";

    tt = time (0);
    tc = clock ();

    a = invroot (invroot (apfloat (640320, destprec), 2) * T, 1) * 53360 * Q;

    cerr.setf (ios::fixed, ios::floatfield);
    cerr << " took " << setprecision (3) << (clock () - tc) / (double) CLOCKS_PER_SEC << " seconds CPU time, elapsed time " << setprecision (0) << difftime (time (0), tt) << " seconds" << endl;

    return a;
}

int main (int argc, char *argv[])
{
    size_t prec;
    int m = 0, base = 10;
    time_t tt;
    clock_t tc;

    if (argc < 2)
    {
        cerr << "USAGE: aptest digits [method] [base]" << endl;
        cerr << "    method: 0 = Chudnovskys' binsplit" << endl;
        cerr << "            1 = Gauss-Legendre" << endl;
        cerr << "            2 = Borweins' quartic" << endl;
        cerr << "    base must be 2...36" << endl;
        return 2;
    }

    istringstream s (argv[1]);
    if (!(s >> prec) || !prec)
    {
        cerr << "Invalid argument digits: " << argv[1] << endl;
        return 1;
    }

    if (argc > 2)
    {
        istringstream s (argv[2]);
        if (!(s >> m))
        {
            cerr << "Method must be 0, 1 or 2" << endl;
            return 1;
        }
    }

    if (argc > 3)
    {
        istringstream s (argv[3]);
        if (!(s >> base))
        {
            cerr << "Invalid argument base: " << argv[3] << endl;
            return 1;
        }
    }

    apbase (base);
    dump ();

    cerr << "Calculating pi to " << prec << " base-" << Basedigit << " digits" << endl;

    tt = time (0);
    tc = clock ();

    if (m == 0)
        cout << pretty << pib (prec) << endl;
    else if (m == 1)
        cout << pretty << pi2 (prec) << endl;
    else if (m == 2)
        cout << pretty << pi4 (prec) << endl;

    cerr.setf (ios::fixed, ios::floatfield);
    cerr << "Total CPU time " << setprecision (3) << (clock () - tc) / (double) CLOCKS_PER_SEC << " seconds, total elapsed time " << setprecision (0) << difftime (time (0), tt) << " seconds" << endl;

    return 0;
}
