#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "tesseracthelper.h"

#include <cstdlib>
#include <limits>
#include <stdlib.h>
#include <stdint.h>
#pragma GCC diagnostic pop

//Identical to UNIX nrand48
long int Nrand48(unsigned short int xsubi[3])
{
  static unsigned long long int a = 0x5deece66dull;
  static unsigned short int c = 0xb;
  const uint64_t x
    = static_cast<uint64_t>(xsubi[2]) << 32
    | static_cast<uint32_t>(xsubi[1]) << 16
    | xsubi[0];
  const uint64_t y = x * a + c;

  xsubi[0] = y & 0xffff;
  xsubi[1] = (y >> 16) & 0xffff;
  xsubi[2] = (y >> 32) & 0xffff;

  if (sizeof(unsigned short int) == 2)
  {
    return xsubi[2] << 15 | xsubi[1] >> 1;
  }
  else
  {
    return xsubi[2] >> 1;
  }
}

//Used by the original program
//uinT32 nrand48(               //get random number
//               uinT16 *seeds  //seeds to use
//              ) {
//  static uinT32 seed = 0;        //only seed
//
//  if (seed == 0) {
//    seed = seeds[0] ^ (seeds[1] << 8) ^ (seeds[2] << 16);
//    srand(seed);
//  }
//                                 //make 32 bit one
//  return rand () | (rand () << 16);
//}
