#include <cassert>
#include <fstream>
#include <iostream>

#include <QFile>

#include "fileio.h"
#include "beast.h"
#include "beastparameterfile.h"
#include "beaststatefile.h"
#include "fastafile.h"
#include "helper.h"
#include "parameters.h"
#include "simulation.h"
#include "trace.h"

int main()
{
  Beast();
  BeastStateFile::Test();
  const bool verbose{true};

  if (verbose) { TRACE("1) Read parameters from file"); }



  const int dna_length{100};
  const double mutation_rate{0.0001};
  const int n_generations{1000};
  const int pop_size{100};
  const int seed{42};
  const Parameters parameters(
    dna_length,
    mutation_rate,
    n_generations,
    pop_size,
    seed
  );
  const int mcmc_chainlength{10000};

  if (verbose) { TRACE("2) Run simulation"); }

  Simulation simulation(parameters);
  //Loop n_generations
  for (int i=0; i!=n_generations; ++i)
  {
    simulation.NextGeneration();
  }

  if (verbose) { TRACE("Start simulation"); }
  for (const BeastParameterFile::TreePrior tree_prior:
    {
      BeastParameterFile::TreePrior::birth_death,
      BeastParameterFile::TreePrior::coalescent_constant_population
    }
  )
  {
    const std::string alignment_base_filename{
      tree_prior == BeastParameterFile::TreePrior::birth_death
        ? "birthdeath_birthdeath"
        : "coalescent_coalescent"
    };
    const std::string beast_xml_output_filename{alignment_base_filename + ".xml"};
    const std::string fasta_output_filename{alignment_base_filename + ".fas"};

    if (verbose) { TRACE("3) Create BEAST2 XML parameter file"); }

    const BeastParameterFile beast_parameter_file(
      simulation.GetSequences(),
      alignment_base_filename,
      mcmc_chainlength,
      tree_prior

    );
    {
      std::ofstream f(beast_xml_output_filename.c_str());
      f << beast_parameter_file;
    }

    const FastaFile fasta_file(
      simulation.GetSequences()
    );
    {
      std::ofstream f(fasta_output_filename);
      f << fasta_file;
    }
    std::cout << fasta_file << std::endl;

    if (verbose) { TRACE("Start BEAST2"); }


    Beast().Run(
      beast_xml_output_filename,
      alignment_base_filename + ".log",
      alignment_base_filename + ".trees"
    );
    assert(ribi::fileio::FileIo().IsRegularFile(beast_xml_output_filename));
  }

  if (verbose) { TRACE("Interpret BEAST2 results"); }
  {
    const std::string s{"Beaster.R"};
    if (!Helper().IsRegularFileStl(s))
    {
      QFile((std::string(":/files/") + s).c_str()).copy(s.c_str());
    }
    assert(Helper().IsRegularFileStl(s));
    std::system("Rscript Beaster.R");
  }

  if (verbose) { TRACE("Check BEAST2 results"); }
  if ( Helper().IsRegularFileStl("coalescent_coalescent.svg")
    && Helper().IsRegularFileStl("birthdeath_birthdeath.svg")
  )
  {
    std::clog << "OK" << std::endl;
  }
  else
  {
    std::clog << "ERROR: final SVGs not created" << std::endl;
  }
}

