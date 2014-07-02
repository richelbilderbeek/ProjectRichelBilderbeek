#include <iostream>
#include "ap.h"


// Program for testing the "baseint" functions
// Won't work with the floating-point versions for now

int main (void)
{
    size_t n = 4, t;
    rawtype *a = new rawtype[n], *b = new rawtype[n];

    if (!a || !b)
    {
        cerr << "Not enough memory" << endl;
        return 1;
    }

    a[0] = 111111111;
    a[1] = 222222222;
    a[2] = 333333333;
    a[3] = 444444444;

    b[0] = 555555555;
    b[1] = 666666666;
    b[2] = 777777777;
    b[3] = 888888888;

    cout << basemuladd (b, a, 0, (rawtype) 100000, n, 0) << endl;

    for (t = 0; t < n; t++)
        cout << b[t] << endl;

    cout << endl;

    cout << basediv (b, a, (rawtype) 100000, n, 0) << endl;

    for (t = 0; t < n; t++)
        cout << b[t] << endl;

    cout << endl;

    return 0;
}
