#include <iostream>
#include <cstdio>
#include "ap.h"


using namespace std;


// Program for testing the "bigint" functions
// Won't work with the floating-point versions for now

int main (void)
{
    size_t n = 8, t;
    rawtype *a = new rawtype[n], *b = new rawtype[n];

    if (!a || !b)
    {
        cerr << "Not enough memory" << endl;
        return 1;
    }

    a[0] = 0xFFFFFFFF;
    a[1] = 0xFFFFFFFF;
    a[2] = 0xFFFFFFFF;
    a[3] = 0xFFFFFFFF;
    a[4] = 0xFFFFFFFF;
    a[5] = 0xFFFFFFFF;
    a[6] = 0xFFFFFFFF;
    a[7] = 0xFFFFFFFF;

    b[0] = 0xFFFFFFFE;
    b[1] = 0xFFFFFFFF;
    b[2] = 0xFFFFFFFF;
    b[3] = 0xFFFFFFFF;
    b[4] = 0xFFFFFFFF;
    b[5] = 0xFFFFFFFF;
    b[6] = 0xFFFFFFFF;
    b[7] = 0xFFFFFFFF;

    cout << "a > b: " << bigcmp (a, b, n) << endl;
    cout << "a < b: " << bigcmp (b, a, n) << endl;

    printf ("%08X", bigmul (a, a, (rawtype) -1, n));

    for (t = 0; t < n; t++)
        printf ("%08X", a[t]);

    printf ("\n");

    printf ("%08X\n", bigdiv (b, b, (rawtype) -1, n));

    for (t = 0; t < n; t++)
        printf ("%08X", b[t]);

    printf ("\n");

    return 0;
}
