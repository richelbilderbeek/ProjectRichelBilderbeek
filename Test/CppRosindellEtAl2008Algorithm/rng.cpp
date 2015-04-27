#include "rng.h"

#include <cassert>

Rng::Rng(const long seed, const Type type)
  : m_seed{seed},
    m_type{type},
    m_nrrand(seed)
{
}

double Rng::GetRandomFraction()
{
  switch (m_type)
  {
    case Type::rosindell: return m_nrrand.GetRandomFraction();
    case Type::bilderbeek: assert(!"Not implemented yet");
  }
}

long Rng::GetRandomInt(long max)
{
  switch (m_type)
  {
    case Type::rosindell: return m_nrrand.GetRandomInt(max);
    case Type::bilderbeek: assert(!"Not implemented yet");
  }

}
double Rng::GetRandomNormal()
{
  switch (m_type)
  {
    case Type::rosindell: return m_nrrand.GetRandomNormal();
    case Type::bilderbeek: assert(!"Not implemented yet");
  }
}
