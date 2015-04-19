#ifndef RIBI_DNASEQUENCE_H
#define RIBI_DNASEQUENCE_H

#include <string>

namespace ribi {

struct DnaSequence
{
  explicit DnaSequence(const std::string& description, const std::string& sequence);

  const std::string& GetDescription() const noexcept { return m_description; }
  const std::string& GetSequence() const noexcept { return m_sequence; }

  private:
  const std::string m_description;
  const std::string m_sequence;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

bool operator==(const DnaSequence& lhs, const DnaSequence& rhs) noexcept;
bool operator!=(const DnaSequence& lhs, const DnaSequence& rhs) noexcept;

} //~namespace ribi
#endif // RIBI_DNASEQUENCE_H
