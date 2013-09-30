#ifndef CS2_H
#define CS2_H

using namespace std;

struct cs2
{
  //CiperSaber2 algorithm class
  //Adapted from Coen Doorenbos
  // http://ciphersaber.gurus.org/

  public:
  // Constructor
  cs2(unsigned char *const key,int keylen,int n=20);
  cs2(void);
  ~cs2();

  // Key Scheduling Algorithm
  void seed(unsigned char *const key,int keylen,int n=20);

  // Return a single character
  unsigned char ch();

  // Encrypt/decrypt (part of) a stream
  void encrypt (istream & inStream, ostream & outStream, int count=0);

  private:
  int i,j;
  unsigned char S[256]; // Substitution Box

};


#endif // CS2_H
