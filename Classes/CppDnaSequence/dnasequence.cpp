#include "dnasequence.h"

#include <algorithm>
#include <cassert>
#include <sstream>
#include <stdexcept>

ribi::DnaSequence::DnaSequence(const std::string& description, const std::string& sequence)
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


bool ribi::operator==(const DnaSequence& lhs, const DnaSequence& rhs) noexcept
{
  return
    lhs.GetDescription() == rhs.GetDescription()
    && lhs.GetSequence() == rhs.GetSequence()
  ;
}

bool ribi::operator!=(const DnaSequence& lhs, const DnaSequence& rhs) noexcept
{
  return !(lhs == rhs);
}
