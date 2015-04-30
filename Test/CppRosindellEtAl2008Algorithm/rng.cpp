#include "rng.h"

#include <cassert>
#include <stdexcept>

Rng::Rng(const int seed, const Type type) noexcept
  : m_seed{seed},
    m_type{type},
    m_mt(seed),
    m_nrrand(seed)
{
  #ifndef NDEBUG
  ///Must be called before Rng construction,
  ///due to Rosindell implementation calling std::srand
  Test();
  #endif
}

int Rng::GetRandomInt(const int max) noexcept
{
  switch (m_type)
  {
    case Type::rosindell: return m_nrrand.GetRandomInt(max);
    case Type::bilderbeek:
    {
      std::uniform_int_distribution<int> d(0,max);
      const int x{d(m_mt)};
      return x;
    }
  }
  throw std::logic_error("Rng::GetRandomInt"); //Yes, the program will crash, due to noexcept
}

double Rng::GetRandomNormal() noexcept
{
  switch (m_type)
  {
    case Type::rosindell: return m_nrrand.GetRandomNormal();
    case Type::bilderbeek:
    {
      static const double mean{0.0};
      static const double sigma{1.0};
      static std::normal_distribution<double> d(mean,sigma);
      const double x{d(m_mt)};
      return x;
    }
  }
  throw std::logic_error("Rng::GetRandomNormal"); //Yes, the program will crash, due to noexcept
}
