#ifndef RNG_H
#define RNG_H

#include "nrrand.h"

struct Rng
{
  enum class Type { rosindell, bilderbeek };
  Rng(const int seed, const Type type = Type::rosindell);

  //Interface as NRrand class

  // returns a uniform random number in (0,1)
  double GetRandomFraction();
  // returns an integer between 0 and max
  int GetRandomInt(const int max);
  // returns normal deviates
  double GetRandomNormal();

  private:
  const int m_seed;
  const Type m_type;

  ///Rosindell implementation
  NRrand m_nrrand;
};

#endif // RNG_H
