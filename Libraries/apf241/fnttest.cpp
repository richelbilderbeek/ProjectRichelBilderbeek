#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include "ap.h"


using namespace std;


// Program for testing the various fnt algorithms

int main (int argc, char *argv[])
{
    int t, r, n, i = 1, m = 0, p = 0;
    time_t b;
    modint pr, q;

    if (argc < 2)
    {
        cerr << "USAGE: fnt t [sign] [method] [print]" << endl;
        return 2;
    }

    istringstream s (argv[1]);

    if (!(s >> n))
    {
        cerr << "Invalid argument t: " << argv[1] << endl;
        return 1;
    }

    if (argc > 2)
    {
        istringstream s (argv[2]);

        if (!(s >> i))
        {
            cerr << "Invalid argument sign: " << argv[2] << endl;
            return 1;
        }
    }

    if (argc > 3)
    {
        istringstream s (argv[3]);

        if (!(s >> m))
        {
            cerr << "Invalid argument method: " << argv[3] << endl;
            return 1;
        }
    }

    if (argc > 4)
    {
        istringstream s (argv[4]);

        if (!(s >> p))
        {
            cerr << "Invalid argument print: " << argv[4] << endl;
            return 1;
        }
    }

    n = 1 << n;

    setmodulus (moduli[0]);

    pr = primitiveroots[0];

    modint *d = new modint[n];

    if (!d)
    {
        cerr << "Out of memory" << endl;
        return 1;
    }

    cout << "Size: " << n << endl;
    cout << "Modulus: " << modint::modulus << endl;
    cout << "Primitive root: " << pr << endl;
    cout << "Sign: " << i << endl;
    cout << "Method: ";
    switch (m)
    {
        case 0: cout << "Cooley-Tukey (ifnt)" << endl;
                break;
        case 1: cout << "Sande-Tukey (fnt)" << endl;
                break;
        case 2: cout << "\"Four-Step\" Cooley-Tukey (ifourstep)" << endl;
                break;
        case 3: cout << "\"Four-Step\" Sande-Tukey (fourstep)" << endl;
                break;
        case 4: cout << "\"Four-Step\" Table Cooley-Tukey (itablefourstep)" << endl;
                break;
        case 5: cout << "\"Four-Step\" Table Sande-Tukey (tablefourstep)" << endl;
                break;
        case 6: cout << "\"Six-Step\" Cooley-Tukey (isixstep)" << endl;
                break;
        case 7: cout << "\"Six-Step\" Sande-Tukey (sixstep)" << endl;
                break;
        case 8: cout << "\"Six-Step\" Table Cooley-Tukey (itablesixstep)" << endl;
                break;
        case 9: cout << "\"Six-Step\" Table Sande-Tukey (tablesixstep)" << endl;
                break;
        case 10: cout << "\"Six-step\" Table (i/tablesixsteptrans) & inverse" << endl;
                 break;
    }

    for (t = 0; t < n; t++)
        d[t] = t + 1;

    b = time (0);

    switch (m)
    {
        case 0: ifnt (d, pr, i, n);
                break;
        case 1: fnt (d, pr, i, n);
                break;
        case 2: ifourstepfnt (d, pr, i, n);
                break;
        case 3: fourstepfnt (d, pr, i, n);
                break;
        case 4: itablefourstepfnt (d, pr, i, n);
                break;
        case 5: tablefourstepfnt (d, pr, i, n);
                break;
        case 6: isixstepfnt (d, pr, i, n);
                break;
        case 7: sixstepfnt (d, pr, i, n);
                break;
        case 8: itablesixstepfnt (d, pr, i, n);
                break;
        case 9: tablesixstepfnt (d, pr, i, n);
                break;
        case 10: tablesixstepfnttrans (d, pr, i, n);
                 itablesixstepfnttrans (d, pr, -i, n);
                 break;
    }

    cout << "Seconds: " << difftime (time (0), b) << endl;

    cout << endl;

    q = modint (1) / modint (n);

    if (p)
        for (t = 0; t < n; t++)
        {
            cout << setw (16) << d[t];
            if ((t & 3) == 3)
                cout << endl;
        }

    delete[] d;

    clearmodulus ();

    return 0;
}
