#include "simulation.h"

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iterator>
#include <sstream>

#include <boost/numeric/conversion/cast.hpp>

#include "dna.h"
#include "individual.h"

Simulation::Simulation(
  const Parameters& parameters,
  const Generation& generation
)
  : m_generations{},
    m_parameters{parameters},
    m_rnd_engine{static_cast<unsigned int>(parameters.GetSeed())}
{
  #ifndef NDEBUG
  Test();
  #endif

  m_generations.push_back(generation);
}

Generation Simulation::CreateFirstGeneration(
  const Parameters& parameters
) noexcept
{
  //Create parameters.GetPopSize() individuals
  // with DNA length of parameters.GetDnaLength()
  std::vector<Individual> v;
  const int dna_length{parameters.GetDnaLength()};
  const double mutation_rate{parameters.GetMutationRate()};
  std::generate_n(
    std::back_inserter(v),
    parameters.GetPopSize(),
    [dna_length,mutation_rate,this]()
    {
      return Individual(
        Dna(mutation_rate,m_rnd_engine,dna_length),
          Pedigree::Create()
        );
    }
  );
  Generation g(v);
  return g;
}


Generation Simulation::CreateNextGeneration(
  Generation& current_generation
  ) noexcept
{
  std::vector<Individual> individuals;

  const int n{m_parameters.GetPopSize()};
  for (int i=0; i!=n; ++i)
  {
    const int index = std::rand() % n;
    assert(index >= 0);
    assert(index < static_cast<int>(current_generation.size()));
    Individual& parent{current_generation[index]};
    const Individual kid{parent.CreateOffspring()};
    individuals.push_back(kid);
  }
  const Generation next_generation(individuals);
  return next_generation;
}


std::vector<Parameters> Simulation::CreateTestParameters() noexcept
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

std::vector<Sequence> Simulation::GetCurrentSequences() const noexcept
{
  return GetGenerations().back().GetSequences();
}

std::string Simulation::GetPedigree() noexcept
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

void Simulation::NextGeneration() noexcept
{
  m_generations.push_back(
    CreateNextGeneration(m_generations.back())
  );
}

#ifndef NDEBUG
void Simulation::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  std::mt19937 rnd_engine;
  for (const auto parameters: CreateTestParameters())
  {
    //Run simulation
    Simulation simulation(parameters);
    const int n_generations{parameters.GetNumberOfGenerations()};
    for (int i=0; i!=n_generations; ++i)
    {
      simulation.NextGeneration();
    }

    //Sample the alignments
    const std::vector<Sequence> alignments{
      simulation.GetCurrentSequences()
    };
    assert(parameters.GetPopSize() == static_cast<int>(alignments.size()));
  }
  //If mutation rate is zero, a population of one individuals remains the same
  {
    const int dna_length{10000};
    const int n_generations{100};
    const double mutation_rate{0.0};
    const Parameters p(dna_length,mutation_rate,n_generations,1,42);
    const Individual i(
      Dna(mutation_rate,rnd_engine,dna_length),Pedigree::Create());
    std::vector<Individual> is;
    is.push_back(i);
    Simulation s(p,is);
    for (int i=0; i!=n_generations; ++i) { s.NextGeneration(); }
    assert(s.GetGenerations().back().m_individuals == is);
  }
}
#endif
