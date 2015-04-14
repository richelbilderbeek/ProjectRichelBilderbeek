#ifndef GENERATION_H
#define GENERATION_H

#include <vector>

#include "individual.h"
#include "sequence.h"

//Just a collection of Individuals
struct Generation
{
  Generation(const std::vector<Individual>& individuals)
    : m_individuals{individuals} {}
  bool empty() const noexcept { return m_individuals.empty(); }

  std::vector<Individual>& GetIndividuals() noexcept { return m_individuals; }
  const std::vector<Individual>& GetIndividuals() const noexcept { return m_individuals; }
  std::vector<Sequence> GetSequences() const noexcept;

  std::vector<Individual>::size_type size() const noexcept { return m_individuals.size(); }
  const Individual& operator[](const int index) const noexcept;
  Individual& operator[](const int index) noexcept;

  std::vector<Individual> m_individuals;
};

#endif // GENERATION_H
