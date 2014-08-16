#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <cstring>
#include <ctime>
#include "ap.h"
#include "apint.h"


using namespace std;


// Largest prime in primetable
const size_t MAXPRIME = 65537;

// Number of times to try the probable prime test before we are convinced
// Chances of the tested probable prime actually being composite is about
// one to 4^POWTESTS, that is for POWTESTS = 20 it is about 10e-12
const int POWTESTS = 20;

// Test for probable prime, the Miller-Rabin test
// For primes a^(p-1) == 1 (mod p) for all a
// For non-primes this is not true for most a
bool powtest (apint m)
{
    size_t t;

    for (t = 0; t < POWTESTS; t++)
        if (powmod (apint ((int) primetable[t]), m - 1, m) != 1)
            return false;

    return true;
}

// Filter out numbers which have n smallest odd primes as factors,
// using Erasthothenes' sieve
// The sieve has only odd numbers
void sieve (apint m, bool *b, size_t n)
{
    size_t t, s, p;
    apint r;

    // Sanity check
    assert (m % 2 == 1);

    for (t = 0; t < n; t++)
        b[t] = true;

    for (t = 0; t < n; t++)
    {
        p = (size_t) primetable[t + 1];         // Start with 3, assume m is odd
        r = m % p;

        s = (size_t) ap2rawtype (r.val.ap);

        if (s) s = p - s;
        if (s & 1) s = (s + p) / 2;
        else s = s / 2;

        for (; s < n; s += p)
            b[s] = false;

        if (p == MAXPRIME) break;
    }
}

// Find next probable prime starting from p so that (p - 1) / 2 is also prime
apint findnextstrongprime (apint p, char c)
{
    size_t t, n;
    bool *b1, *b2, found = false;

    // Sanity check
    assert (p % 4 == 3);

    n = 1000 * p.exp ();            // Size of sieving array for potential primes

    b1 = new bool[n];
    b2 = new bool[n / 2];

    do
    {
        cout << "Sieving candidates for " << c << "..." << endl;
        sieve (p, b1, n);                       // Filter candidates for prime p
        sieve ((p - 1) / 2, b2, n / 2);         // Filter candidates for prime (p - 1) / 2

        cout << "Testing candidates for " << c << "..." << endl;
        for (t = 0; t < n; t += 2, p += 4)      // Seek a probable prime p from the candidates
            if (b1[t] && b2[t / 2] && powtest ((p - 1) / 2) && powtest (p))
            {
                found = true;
                break;
            }
    } while (!found);

    delete[] b2;
    delete[] b1;

    return p;
}

// Find next probable prime starting from p
apint findnextprime (apint p, char c)
{
    size_t t, n;
    bool *b, found = false;

    // Sanity check
    assert (p % 2 == 1);

    n = 100 * p.exp ();             // Size of sieving array for potential primes

    b = new bool[n];

    do
    {
        cout << "Sieving candidates for " << c << "..." << endl;
        sieve (p, b, n);                        // Filter candidates for prime p

        cout << "Testing candidates for " << c << "..." << endl;
        for (t = 0; t < n; t++, p += 2)         // Seek a probable prime p from the candidates
            if (b[t] && powtest (p))
            {
                found = true;
                break;
            }
    } while (!found);

    delete[] b;

    return p;
}

