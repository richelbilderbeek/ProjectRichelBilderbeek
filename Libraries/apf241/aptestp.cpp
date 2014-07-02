#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstring>
#include <cmath>
#include <ctime>
#include "ap.h"
#include "apint.h"


using namespace std;


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

// Approximates the number of terms used in the algorithm when ln Q is x
// Note that Q = J^n * (n!)^3 where n is the number of terms
// Use Stirling's formula for approximation of n!: for large values of n
// (n/e)^n * sqrt (2*n*pi) < n! < (n/e)^n (1 + 1 / (12*n-1)) sqrt (2*n*pi)
double terms (double x)
{
    double a = log (10939058860032000.0) - 3.0,
           n = x;                       // Initial guess

    // x = n (3 ln n + a); find n

    while (fabs ((n * (3 * log (n) + a) - x) / x) > 1e-12)
        n -= (n * (3 * log (n) + a) - x) / (3 * log (n) + a + 3);       // Newton's iteration

    return n;
}

// Calculates pi using the binary splitting algorithm of the Chudnovsky brothers
// Code is essentially taken from CLN by Bruno Haible

apint A, B, J, one, two, five, six;
size_t maxk, currk, oldpct = 0;

apint a (size_t n)
{
    apint v = A + B * n;

    v.sign (1 - 2 * (n & 1));

    return v;
}

apint p (size_t n)
{
    apint f = n, sixf = six * f;

    if (!n)
        return one;
    else
        return (sixf - one) * (two * f - one) * (sixf - five);
}

apint q (size_t n)
{
    apint f = n;

    if (!n)
        return one;
    else
        return J * f * f * f;
}

