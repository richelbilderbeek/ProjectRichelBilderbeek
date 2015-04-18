#ifndef GENERATION_H
#define GENERATION_H

#include <vector>

#include "individual.h"
#include "sequence.h"

//Just a collection of Individuals
struct Generation
{
  Generation(const std::vector<Individual>& individuals);

  bool empty() const noexcept { return m_individuals.empty(); }

  std::vector<Individual>& GetIndividuals() noexcept { return m_individuals; }
  const std::vector<Individual>& GetIndividuals() const noexcept { return m_individuals; }
  std::vector<Sequence> GetSequences() const noexcept;

  std::vector<Individual>::size_type size() const noexcept { return m_individuals.size(); }
  const Individual& operator[](const int index) const noexcept;
  Individual& operator[](const int index) noexcept;

  private:
  std::vector<Individual> m_individuals;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

bool operator==(const Generation& lhs, const Generation& rhs) noexcept;

#endif // GENERATION_H
