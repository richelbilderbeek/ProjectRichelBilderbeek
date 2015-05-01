#ifndef RNG_H
#define RNG_H

#include "nrrand.h"
#include <random>

struct Rng
{
  #ifndef NDEBUG
  ///Must be called before Rng construction,
  ///due to Rosindell implementation calling std::srand
  static void Test() noexcept;
  #endif

  enum class Type { rosindell, bilderbeek };
  Rng(const int seed, const Type type) noexcept;

  // returns an integer between 0 and max
  int GetRandomInt(const int max) noexcept;
  // returns normal deviates
  double GetRandomNormal() noexcept;

  private:

  const int m_seed;
  const Type m_type;

  //mt generates random numbers
  std::mt19937 m_mt;

  ///Rosindell implementation
  NRrand m_nrrand;
};

#endif // RNG_H
