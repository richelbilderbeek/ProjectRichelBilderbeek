#include <iostream>
#include <iostream>
#include "tapfloat.h"


int main (int argc, char *argv[])
{
    apfloat x, y, z;
    tapfloat u, v, w;

    x = pi (1000);
    y = pi (1000);

    u = transform (x);
    v = transform (x);

    cout << pretty << x * x << endl;
    cout << pretty << u * u << endl;
    cout << pretty << u * v << endl;
    cout << pretty << u * x << endl;
    cout << pretty << x * u << endl;

    z = 1;
    u = transform (x, x.ap->size, x.ap->size);
    v = transform (y, y.ap->size, x.ap->size);
    w = transform (z, z.ap->size, x.ap->size);

    cout << pretty << x + x << endl;
    cout << pretty << x + y << endl;
    cout << pretty << w * (u + u) << endl;
    cout << pretty << w * (u + v) << endl;
    cout << pretty << 1 * (u + u) << endl;
    cout << pretty << z * (u + v) << endl;

    return 0;
}
