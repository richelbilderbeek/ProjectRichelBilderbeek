#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <ctime>
#include "ap.h"


using namespace std;


// Program for searching Mersenne primes using the Lucas-Lehmer test
// Basedigit must be 2


// Maximum factor to be searched by trial division
const unsigned long MAXFACTOR = 0xFFFFFFFF;

inline unsigned long min (unsigned long a, unsigned long b)
{
    return (a < b ? a : b);
}

// If prime p == 3 (mod 4) and 2 * p + 1 is prime, then 2^p-1 is composite
bool trivtest (unsigned long p)
{
    if (p > 3 && (p & 3) == 3 && isprime (2 * p + 1)) return false;
    else return true;
}

// All divisors are of the form 2 * k * p + 1
// Algorithm improved by Jo Yeong Uk
bool divtest (unsigned long p, bool o = false)
{
    unsigned long k, m, d, s = (p + RAWBITS - 1) / RAWBITS, incr = (p & 3) ^ 2;
    rawtype *M = new rawtype[s], *A = new rawtype[s], a = 1, u = 1;
    double l;

    for (m = 0; m < s - 1; m++)
        M[m] = MAXRAW;

    for (m = 0; m < p % RAWBITS - 1; m++)
    {
        bigadd (&a, &a, 1);
        bigadd (&a, &u, 1);
    }

    M[s - 1] = a;

    if (p <= RAWBITS * 2)
        m = min ((unsigned long) (pow (2.0, 0.5 * p) / (2 * p)), MAXFACTOR / (2 * p));
    else
        m = MAXFACTOR / (2 * p);

    l = 1.5 * p * log ((double) p);
    if (l < m) m = (unsigned long) l;

    for (k = incr; k <= m; k += (incr ^= 2))
    {
        d = 2 * k * p + 1;

        if (isprime (d))
            if (bigdiv (A, M, d, s) == 0)
            {
                if (o) cout << "(factor: " << d << ") ";

                delete[] A;
                delete[] M;

                return false;
            }
    }

    delete[] A;
    delete[] M;

    return true;
}

// The Lucas-Lehmer test for 2^p-1
int lucas (unsigned long p)
{
    unsigned long n = 1, i = p / Basedigits, r = p % Basedigits;
    apfloat L = 4, A, B, M, tr = pow (apfloat (2), r);

    // The modulus
    M = tr;
    M.exp (M.exp () + Basedigits * i);
    M -= 1;

    while (n < p - 1)
    {
        L = L * L - 2;

        // Modulo reduction
        A = L;
        A.exp (A.exp () - Basedigits * i);
        A /= tr;
        A = floor (A);
        B = A;
        B.exp (B.exp () + Basedigits * i);
        B *= tr;
        L = L - B + A;

        // Second check
        if (L >= M) L -= M;

        n++;
    }

    return L == 0;
}

int main (int argc, char *argv[])
{
    unsigned long p, p1, p2;
    bool o = true, l = false;
    time_t t;

    if (argc < 2)
    {
        cerr << "USAGE: mersenne p1 [p2] [primeonly] [Lucas-Lehmer only]" << endl;
        return 2;
    }

    istringstream s (argv[1]);
    if (!(s >> p1) || p1 < 3)
    {
        cerr << "Invalid argument p1: " << argv[1] << endl;
        return 1;
    }

    if (argc > 2)
    {
        istringstream s (argv[2]);
        if (!(s >> p2) || p2 < p1)
        {
            cerr << "Invalid argument p2: " << argv[2] << endl;
            return 1;
        }
    }
    else
        p2 = nextprime (p1);

    if (argc > 3) o = false;
    if (argc > 4) l = true;

    apbase (2);

    for (p = nextprime (p1); p <= p2; p = nextprime (++p))
        if (o)
        {
            cout << "2^" << p << "-1 is... " << flush;
            t = time (0);
            if (!trivtest (p))
                cout << "trivially not prime." << endl;
            else if (!divtest (p, o))
                cout << "not prime. (Trial division " << difftime (time (0), t) << " s)." << endl;
            else
            {
                cout << "(Trial division " << difftime (time (0), t) << " s)... " << flush;
                t = time (0);
                cout << (lucas (p) ? "" : "not ") << "prime. ";
                cout << "(Lucas-Lehmer test " << difftime (time (0), t) << " s)." << endl;
            }
        }
        else
        {
            t = time (0);
            if (trivtest (p) && (l || divtest (p, o)) && lucas (p))
                cout << "2^" << p << "-1 is prime. Elapsed time " << difftime (time (0), t) << " seconds." << endl;
        }

    return 0;
}
