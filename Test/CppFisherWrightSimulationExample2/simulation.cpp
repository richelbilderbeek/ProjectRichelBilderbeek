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
  const std::vector<Individual>& individuals
)
  : m_generations{},
    m_parameters{parameters},
    m_rnd_engine{static_cast<unsigned int>(parameters.GetSeed())}
{
  #ifndef NDEBUG
  Test();
  #endif

  m_generations.push_back(individuals);
}

std::vector<Individual> Simulation::CreateIndividuals(
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
        Dna(mutation_rate,m_rnd_engine,Dna::CreateRandomDna(dna_length)),
          Pedigree::Create()
        );
    }
  );
  return v;
}


std::vector<Individual> Simulation::CreateNextGeneration(
  std::vector<Individual>& current_generation
  ) noexcept
{
  std::vector<Individual> next_generation;

  const int n{m_parameters.GetPopSize()};
  for (int i=0; i!=n; ++i)
  {
    const int index = std::rand() % n;
    assert(index >= 0);
    assert(index < static_cast<int>(current_generation.size()));
    Individual& parent{current_generation[index]};
    const Individual kid{parent.CreateOffspring()};
    next_generation.push_back(kid);
  }
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

std::string Simulation::GetPedigree() const noexcept
{
  //Take the first individual from the first generation
  if (this->m_generations.empty()) return "";
  if (this->m_generations.back().empty()) return "";
  return m_generations[0][0].GetPedigree()->ToNewick();

  /*
  if (!simulation.GetGenerations().back().empty())
  {
    const Individual& first_individual{simulation.GetGenerations().back().front() };
    std::shared_ptr<const Pedigree> first_pedigree{
      first_individual.GetPedigree()
    };
    assert(first_pedigree);
    for (int i=0; i!=n_generations; ++i)
    {
      std::shared_ptr<const Pedigree> parent_pedigree{
        first_individual.GetPedigree()->GetParent().lock()
      };
      if (parent_pedigree) { first_pedigree = parent_pedigree; }
      else { break; }
    }
    assert(first_pedigree);
    std::cout << first_pedigree->ToNewick() << std::endl;

  }
  */
  return "TODO";
}

std::vector<Sequence> Simulation::GetSequences() const noexcept
{
  std::vector<Sequence> alignments;
  const std::vector<Individual>& current_generation = m_generations.back();
  std::transform(
    std::begin(current_generation),
    std::end(current_generation),
    std::back_inserter(alignments),
    [](const Individual& i)
    {
      const std::string description = std::to_string(i.GetIndex());
      assert(std::stoi(description) == i.GetIndex());
      return Sequence(description,i.GetDna().GetSequence());
    }
  );

  return alignments;
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
      simulation.GetSequences()
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
      Dna(mutation_rate,rnd_engine,Dna::CreateRandomDna(dna_length)),Pedigree::Create());
    std::vector<Individual> is;
    is.push_back(i);
    Simulation s(p,is);
    for (int i=0; i!=n_generations; ++i) { s.NextGeneration(); }
    assert(s.GetGenerations().back() == is);
  }
}
#endif
