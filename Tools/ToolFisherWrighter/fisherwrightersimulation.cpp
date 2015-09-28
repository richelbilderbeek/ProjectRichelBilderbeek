#include "fisherwrightersimulation.h"

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iterator>
#include <sstream>

#include <boost/numeric/conversion/cast.hpp>

#include "fisherwrighterdna.h"
#include "fisherwrighterindividual.h"
#include "trace.h"

ribi::fw::Simulation::Simulation(
  const Parameters& parameters,
  const Generation& first_generation
)
  : m_counter{},
    m_generations{},
    m_parameters{parameters},
    m_rnd_engine{static_cast<unsigned int>(parameters.GetSeed())}
{
  #ifndef NDEBUG
  Test();
  #endif

  m_generations.push_back(first_generation);
}

ribi::fw::Simulation::Simulation(
  const Parameters& parameters
)
  : m_counter{},
    m_generations{},
    m_parameters{parameters},
    m_rnd_engine{static_cast<unsigned int>(parameters.GetSeed())}
{
  #ifndef NDEBUG
  Test();
  #endif

  //Create parameters.GetPopSize() individuals
  // with DNA length of parameters.GetDnaLength()
  std::vector<Individual> v;
  const int dna_length{parameters.GetDnaLength()};
  const double mutation_rate{parameters.GetMutationRate()};
  std::mt19937& rnd_engine(m_rnd_engine);
  ribi::Counter& counter(m_counter);
  std::generate_n(
    std::back_inserter(v),
    parameters.GetPopSize(),
    [&counter,dna_length,mutation_rate,&rnd_engine]()
    {
      return Individual(
          Dna(mutation_rate,rnd_engine,dna_length),
          Pedigree::Create(),
          counter
        );
    }
  );
  const Generation first_generation(v);

  m_generations.push_back(first_generation);
}


ribi::fw::Generation ribi::fw::Simulation::CreateNextGeneration(
  Generation& current_generation
  ) noexcept
{
  std::vector<Individual> individuals;

  const int n{m_parameters.GetPopSize()};

  std::uniform_int_distribution<int> d(0,n-1); //-1 because uniform_int_distribution uses symmetric range
  for (int i=0; i!=n; ++i)
  {  
    const int index{d(m_rnd_engine)};
    assert(index >= 0);
    assert(index < static_cast<int>(current_generation.size()));
    Individual& parent(current_generation[index]);
    const Individual kid{parent.CreateOffspring()};
    individuals.push_back(kid);
  }
  const Generation next_generation(individuals);
  return next_generation;
}


std::vector<ribi::fw::Parameters> ribi::fw::Simulation::CreateTestParameters() noexcept
{
  std::vector<Parameters> v;
  //0: shortest interesting simulation
  v.push_back(
    Parameters(
      1,   //dna_length
      0.0, //mutation_rate
      1,   //n_generations
      1,   //pop_size
      42   //seed
    )
  );
  //Bash at simulation by adding zero-length parameters
  for (int i=0; i!=8; ++i)
  {
    v.push_back(
      Parameters(
        i & 1, //dna_length
        0.0,   //mutation_rate
        i & 2, //n_generations
        i & 4, //pop_size
        42     //seed
      )
    );
  }
  return v;
}

std::vector<ribi::DnaSequence> ribi::fw::Simulation::GetCurrentSequences() const noexcept
{
  return GetGenerations().back().GetSequences();
}

std::string ribi::fw::Simulation::GetPedigree() noexcept
{
  //Take the first individual from the first generation
  if (this->m_generations.empty()) return "";
  if (this->m_generations.back().empty()) return "";

  std::shared_ptr<const Pedigree> pedigree = m_generations.back().GetIndividuals()[0].GetPedigree();
  while (1)
  {
    std::shared_ptr<const Pedigree> parent = pedigree->GetParent().lock();
    if (!parent) break;
    pedigree = parent;
  }
  return pedigree->ToNewick();
}

void ribi::fw::Simulation::NextGeneration() noexcept
{
  assert(!m_generations.empty());
  m_generations.push_back(
    CreateNextGeneration(m_generations.back())
  );
}

bool ribi::fw::operator==(const Simulation& lhs, const Simulation& rhs) noexcept
{
  return
       lhs.GetParameters() == rhs.GetParameters()
    && lhs.GetGenerations() == rhs.GetGenerations()
  ;
}

bool ribi::fw::operator!=(const Simulation& lhs, const Simulation& rhs) noexcept
{
  return !(lhs == rhs);
}