int main (int argc, char *argv[])
{
    size_t i, t, k;
    apint p, q, e, d, pq, pq1;
    char *c;
    bool fast = false, shorte = false;

    if (argc > 1 && !strcmp (argv[1], "-fast"))
    {
        fast = true;
        argc--;
        argv++;
    }

    if (argc < 4)
    {
        cerr << "USAGE: rsagen [-fast] keylength publickeyfile privatekeyfile [shortpublickey]" << endl;
        cerr << "    specifying the -fast switch does not generate strong primes and is faster" << endl;
        return 2;
    }

    istringstream s (argv[1]);
    if (!(s >> k))
    {
        cerr << "Invalid argument keylength: " << argv[1] << endl;
        return 1;
    }

    if (argc > 4)
        shorte = true;

    k /= 2;                     // k is the number of digits in one prime

    c = new char[2 * k];

    cout << "Input at least " << 2 * k << " random characters and press Enter: ";
    for (t = 0; t < 2 * k; t++)
    {
        i = (size_t) cin.get ();
        c[t] = (i + 69 * t + time (0)) % 10 + '0';      // Add pseudorandom noise
    }

    istringstream o1 (string (c, k));
    istringstream o2 (string (c + k, k));

    o1 >> p;                    // Read initial p
    o2 >> q;                    // Read initial p

    if (fast)
    {
        p += 1 - p % 2;         // Make sure p will be odd
        q += 1 - q % 2;         // Make sure q will be odd
    }
    else
    {
        p += 3 - p % 4;         // Make sure p = 3 (mod 4) so (p - 1) / 2 will be odd
        q += 3 - q % 4;         // Make sure q = 3 (mod 4) so (q - 1) / 2 will be odd
    }

    if (fast)
        p = findnextprime (p, 'p');
    else
        p = findnextstrongprime (p, 'p');

    cout << "Suitable p was found." << endl;

    if (fast)
        q = findnextprime (q, 'q');
    else
        q = findnextstrongprime (q, 'q');

    cout << "Suitable q was found." << endl;

    pq = p * q;
    pq1 = (p - 1) * (q - 1);

    if (shorte)
    {
        istringstream i (argv[4]);

        // Generate a public key that is as small as possible to speed up encoding
        e = 3;
        i >> e;                     // Take it from the command line if specified
        if (e < 3) e = 3;
        else e += 1 - e % 2;        // Make sure e will be odd
    }
    else
    {
        // Add pseudorandom noise for generating e
        for (t = 0; t < 2 * k; t++)
            c[t] = (c[t] + 57 * t + time (0)) % 10 + '0';

        istringstream o3 (string (c, 2 * k));

        o3 >> e;                    // Read initial e

        e %= pq1;                   // e should be < p*q

        e += 1 - e % 2;             // Make sure e will be odd
    }

    cout << "Finding e..." << endl;

    if (fast)
    {
        // Seek an e which is relatively prime to pq1
        for (; ; e += 2)
        {
            apint a0 = pq1, a1 = e, q, r, t, y0 = 0, y1 = 1;

            q = a0 / a1;
            r = a0 - q * a1;

            while (r.sign ())               // Extended Euclidean Algorithm
            {
                t = y0 - q * y1;
                t %= pq1;
                if (t.sign () < 0) t += pq1;
                y0 = y1;
                y1 = t;
                a0 = a1;
                a1 = r;
                q = a0 / a1;
                r = a0 - q * a1;
            }

            if (a1 == 1)                    // gcd (e, pq1) == 1, multiplicative inverse exists
            {
                d = y1;                     // d is the multiplicative inverse of e mod pq1
                break;
            }
        }
    }
    else
    {
        // Any odd e will basically do, a multiplicative inverse will exist
        d = powmod (e, (p - 3) * (q - 3) / 2 - 1, pq1);
    }

    // Sanity check
    assert (gcd (e, pq1) == 1);
    assert (e * d % pq1 == 1);

    cout << "Suitable e and d were found." << endl;

    cout << "Writing keys to output files..." << endl;
    ofstream pub (argv[2]);

    if (!pub)
    {
        cerr << "Unable to open public key file: " << argv[2] << endl;
        return 1;
    }

    ofstream priv (argv[3]);

    if (!priv)
    {
        cerr << "Unable to open private key file: " << argv[3] << endl;
        return 1;
    }

    pub << pq << endl << e << endl;
    priv << pq << endl << d << endl << p << ' ' << q << endl;

    cout << "Done." << endl;

    delete[] c;

    return 0;
}
