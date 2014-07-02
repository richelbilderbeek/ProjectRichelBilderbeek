#include <iostream>
#include "apcplx.h"


using namespace std;


int main (int argc, char *argv[])
{
    apfloat x, y;
    apcomplex z, w;

    x = apfloat (1, 200);
    y = apfloat (-1, 200);

    z = apcomplex (x, y);
    w = apcomplex (y, x);

    z = sin (z);
    w = sin (w);

    cout << pretty << z << endl;
    cout << pretty << w << endl;

    z = asin (z);
    w = asin (w);

    cout << pretty << z << endl;
    cout << pretty << w << endl;

    return 0;
}
