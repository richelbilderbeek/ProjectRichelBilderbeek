#include <iostream>

#ifndef CS2_ENCRYPT_H
#define CS2_ENCRYPT_H

using namespace std;

void logProgress(int bytecount, double fraction);

void cs2_encrypt(istream & inStream,
                 ostream & outStream,
                 unsigned char *const userkey,
                 int userkeyLength,
                 int n=20,
                 int bytetotal=0);

void cs2_decrypt(istream & inStream,
                 ostream & outStream,
                 unsigned char *const userkey,
                 int userkeyLength,
                 int n=20,
                 int bytetotal=0);

#endif // CS2_ENCRYPT_H
