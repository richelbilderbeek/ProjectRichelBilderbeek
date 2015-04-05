#include "simulation.h"

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iterator>
#include <sstream>

#include <boost/numeric/conversion/cast.hpp>

#include "individual.h"

Simulation::Simulation(
  const Parameters& parameters,
  const std::vector<Individual>& individuals
)
  : m_current_generation{individuals},
    m_parameters{parameters},
    m_rnd_engine{static_cast<unsigned int>(parameters.GetSeed())}
{
  #ifndef NDEBUG
  Test();
  #endif

  assert(m_parameters.GetPopSize()
    == static_cast<int>(m_current_generation.size())
  );
}

std::vector<Individual> Simulation::CreateIndividuals(
  const Parameters& parameters
) noexcept
{
  //Create parameters.GetPopSize() individuals
  // with DNA length of parameters.GetDnaLength()
  std::vector<Individual> v;
  const int dna_length{parameters.GetDnaLength()};
  std::generate_n(
    std::back_inserter(v),
    parameters.GetPopSize(),
    [dna_length]() { return CreateRandomDna(dna_length); }
  );

  assert(v.empty()
    || parameters.GetDnaLength() == static_cast<int>(v[0].GetDna().size())
  );
  assert(parameters.GetPopSize()
    == static_cast<int>(v.size())
  );
  return v;
}


std::vector<Individual> Simulation::CreateNextGeneration(
  const std::vector<Individual>& current_generation
  ) noexcept
{
  std::vector<Individual> next_generation;

  const int n{m_parameters.GetPopSize()};
  for (int i=0; i!=n; ++i)
  {
    const int index = std::rand() % n;
    assert(index >= 0);
    assert(index < static_cast<int>(current_generation.size()));
    const Individual& parent{current_generation[index]};
    const Individual kid(
      CreateMutatedDna(
        parent.GetDna(),
        m_parameters.GetMutationRate()
      )
    );
    next_generation.push_back(kid);
  }
  return next_generation;
}

std::string Simulation::CreateMutatedDna(
  const std::string& dna,
  const double mutation_rate_per_base_pair
) noexcept
{
  //Go through all nucleotides,
  //overwrite with a random base pair by chance
  //(note: the might result in an A being overwritten by an A)
  std::string next_dna{dna};
  const int sz{static_cast<int>(dna.size())};
  for (int i=0; i!=sz; ++i)
  {
    const double p{GetRandomFraction()};
    if (p < mutation_rate_per_base_pair)
    {
      assert(i >= 0);
      assert(i < static_cast<int>(next_dna.size()));
      next_dna[i] = CreateRandomBasePair();
    }
  }
  return next_dna;
}

char Simulation::CreateRandomBasePair() noexcept
{
  switch (std::rand() % 4)
  {
    case 0: return 'A';
    case 1: return 'C';
    case 2: return 'G';
    case 3: return 'T';
  }
  assert(!"Should not get here");
}

std::string Simulation::CreateRandomDna(
  const int dna_length
) noexcept
{
  std::string s(dna_length,0);
  std::generate(std::begin(s),std::end(s),CreateRandomBasePair);
  return s;
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

std::vector<Sequence> Simulation::GetSequences() const noexcept
{
  std::vector<Sequence> alignments;

  std::transform(
    std::begin(m_current_generation),
    std::end(m_current_generation),
    std::back_inserter(alignments),
    [](const Individual& i)
    {
      const std::string description = std::to_string(i.GetIndex());
      assert(std::stoi(description) == i.GetIndex());
      return Sequence(description,i.GetDna());
    }
  );

  return alignments;
}

double Simulation::GetRandomFraction() noexcept
{
  static std::uniform_real_distribution<double> d(0.0,1.0);
  //The random value x gets drawn here
  const double f{d(m_rnd_engine)};

  assert(f >= 0.0);
  assert(f <= 1.0);
  return f;
}

void Simulation::NextGeneration() noexcept
{
  m_current_generation =
    CreateNextGeneration(m_current_generation)
  ;
  assert(m_parameters.GetPopSize()
    == static_cast<int>(m_current_generation.size())
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
  //Create random DNA
  {
    const int dna_length{3};
    const std::string dna{CreateRandomDna(dna_length)};
    assert(dna_length == static_cast<int>(dna.size()));
  }
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
    const Parameters p(dna_length,0.0,n_generations,1,42);
    const Individual i(CreateRandomDna(dna_length));
    std::vector<Individual> is;
    is.push_back(i);
    Simulation s(p,is);
    for (int i=0; i!=n_generations; ++i) { s.NextGeneration(); }
    assert(s.GetCurrentGeneration() == is);
  }
}
#endif
