#include <iostream>
#include "ap.h"


using namespace std;


// Transposition test functions

int main (void)
{
    int t, r, n = 128, n1 = 8, n2 = 16;
    modint *data = new modint[n];

    for (t = 0; t < n; t++)
        data[t] = t;

    for (t = 0; t < n1; t++)
    {
        for (r = 0; r < n2; r++)
            cout << data[t * n2 + r] << "\t";
        cout << endl;
    }

    cout << endl;

    transpose (data, n1, n2);

    for (t = 0; t < n2; t++)
    {
        for (r = 0; r < n1; r++)
            cout << data[t * n1 + r] << "\t";
        cout << endl;
    }

    cout << endl;

    transpose (data, n2, n1);

    for (t = 0; t < n1; t++)
    {
        for (r = 0; r < n2; r++)
            cout << data[t * n2 + r] << "\t";
        cout << endl;
    }

    return 0;
}
