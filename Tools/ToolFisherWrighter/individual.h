#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <string>
#include <random>

#include "dna.h"
#include "pedigree.h"

struct Individual
{
  //Pedigree can only be created by parent using CreateOffspring
  //CreateOffspring creates a std::shared_ptr
  //Must use std::shared_ptr, due to use of std::weak_ptr
  Individual(
    const Dna& dna,
    const std::shared_ptr<Pedigree>& pedigree
  );

  Individual CreateOffspring(const std::string& name = "") noexcept;

  const Dna& GetDna() const noexcept { return m_dna; }
  int GetIndex() const noexcept { return m_index; }
  std::shared_ptr<const Pedigree> GetPedigree() const noexcept { return m_pedigree; }
  std::shared_ptr<Pedigree> GetPedigree() noexcept { return m_pedigree; }
  void SetName(const std::string& name) noexcept;

  private:
  Dna m_dna; //Non-const, because RNG is passed on

  /// Unique index as long as there are less than (2^32)/2 Individuals
  const int m_index;

  const std::shared_ptr<Pedigree> m_pedigree;

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
