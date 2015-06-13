#include "fisherwrightersimulation.h"

#include <cassert>

#include "trace.h"

#ifndef NDEBUG
void ribi::fw::Simulation::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  //If random number generator seed is equal, simulations should yield equal results
  {
    const int dna_length{4};
    const int n_generations{2};
    const double mutation_rate{0.5};
    const int pop_size{1};
    const int seed{42};
    const Parameters p(dna_length,mutation_rate,n_generations,pop_size,seed);
    Simulation s(p);
    Simulation t(p);
    assert(s == t);
    {
      const auto parent1 = s.GetGenerations().front().GetIndividuals()[0];
      const auto parent2 = t.GetGenerations().front().GetIndividuals()[0];
      assert(parent1 == parent2);
      assert(parent1.GetDna() == parent2.GetDna());
      assert(parent1.GetDna().GetSequence() == parent2.GetDna().GetSequence());
    }
    for (int i=1; i!=n_generations; ++i) //Start at 1, because initial generation is already present
    {
      s.NextGeneration();
      t.NextGeneration();
    }
    assert(s == t);
  }
  {
    const int dna_length{10};
    const int n_generations{10};
    const double mutation_rate{0.1};
    const int pop_size{10};
    const int seed1{42};
    const int seed2{35};
    const Parameters p(dna_length,mutation_rate,n_generations,pop_size,seed1);
    const Parameters q(dna_length,mutation_rate,n_generations,pop_size,seed2);
    Simulation s(p);
    Simulation t(q);
    for (int i=0; i!=n_generations; ++i)
    {
      s.NextGeneration();
      t.NextGeneration();
    }
    assert(s != t);
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
    const std::vector<ribi::DnaSequence> alignments{
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
    ribi::Counter counter;
    const Individual i(
      Dna(mutation_rate,rnd_engine,dna_length),Pedigree::Create(),counter);
    std::vector<Individual> is;
    is.push_back(i);
    Simulation s(p,is);
    for (int i=0; i!=n_generations; ++i) { s.NextGeneration(); }
    assert(s.GetGenerations().back().GetIndividuals() == is);
  }
  //Simulations should be equal at construction from same parameters
  {
    const int dna_length{10};
    const int n_generations{1};
    const double mutation_rate{0.1};
    const int pop_size{1};
    const int seed{42};
    const Parameters p(dna_length,mutation_rate,n_generations,pop_size,seed);
    const Simulation s(p);
    const Simulation t(p);
    assert(s.GetGenerations().size() == 1); //Initial generation is present
    assert(t.GetGenerations().size() == 1);
    assert(s.GetGenerations().front().GetIndividuals().size() == pop_size);
    assert(t.GetGenerations().front().GetIndividuals().size() == pop_size);
    const auto kid1 = s.GetGenerations().front().GetIndividuals()[0];
    const auto kid2 = t.GetGenerations().front().GetIndividuals()[0];
    assert(kid1 == kid1);
    assert(kid2 == kid2);
    assert(kid1.GetDna() == kid2.GetDna());
    assert(kid1 == kid2);
    assert(s.GetGenerations() == t.GetGenerations());
    assert(s == t);
  }
}
#endif

