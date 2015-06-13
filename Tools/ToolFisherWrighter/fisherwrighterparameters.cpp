#include "fisherwrighterparameters.h"

#include <cassert>
#include <fstream>
#include <stdexcept>
#include <sstream>

ribi::fw::Parameters::Parameters(
  const int dna_length,
  const double mutation_rate,
  const int n_generations,
  const int pop_size,
  const int seed
)
  :
    m_dna_length{dna_length},
    m_mutation_rate{mutation_rate},
    m_n_generations{n_generations},
    m_pop_size{pop_size},
    m_seed{seed}
{
  #ifndef NDEBUG
  Test();
  #endif

  if (m_dna_length < 0)
  {
    std::stringstream s;
    s << "Parameters::Parameters: DNA length must be positive, DNA length given: "
      << m_dna_length
    ;
    throw std::logic_error(s.str().c_str());
  }
  if (m_n_generations < 0)
  {
    std::stringstream s;
    s << "Parameters::Parameters: "
      << "number of generations must be positive, "
      << "number of generations supplied: "
      << m_n_generations
    ;
    throw std::logic_error(s.str().c_str());
  }
  if (m_pop_size < 0)
  {
    std::stringstream s;
    s << "Parameters::Parameters: "
      << "population size must be positive, "
      << "population size supplied: "
      << m_pop_size
    ;
    throw std::logic_error(s.str().c_str());
  }
  if (m_seed < 0)
  {
    std::stringstream s;
    s << "Parameters::Parameters: cannot create Parameters with seed < 0";
    throw std::logic_error(s.str().c_str());
  }

}

ribi::fw::Parameters ribi::fw::Parameters::CreateParameters(const std::string& filename)
{
  std::string dna_length_str{""};
  int dna_length{0};
  std::string mutation_rate_str{""};
  double mutation_rate{0.0};
  std::string n_generations_str{""};
  int n_generations{0};
  std::string pop_size_str{""};
  int pop_size{0};
  std::string seed_str{""};
  int seed{0};

  std::ifstream f(filename.c_str());
  //TODO: Add safety is file has wrong format
  f
    >> dna_length_str >> dna_length
    >> mutation_rate_str >> mutation_rate
    >> n_generations_str >> n_generations
    >> pop_size_str >> pop_size
    >> seed_str >> seed
  ;
  const Parameters parameters(
    dna_length,
    mutation_rate,
    n_generations,
    pop_size,
    seed
  );
  return parameters;
}


std::ostream& ribi::fw::operator<<(std::ostream& os, const Parameters& parameters)
{
  os
    << "dna_length " << parameters.GetDnaLength() << '\n'
    << "mutation_rate " << parameters.GetMutationRate() << '\n'
    << "n_generations " << parameters.GetNumberOfGenerations() << '\n'
    << "pop_size " << parameters.GetPopSize() << '\n'
    << "seed " << parameters.GetSeed() << '\n'
  ;
  return os;
}

bool ribi::fw::operator==(const Parameters& lhs, const Parameters& rhs) noexcept
{
  return
       lhs.GetDnaLength() == rhs.GetDnaLength()
    && lhs.GetMutationRate() == rhs.GetMutationRate()
    && lhs.GetNumberOfGenerations() == rhs.GetNumberOfGenerations()
    && lhs.GetPopSize() == rhs.GetPopSize()
    && lhs.GetSeed() == rhs.GetSeed()
  ;
}

bool ribi::fw::operator!=(const Parameters& lhs, const Parameters& rhs) noexcept
{
  return !(lhs == rhs);
}
