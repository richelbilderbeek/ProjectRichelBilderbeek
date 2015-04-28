#include "rng.h"

#include <cassert>
#include <stdexcept>

Rng::Rng(const int seed, const Type type) noexcept
  : m_seed{seed},
    m_type{type},
    m_nrrand(seed)
{

}

double Rng::GetRandomFraction() noexcept
{
  switch (m_type)
  {
    case Type::rosindell: return m_nrrand.GetRandomFraction();
    case Type::bilderbeek: assert(!"Not implemented yet");
  }
  std::exit(1);
}

int Rng::GetRandomInt(const int max) noexcept
{
  switch (m_type)
  {
    case Type::rosindell: return m_nrrand.GetRandomInt(max);
    case Type::bilderbeek: assert(!"Not implemented yet");
  }
  std::exit(1);
}

double Rng::GetRandomNormal() noexcept
{
  switch (m_type)
  {
    case Type::rosindell: return m_nrrand.GetRandomNormal();
    case Type::bilderbeek: assert(!"Not implemented yet");
  }
  std::exit(1);
}
