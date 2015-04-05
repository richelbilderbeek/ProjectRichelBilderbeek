#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <string>

struct Sequence
{
  explicit Sequence(const std::string& description, const std::string& sequence);

  const std::string& GetDescription() const noexcept { return m_description; }
  const std::string& GetSequence() const noexcept { return m_sequence; }

  private:
  const std::string m_description;
  const std::string m_sequence;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

bool operator==(const Sequence& lhs, const Sequence& rhs) noexcept;

#endif // SEQUENCE_H
