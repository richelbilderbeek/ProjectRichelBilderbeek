#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <string>

struct Individual
{
  Individual(const std::string& dna);

  std::string GetDna() const noexcept { return m_dna; }
  int GetIndex() const noexcept { return m_index; }

  private:
  const std::string m_dna;
  /// Unique index as long as there are less than (2^32)/2 Individuals
  const int m_index;

  /// Counter that increases when an Individual is constructed
  static int sm_index;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};


///Checks if different individuals have the same attributes (e.g. DNA)
///This does not take the index of the Individuals into account, as
///these are all (semi)unique
bool operator==(const Individual& lhs, const Individual& rhs) noexcept;

#endif // INDIVIDUAL_H
