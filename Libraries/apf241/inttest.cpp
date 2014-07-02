#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <ctime>
#include "ap.h"
#include "apint.h"


using namespace std;


// Calculates pi using the binary splitting algorithm
// Code is essentially taken from CLN by Bruno Haible

apint A, B, J;

apint a (size_t n)
{
    apint v = A + B * n;

    v.sign (1 - 2 * (n & 1));

    return v;
}

apint p (size_t n)
{
    if (!n)
        return 1;
    else
        return apint (6 * n - 1) * (2 * n - 1) * (6 * n - 5);
}

apint q (size_t n)
{
    if (!n)
        return 1;
    else
        return J * n * n * n;
}

void r (size_t N1, size_t N2, apint *T, apint *Q, apint *P)
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
            apint p0 = p (N1);

            *T = a (N1) * p0;
            *Q = q (N1);
            if (P) *P = p0;

            break;
        }
        case 2:
        {
            apint p0 = p (N1), p01 = p0 * p (N1 + 1),
                  q1 = q (N1 + 1);

            *T = q1 * a (N1) * p0 +
                 a (N1 + 1) * p01;
            *Q = q (N1) * q1;
            if (P) *P = p01;

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
            if (P) *P = p012;

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
            if (P) *P = p0123;

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
            if (P) *P = LP * RP;
        }
    }
}

int main (int argc, char *argv[])
{
    size_t prec, n;
    int m = 0, base = 10;
    apfloat p;
    time_t tt;
    clock_t tc;

    if (argc < 2)
    {
        cerr << "USAGE: inttest digits [base]" << endl;
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
        if (!(s >> base))
        {
            cerr << "Invalid argument base: " << argv[2] << endl;
            return 1;
        }
    }

    apbase (base);

    A = 13591409;
    B = 545140134;
    J = 101568000; J *= 107701824;       // J = 10939058860032000

    n = (size_t) (prec * log ((double) base) / 32.65445004177);

    tt = time (0);
    tc = clock ();

    apint T, Q, P;

    r (0, n + 1, &T, &Q, &P);

    p = invroot (invroot (apfloat (640320, prec), 2) * T, 1) * 53360 * Q;

    cerr.setf (ios::fixed, ios::floatfield);
    cerr << "Total CPU time " << setprecision (3) << (clock () - tc) / (double) CLOCKS_PER_SEC << " seconds, total elapsed time " << setprecision (0) << difftime (time (0), tt) << " seconds" << endl;

    cout << pretty << p << endl;

    return 0;
}
