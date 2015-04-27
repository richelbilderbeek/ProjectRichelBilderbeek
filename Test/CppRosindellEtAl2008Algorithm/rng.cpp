#include "rng.h"

#include <cassert>

Rng::Rng(const Type type)
  : m_type{type},
    m_nrrand{}
{
}

void Rng::set_seed(long seed)
{
  switch (m_type)
  {
    case Type::rosindell: m_nrrand.set_seed(seed); return;
    case Type::bilderbeek: assert(!"Not implemented yet");
  }
}

double Rng::d01()
{
  switch (m_type)
  {
    case Type::rosindell: return m_nrrand.d01();
    case Type::bilderbeek: assert(!"Not implemented yet");
  }

}

long Rng::i0(long max)
{
  switch (m_type)
  {
    case Type::rosindell: return m_nrrand.i0(max);
    case Type::bilderbeek: assert(!"Not implemented yet");
  }

}
double Rng::norm()
{
  switch (m_type)
  {
    case Type::rosindell: return m_nrrand.norm();
    case Type::bilderbeek: assert(!"Not implemented yet");
  }
}
