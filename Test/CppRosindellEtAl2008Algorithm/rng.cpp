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

double Rng::GetRandomFraction() noexcept
{
  switch (m_type)
  {
    case Type::rosindell: return m_nrrand.GetRandomFraction();
    case Type::bilderbeek:
    {
      static std::uniform_real_distribution<double> d(0.0,1.0);
      const double x{d(m_mt)};
      return x;
    }
  }
  std::exit(1);
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
  std::exit(1);
}

double Rng::GetRandomNormal() noexcept
{
  switch (m_type)
  {
    case Type::rosindell: return m_nrrand.GetRandomNormal();
    case Type::bilderbeek:
    {
      #ifdef FIX_ISSUE
      //Unknown which sigma to use
      static const double mean{0.0};
      static const double sigma{2.0};
      static std::normal_distribution<double> d(mean,sigma);
      const double x{d(m_mt)};
      return x;
      #else
      return m_nrrand.GetRandomNormal();
      #endif
    }
  }
  std::exit(1);
}
