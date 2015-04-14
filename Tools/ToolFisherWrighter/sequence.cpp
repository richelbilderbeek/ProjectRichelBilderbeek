#include "sequence.h"

#include <algorithm>
#include <cassert>
#include <sstream>
#include <stdexcept>

Sequence::Sequence(const std::string& description, const std::string& sequence)
  : m_description{description},
    m_sequence{sequence}
{
  #ifndef NDEBUG
  Test();
  #endif
  const auto iter = std::find_if_not(
    std::begin(m_sequence),
    std::end(m_sequence),
    [](const char c) { return c == 'A' || c == 'C' ||  c == 'G' ||  c == 'T'; }
  );
  if (iter != std::end(m_sequence))
  {
    std::stringstream s;
    s << "Sequence::Sequence: sequence can only contain the characters 'A','C','G','T'";
    throw std::logic_error(s.str().c_str());
  }
}

#ifndef NDEBUG
void Sequence::Test() noexcept
{
  {
    static bool is_tested {false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    const std::string description{"description"};
    const std::string sequence{"ACGT"};
    const Sequence s(description,sequence);
    assert(s.GetDescription() == description);
    assert(s.GetSequence() == sequence);
  }
  {
    try
    {
      Sequence s("description","incorrect_sequence");
      assert(!"Should not get here");
    }
    catch (std::logic_error&)
    {
      //Well detected!
    }
  }
}
#endif

bool operator==(const Sequence& lhs, const Sequence& rhs) noexcept
{
  return
    lhs.GetDescription() == rhs.GetDescription()
    && lhs.GetSequence() == rhs.GetSequence()
  ;
}
