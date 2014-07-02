#include <iostream>
#include <fstream>
#include "ap.h"
#include "apint.h"


using namespace std;


void message2bytes (apint m, char *b, size_t s, size_t l)
{
    size_t t;
    apdiv_t v;

    v.quot = m;

    // Slow n^2 algorithm, could be done faster, however is not significant
    for (t = s; t--;)
        b[t] = (int) ap2rawtype ((v = div (v.quot, 256)).rem.val.ap) - t - l;
}

// Calculate powmod (c, d, pq) faster when the factors of pq are known: the primes p and q
// This uses the Chinese Remainder Theorem (CRT)
apint crtpowmod (apint c, apint d1, apint d2, apint t1, apint t2, apint p, apint q, apint pq)
{
    apint r1, r2, y1, y2, x;

    r1 = powmod (c, d1, p);
    r2 = powmod (c, d2, q);

    y1 = r1 * t1 % p;
    y2 = r2 * t2 % q;

    x = q * y1 + p * y2;

    if (x >= pq) x -= pq;               // x %= pq

    return x;
}

int main (int argc, char *argv[])
{
    size_t l, s;
    apint d, d1, d2, p, q, pq, t1, t2, m, c;
    char *b;
    bool usecrt = true;

    if (argc < 4)
    {
        cerr << "USAGE: rsadec inputfile outputfile privatekeyfile" << endl;
        return 2;
    }

    ifstream in (argv[1]);

    if (!in)
    {
        cerr << "Unable to open input file: " << argv[1] << endl;
        return 1;
    }

    ofstream out (argv[2], ios::out | ios::BIN);

    if (!out)
    {
        cerr << "Unable to open output file: " << argv[2] << endl;
        return 1;
    }

    ifstream key (argv[3]);

    if (!key)
    {
        cerr << "Unable to open private key file: " << argv[3] << endl;
        return 1;
    }

    if (!(key >> pq >> d))
    {
        cerr << "Key not found in key file: " << argv[3] << endl;
        return 1;
    }

    if (!(key >> p >> q))
    {
        // CRT cannot be used, the factors p and q are not known
        usecrt = false;
    }
    else
    {
        // Precalculate values for the CRT
        t1 = powmod (q, p - 2, p);
        t2 = powmod (p, q - 2, q);

        d1 = d % (p - 1);
        d2 = d % (q - 1);
    }

    if (!(in >> l))
    {
        cerr << "Unknown message length." << endl;
        return 1;
    }

    cout << "Calculating block length..." << endl;
    for (s = 0, m = 0; m < pq; s++)
        m = m * 256 + 255;

    assert (s);
    s--;

    b = new char[s];

    while (l)
    {
        cout << l << " bytes left to decode...    \r";
        cout.flush ();
        if (l < s) s = l;
        if (!(in >> c)) break;
        if (usecrt)
            m = crtpowmod (c, d1, d2, t1, t2, p, q, pq);
        else
            m = powmod (c, d, pq);
        message2bytes (m, b, s, l);
        out.write (b, s);
        l -= s;
    }

    cout << "Done.                                 " << endl;

    delete[] b;

    return 0;
}
