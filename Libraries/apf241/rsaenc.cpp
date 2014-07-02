#include <iostream>
#include <fstream>
#include "ap.h"
#include "apint.h"


using namespace std;


apint bytes2message (char *b, size_t s, size_t f, size_t l)
{
    size_t t;
    apint m = 0;

    // Slow n^2 algorithm, could be done faster, however is not significant
    for (t = s; t < f; t++)
        m = 256 * m + (int) (unsigned char) (t + l);

    for (t = 0; t < s; t++)
        m = 256 * m + (int) (unsigned char) (b[t] + t + l);

    return m;
}

int main (int argc, char *argv[])
{
    size_t l, s, f;
    apint e, pq, m, c;
    char *b;

    if (argc < 4)
    {
        cerr << "USAGE: rsaenc inputfile outputfile publickeyfile" << endl;
        return 2;
    }

    ifstream in (argv[1], ios::in | ios::BIN);

    if (!in)
    {
        cerr << "Unable to open input file: " << argv[1] << endl;
        return 1;
    }

    ofstream out (argv[2]);

    if (!out)
    {
        cerr << "Unable to open output file: " << argv[2] << endl;
        return 1;
    }

    ifstream key (argv[3]);

    if (!key)
    {
        cerr << "Unable to open public key file: " << argv[3] << endl;
        return 1;
    }

    if (!(key >> pq >> e))
    {
        cerr << "Key not found in key file: " << argv[3] << endl;
        return 1;
    }

    in.seekg (0, ios::end);
    l = in.tellg ();
    in.seekg (0, ios::beg);

    out << l << endl;           // Message length

    cout << "Calculating block length..." << endl;
    for (s = 0, m = 0; m < pq; s++)
        m = m * 256 + 255;

    assert (s);
    s--;

    b = new char[s];

    f = s;

    while (l)
    {
        cout << l << " bytes left to encode...    \r";
        cout.flush ();
        if (l < s) s = l;
        in.read (b, s);
        m = bytes2message (b, s, f, l);
        c = powmod (m, e, pq);
        out << c << endl;
        l -= s;
    }

    cout << "Done.                                 " << endl;

    delete[] b;

    return 0;
}
