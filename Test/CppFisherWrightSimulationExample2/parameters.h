#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <string>

struct Parameters
{
  ///Factory method
  static Parameters CreateParameters(const std::string& filename);

  ///Create parameters from scratch
  explicit Parameters(
    const int dna_length,
    const double mutation_rate,
    const int n_generations,
    const int pop_size,
    const int seed
  );

  int GetDnaLength() const noexcept { return m_dna_length; }
  double GetMutationRate() const noexcept { return m_mutation_rate; }
  int GetNumberOfGenerations() const noexcept { return m_n_generations; }
  int GetPopSize() const noexcept { return m_pop_size; }
  int GetSeed() const noexcept { return m_seed; }

  private:
  const int m_dna_length;
  const double m_mutation_rate;
  const int m_n_generations;
  const int m_pop_size;
  const int m_seed;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

std::ostream& operator<<(std::ostream& os, const Parameters& parameters);


#endif // PARAMETERS_H