void r (size_t N1, size_t N2, apint *T, apint *Q, apint *P)
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
            apint p0 = p (N1);

            *T = a (N1) * p0;
            *Q = q (N1);
            *P = p0;

            currk += 1;

            break;
        }
        case 2:
        {
            apint p0 = p (N1), p01 = p0 * p (N1 + 1),
                  q1 = q (N1 + 1);

            *T = q1 * a (N1) * p0 +
                 a (N1 + 1) * p01;
            *Q = q (N1) * q1;
            *P = p01;

            currk += 4;

            break;
        }
        case 3:
        {
            apint p0 = p (N1), p01 = p0 * p (N1 + 1), p012 = p01 * p (N1 + 2),
                  q2 = q (N1 + 2), q12 = q (N1 + 1) * q2;

            *T = q12 * a (N1) * p0 +
                 q2 * a (N1 + 1) * p01 +
                 a (N1 + 2) * p012;
            *Q = q (N1) * q12;
            *P = p012;

            currk += 8;

            break;
        }
        case 4:
        {
            apint p0 = p (N1), p01 = p0 * p (N1 + 1), p012 = p01 * p (N1 + 2), p0123 = p012 * p (N1 + 3),
                  q3 = q (N1 + 3), q23 = q (N1 + 2) * q3, q123 = q (N1 + 1) * q23;

            *T = q123 * a (N1) * p0 +
                 q23 * a (N1 + 1) * p01 +
                 q3 * a (N1 + 2) * p012 +
                 a (N1 + 3) * p0123;
            *Q = q (N1) * q123;
            *P = p0123;

            currk += 12;

            break;
        }
        default:
        {
            size_t Nm = (N1 + N2) / 2;
            apint LT, LQ, LP, RT, RQ, RP;

            r (N1, Nm, &LT, &LQ, &LP);
            r (Nm, N2, &RT, &RQ, &RP);

            *T = RQ * LT + LP * RT;
            *Q = LQ * RQ;
            *P = LP * RP;

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

void calcpart (size_t startterm, size_t endterm, apint *T, apint *Q, apint *P)
{
    size_t n;
    time_t tt;
    clock_t tc;

    cerr << "Calculating terms " << startterm << " to " << endterm << " in base " << Basedigit << endl;
    cerr << "Using the Chudnovsky brothers' binary splitting algorithm" << endl;

    A = 13591409;
    B = 545140134;
    J = 101568000; J *= 107701824;       // J = 10939058860032000

    one = 1;
    two = 2;
    five = 5;
    six = 6;

    n = endterm - startterm + 1;
    maxk = (size_t) (n * (log ((double) n) / log (2.0) + 1));
    currk = 0;

    tt = time (0);
    tc = clock ();

    r (startterm, endterm + 1, T, Q, P);

    cerr.setf (ios::fixed, ios::floatfield);
    cerr << "100% complete, took " << setprecision (3) << (clock () - tc) / (double) CLOCKS_PER_SEC << " seconds CPU time, elapsed time " << setprecision (0) << difftime (time (0), tt) << " seconds" << endl;
}

void combine (apint *LT, apint *LQ, apint *LP, apint *RT, apint *RQ, apint *RP, bool combinep = true)
{
    time_t tt;
    clock_t tc;

    cerr << "Using base " << Basedigit << endl;
    cerr << "Combining";

    tt = time (0);
    tc = clock ();

    *LT = *RQ * *LT + *LP * *RT;
    *LQ = *LQ * *RQ;
    if (combinep) *LP = *LP * *RP;

    cerr.setf (ios::fixed, ios::floatfield);
    cerr << " took " << setprecision (3) << (clock () - tc) / (double) CLOCKS_PER_SEC << " seconds CPU time, elapsed time " << setprecision (0) << difftime (time (0), tt) << " seconds" << endl;
}

apfloat final (apint T, apint Q)
{
    size_t destprec;
    time_t tt;
    clock_t tc;
    apfloat p;

    cerr << "Using base " << Basedigit << endl;
    cerr << "Final value";

    tt = time (0);
    tc = clock ();

    destprec = (size_t) (terms (Q.exp () * log ((double) Basedigit)) / log ((double) Basedigit) * 32.65445004177);

    p = invroot (invroot (apfloat (640320, destprec), 2) * T, 1) * 53360 * Q;

    cerr.setf (ios::fixed, ios::floatfield);
    cerr << " took " << setprecision (3) << (clock () - tc) / (double) CLOCKS_PER_SEC << " seconds CPU time, elapsed time " << setprecision (0) << difftime (time (0), tt) << " seconds" << endl;

    return p;
}

int main (int argc, char *argv[])
{
    int n = 4, m = 0, base = 10;

    if (argc > 1)
    {
        if (!strncmp (argv[1], "-c", 2))
        {
            m = 1;
            n = 5;
        }
        else if (!strncmp (argv[1], "-f", 2))
        {
            m = 2;
            n = 3;
        }
        else if (!strncmp (argv[1], "-F", 2))
        {
            m = 3;
            n = 4;
        }
    }

    if (argc < n)
    {
        cerr << "USAGE: aptestp startterm endterm resultfile [base]" << endl;
        cerr << "       aptestp -c[ombine] leftfile rightfile resultfile [base]" << endl;
        cerr << "       aptestp -f[inal] file [base]" << endl;
        cerr << "       aptestp -F[inalAndCombine] leftfile rightfile [base]" << endl;
        cerr << "    base must be 2...36" << endl;
        return 2;
    }

    if (argc > n)
    {
        istringstream s (argv[n]);
        if (!(s >> base))
        {
            cerr << "Invalid argument base: " << argv[n] << endl;
            return 1;
        }
    }

    apbase (base);
    dump ();

    if (m == 0)
    {
        size_t startterm, endterm;
        apint T, Q, P;

        istringstream s1 (argv[1]);
        if (!(s1 >> startterm))
        {
            cerr << "Invalid argument startterm: " << argv[1] << endl;
            return 1;
        }

        istringstream s2 (argv[2]);
        if (!(s2 >> endterm) || endterm < startterm)
        {
            cerr << "Invalid argument endterm: " << argv[2] << endl;
            return 1;
        }

        ofstream out (argv[3]);
        if (!out)
        {
            cerr << "Cannot open output file " << argv[3] << endl;
            return 1;
        }

        calcpart (startterm, endterm, &T, &Q, &P);

        if (!(out << T << endl << Q << endl << P << endl))
        {
            cerr << "Cannot write to output file " << argv[3] << endl;
            return 1;
        }
    }
    else if (m == 1)
    {
        apint LT, LQ, LP, RT, RQ, RP;

        ifstream inl (argv[2]);
        if (!inl)
        {
            cerr << "Cannot open input file " << argv[2] << endl;
            return 1;
        }

        ifstream inr (argv[3]);
        if (!inr)
        {
            cerr << "Cannot open input file " << argv[3] << endl;
            return 1;
        }

        ofstream out (argv[4]);
        if (!out)
        {
            cerr << "Cannot open output file " << argv[4] << endl;
            return 1;
        }

        if (!(inl >> LT >> LQ >> LP))
        {
            cerr << "Cannot read from input file " << argv[2] << endl;
            return 1;
        }
        if (!(inr >> RT >> RQ >> RP))
        {
            cerr << "Cannot read from input file " << argv[3] << endl;
            return 1;
        }

        combine (&LT, &LQ, &LP, &RT, &RQ, &RP);

        if (!(out << LT << endl << LQ << endl << LP << endl))
        {
            cerr << "Cannot write to output file " << argv[4] << endl;
            return 1;
        }
    }
    else if (m == 2)
    {
        apint T, Q;
        apfloat p;

        ifstream in (argv[2]);
        if (!in)
        {
            cerr << "Cannot open input file " << argv[2] << endl;
            return 1;
        }

        if (!(in >> T >> Q))
        {
            cerr << "Cannot read from input file " << argv[2] << endl;
            return 1;
        }

        p = final (T, Q);

        cout << pretty << p << endl;
    }
    else if (m == 3)
    {
        apint LT, LQ, LP, RT, RQ, RP;
        apfloat p;

        ifstream inl (argv[2]);
        if (!inl)
        {
            cerr << "Cannot open input file " << argv[2] << endl;
            return 1;
        }

        ifstream inr (argv[3]);
        if (!inr)
        {
            cerr << "Cannot open input file " << argv[3] << endl;
            return 1;
        }

        if (!(inl >> LT >> LQ >> LP))
        {
            cerr << "Cannot read from input file " << argv[2] << endl;
            return 1;
        }
        if (!(inr >> RT >> RQ >> RP))
        {
            cerr << "Cannot read from input file " << argv[3] << endl;
            return 1;
        }

        combine (&LT, &LQ, &LP, &RT, &RQ, &RP, false);
        p = final (LT, LQ);

        cout << pretty << p << endl;
    }

    return 0;
}
