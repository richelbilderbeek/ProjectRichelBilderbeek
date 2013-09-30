#include <iostream>

#include "cs2.h"

using namespace std;

// Constructor
cs2::cs2(unsigned char *const key,int keylen,int n){
    seed(key,keylen,n);
}
cs2::cs2(void){};
cs2::~cs2(){for (i=j=0;i<256;i++){S[i]=0;}}

// Key Scheduling Algorithm
void cs2::seed(unsigned char *const key,int keylen,int n){
    /* Check integrity of input
    if ((key==nullptr_t)||(keylen<1)||(n<0)){
        throw("Bad function call.");
        return -1;
    }
    */
    try{
        if (n<=0){n=20;}
        // Initial values of substitution box
        for (i=0;i<256;i++){S[i]=i;}
        j=0;
        while (n>0){
            n--;
            for (i=0;i<256;i++){
                j=(j+key[i%keylen]+S[i])%256;
                char c = S[i]; S[i]=S[j];S[j]=c; // swap
            }
        }
        i=j=0;
    }catch(...){cerr << "Bad parameters.\n";}
}

// Return a single character
unsigned char cs2::ch(){
    i=(i+1)%256;
    j=(j+S[i])%256;
    char c = S[i]; S[i]=S[j];S[j]=c; // swap
    return(S[(S[i]+S[j])%256]);
}

// Encrypt/decrypt(part of) a stream
void cs2::encrypt (istream & inStream, ostream & outStream, int count){
    if (count ==0){
        count =1;
        while (count>0){
            char c = inStream.get();
            if(!inStream.eof()) outStream.put(c^ch()); else count=0;
        }
    }else{
        while (count>0){
            char c = inStream.get();
            if(!inStream.eof()) outStream.put(c^ch()); else count=0;
            count--;
        }

    }
}
