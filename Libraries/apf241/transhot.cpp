#include <iostream>
#include "ap.h"


// Visual matrix transposition test program

int main (void)
{
    int t, r, n = 128, n1 = 8, n2 = 16;
    modint *data = new modint[n];

    for (t = 0; t < n1; t++)
        for (r = 0; r < n1; r++)
        {
            data[t * n2 + r] = (t < r ? 0 : 1);
            data[t * n2 + r + n1] = (t < r ? 3 : 7);
        }

    transpose (data, n1, n2);

    transpose (data, n2, n1);

    return 0;
}
