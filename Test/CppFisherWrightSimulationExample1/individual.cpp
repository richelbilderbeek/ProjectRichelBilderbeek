#include "individual.h"

int Individual::sm_index = 0;

Individual::Individual(const std::string& dna)
  : m_dna{dna},
    m_index{sm_index++} //Use the previous value
{
  #ifndef NDEBUG
  Test();
  #endif
}

#ifndef NDEBUG
void Individual::Test() noexcept
{
  {
    static bool is_tested {false};
    if (is_tested) return;
    is_tested = true;
  }
}
#endif

bool operator==(const Individual& lhs, const Individual& rhs) noexcept
{
  return lhs.GetDna() == rhs.GetDna();
}
