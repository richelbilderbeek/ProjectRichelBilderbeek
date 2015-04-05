#include <cassert>
#include <fstream>
#include <iostream>

#include <QFile>

#include "helper.h"
#include "parameters.h"
#include "simulation.h"

int main()
{
  //1) Read parameters from file
  const int dna_length{10};
  const double mutation_rate{0.01};
  const int n_generations{100};
  const int pop_size{100};
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
    if (!simulation.GetSequences().empty())
    {
      //Only show the sequence of the first individual
      std::cout << i << ": " << simulation.GetSequences()[0].GetSequence() << '\n';
    }
  }
}

