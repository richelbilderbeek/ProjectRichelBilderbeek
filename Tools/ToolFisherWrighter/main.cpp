#include <cassert>
#include <fstream>
#include <iostream>

#include <QFile>

#include "helper.h"
#include "parameters.h"
#include "simulation.h"

#include "newickutils.h"

int main()
{
  //1) Read parameters from file
  const int dna_length{10};
  const double mutation_rate{0.01};
  const int n_generations{10};
  const int pop_size{1000};
  const int seed{42};
  const Parameters parameters(
    dna_length,
    mutation_rate,
    n_generations,
    pop_size,
    seed
  );

  //2) Run simulation
  Simulation simulation(parameters);
  //Loop n_generations
  //const int n_generations{parameters.GetNumberOfGenerations()};
  for (int i=0; i!=n_generations; ++i)
  {
    simulation.NextGeneration();
    if (!simulation.GetCurrentSequences().empty())
    {
      //Only show the sequence of the first individual
      //std::cout << i << ": " << simulation.GetCurrentSequences()[0].GetSequence() << '\n';
    }
  }
  const std::string pedigree{simulation.GetPedigree()};

  //Display as newick
  std::cout << pedigree << std::endl;

  //Display as phylogeny
  NewickUtils().Display(pedigree);
}

