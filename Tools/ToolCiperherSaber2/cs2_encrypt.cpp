#include <iostream>
#include <stdlib.h>     // srand
#include <time.h>       // time()

#include "cs2_encrypt.h"
#include "cs2.h"
using namespace std;

void logProgress(int bytecount, double fraction){
    clog << bytecount/1048576<< " megabytes processed (" << fraction*100 << " %)\n";

}

void cs2_encrypt(istream & inStream, ostream & outStream,
                 unsigned char *const userkey,
                 int userkeyLength, int n, int bytetotal)
{
    unsigned char *key;

    // Allocate memory for key, copy userkey
    key = new unsigned char [userkeyLength+10];
    for (int i=0;i<userkeyLength;i++){key[i]=userkey[i];}

    // Generate IV and append to key
    clog << "Generating initialisation vector...\n";
    srand (time(0));
    for (int i=0;i<10;i++) {
        char c=rand()%256;
        outStream << c;
        key[userkeyLength+i] = c;
    }

    // Seed PRNG and encrypt
    clog << "Seeding pseudorandom number generator...\n";
    cs2 ciph;
    ciph.seed(key,userkeyLength+10,n);

    clog << "Encrypting...\n";
    if (bytetotal<=0){
        ciph.encrypt(inStream,outStream);
    }else{
        bool good; double count;int increment=1048576*4;
        for (good=true, count=1; good;count++){
            ciph.encrypt(inStream,outStream,increment);
            if (!inStream.eof()){
                logProgress(count*increment,(count/static_cast<double>(bytetotal/increment)));
            }else{
                logProgress(bytetotal,1);
                good = false;
            }
        }
    }


    return;
}

void cs2_decrypt(istream & inStream, ostream & outStream,
                 unsigned char *const userkey,
                 int userkeyLength, int n, int bytetotal)
{
    unsigned char *key;

    // Allocate memory for key, copy userkey
    key = new unsigned char [userkeyLength+10];
    for (int i=0;i<userkeyLength;i++){key[i]=userkey[i];}

    // Fetch IV
    clog << "Fetching IV...\n";
    for (int i=0;i<10;i++) {key[userkeyLength+i] = inStream.get();}

    // Seed PRNG and dencrypt
    clog << "Seeding pseudorandom number generator...\n";
    cs2 ciph;
    ciph.seed(key,userkeyLength+10,n);

    clog << "Decrypting...\n";
    if (bytetotal<=0){
        ciph.encrypt(inStream,outStream);
    }else{
        bool good; double count;int increment=1048576*4;
        for (good=true, count=1; good;count++){
            ciph.encrypt(inStream,outStream,increment);
            if (!inStream.eof()){
                logProgress(count*increment,(count/static_cast<double>(bytetotal/increment)));
            }else{
                logProgress(bytetotal,1);
                good = false;
            }
        }
    }
    return;
}
