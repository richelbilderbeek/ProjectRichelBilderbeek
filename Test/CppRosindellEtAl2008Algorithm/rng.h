#ifndef RNG_H
#define RNG_H

#include "nrrand.h"

struct Rng
{
  enum class Type { rosindell, bilderbeek };
  Rng(const long seed, const Type type = Type::rosindell);

  //Interface as NRrand class

  // returns a uniform random number in (0,1)
  double d01();
  // returns an integer between 0 and max
  long i0(long max);
  // returns normal deviates
  double norm();

  private:
  const int m_seed;
  const Type m_type;

  ///Rosindell implementation
  NRrand m_nrrand;
};

#endif // RNG_H
