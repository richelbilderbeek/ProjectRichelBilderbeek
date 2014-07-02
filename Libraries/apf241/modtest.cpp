#include <iostream>
#include "ap.h"


using namespace std;


// Program to test the modint class

int main (void)
{
    modint a, b;

    setmodulus (getprime (1));          // Use with 32-bit versions
    // setmodulus (moduli[0]);          // Use with 64-bit and fp versions

    a = 600000;
    b = 600000;

    cout << "sizeof (modint) = " << sizeof (modint) << endl;

    cout << a << " * " << 600000 << " = " << a * modint (600000) << " (mod " << modint::modulus << ")" << endl;

    cout << a << " ^ " << b << " = " << pow (a, b) << " (mod " << modint::modulus << ")" << endl;

    cout << 1 << " / " << a << " = " << (b = modint (1) / a) << " (mod " << modint::modulus << ")" << endl;

    cout << a << " * " << b << " = " << a * b << " (mod " << modint::modulus << ")" << endl;

    cout << "Primitive root of " << modint::modulus << " = " << primitiveroot () << endl;
    // cout << "Primitive root of " << modint::modulus << " = " << primitiveroots[0] << endl;

    clearmodulus ();

    return 0;
}
