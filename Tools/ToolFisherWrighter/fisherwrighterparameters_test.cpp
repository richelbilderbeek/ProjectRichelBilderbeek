#include "fisherwrighterparameters.h"

#include <cassert>
#include <fstream>

#ifndef NDEBUG
void ribi::fw::Parameters::Test() noexcept
{
  {
    static bool is_tested {false};
    if (is_tested) return;
    is_tested = true;
  }
  //Test recovery of parameters
  {
    const int dna_length{3495};
    const double mutation_rate{0.34758};
    const int n_generations{63223};
    const int pop_size{2376};
    const int seed{234};
    const Parameters p(
      dna_length,
      mutation_rate,
      n_generations,
      pop_size,
      seed
    );
    assert(p.GetDnaLength() == dna_length);
    assert(p.GetMutationRate() == mutation_rate);
    assert(p.GetNumberOfGenerations() == n_generations);
    assert(p.GetPopSize() == pop_size);
    assert(p.GetSeed() == seed);
  }
  {
    const int dna_length{345};
    const double mutation_rate{0.34758};
    const int n_generations{63223};
    const int pop_size{2376};
    const int seed{43};
    const Parameters original(
      dna_length,
      mutation_rate,
      n_generations,
      pop_size,
      seed
    );
    const std::string filename{"tmp.txt"};
    { std::ofstream f(filename.c_str()); f << original; }
    const Parameters p(Parameters::CreateParameters(filename));
    assert(p.GetDnaLength() == dna_length);
    assert(p.GetMutationRate() == mutation_rate);
    assert(p.GetNumberOfGenerations() == n_generations);
    assert(p.GetPopSize() == pop_size);
    assert(p.GetSeed() == seed);
  }
  //operator==
  {
    const int dna_length{3495};
    const double mutation_rate{0.34758};
    const int n_generations{63223};
    const int pop_size{2376};
    const int seed{234};
    const Parameters p(
      dna_length,
      mutation_rate,
      n_generations,
      pop_size,
      seed
    );
    const Parameters q(
      dna_length,
      mutation_rate,
      n_generations,
      pop_size,
      seed
    );
    assert(p == q);
  }
  //operator!=
  {
    const int dna_length{3495};
    const double mutation_rate{0.34758};
    const int n_generations{63223};
    const int pop_size{2376};
    const int seed{234};
    const Parameters p(
      dna_length,
      mutation_rate,
      n_generations,
      pop_size,
      seed
    );
    const Parameters q(
      dna_length,
      mutation_rate,
      n_generations,
      pop_size,
      seed + 1
    );
    assert(p != q);
  }
}
#endif

