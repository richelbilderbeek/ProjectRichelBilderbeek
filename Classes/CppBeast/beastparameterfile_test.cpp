#ifndef NDEBUG
#include "beastparameterfile.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>

#include <QFile>

#include "fastafile.h"
#include "fileio.h"

void BeastParameterFile::Test() noexcept
{
  {
    static bool is_tested {false};
    if (is_tested) return;
    is_tested = true;
  }
  const ribi::fileio::FileIo fileio;
  const std::string beast_filename_birth_death_0{"birth_death_0.xml"};
  const std::string beast_filename_birth_death_1{"birth_death_1.xml"};
  const std::string coalescent_constant_population_0{"coalescent_constant_population_0.xml"};
  const std::string coalescent_constant_population_1{"coalescent_constant_population_1.xml"};
  const std::string fasta_filename_0{"test_output_0.fas"};
  const std::string fasta_filename_1{"test_output_1.fas"};
  const std::vector<std::string> resource_filenames
    =
    {
      beast_filename_birth_death_0,
      beast_filename_birth_death_1,
      coalescent_constant_population_0,
      coalescent_constant_population_1,
      fasta_filename_0,
      fasta_filename_1
    };
  //Create resources
  {
    for (const auto& s: resource_filenames)
    {
      if (!fileio.IsRegularFile(s))
      {
        QFile((std::string(":/CppBeast/") + s).c_str()).copy(s.c_str());
      }
      assert(fileio.IsRegularFile(s));
    }
  }
  //Compare fasta_filename_0 and birth_death
  {
    const FastaFile fasta_file(fasta_filename_0);
    const BeastParameterFile beast_file(
      fasta_file.GetSequences(),
      fileio.GetFileBasename(fasta_filename_0), //alignment_base_filename,
      10000000,
      BeastParameterFile::TreePrior::birth_death
    );
    const std::string temp_filename{"tmp.txt"};
    {
      std::ofstream f(temp_filename.c_str());
      f << beast_file;
    }
    if (fileio.FileToVector(temp_filename) != fileio.FileToVector(beast_filename_birth_death_0))
    {
      std::stringstream cmd; cmd << "diff -w " << temp_filename << " " << beast_filename_birth_death_0;
      const int error{std::system(cmd.str().c_str())};
      if (error)
      {
        std::clog << __FILE__ << ": error " << error << '\n';
      }
    }
    assert(
      fileio.FileToVector(temp_filename) == fileio.FileToVector(beast_filename_birth_death_0)
    );
  }
  //Compare fasta_filename_1 and birth_death
  {
    const FastaFile fasta_file(fasta_filename_1);
    const BeastParameterFile beast_file(
      fasta_file.GetSequences(),
      fileio.GetFileBasename(fasta_filename_1),
      10000000,
      BeastParameterFile::TreePrior::birth_death
    );
    const std::string temp_filename{"tmp.txt"};
    {
      std::ofstream f(temp_filename.c_str());
      f << beast_file;
    }
    if (fileio.FileToVector(temp_filename) != fileio.FileToVector(beast_filename_birth_death_1))
    {
      std::stringstream cmd; cmd << "diff -w " << temp_filename << " " << beast_filename_birth_death_1;
      const int error{std::system(cmd.str().c_str())};
      if (error)
      {
        std::clog << __FILE__ << ": error " << error << '\n';
      }
    }
    assert(
      fileio.FileToVector(temp_filename) == fileio.FileToVector(beast_filename_birth_death_1)
    );
  }
  //Compare fasta_filename_0 and coalescent_constant_population
  {
    const FastaFile fasta_file(fasta_filename_0);
    const BeastParameterFile beast_file(
      fasta_file.GetSequences(),
      fileio.GetFileBasename(fasta_filename_0),
      10000000,
      BeastParameterFile::TreePrior::coalescent_constant_population
    );
    const std::string temp_filename{"tmp.txt"};
    {
      std::ofstream f(temp_filename.c_str());
      f << beast_file;
    }
    if (fileio.FileToVector(temp_filename) != fileio.FileToVector(coalescent_constant_population_0))
    {
      std::stringstream cmd; cmd << "diff " << temp_filename << " " << coalescent_constant_population_0;
      const int error{std::system(cmd.str().c_str())};
      if (error)
      {
        std::clog << __FILE__ << ": error " << error << '\n';
      }
    }
    assert(
      fileio.FileToVector(temp_filename) == fileio.FileToVector(coalescent_constant_population_0)
    );
  }
  //Compare fasta_filename_1 and coalescent_constant_population
  {
    const FastaFile fasta_file(fasta_filename_1);
    const BeastParameterFile beast_file(
      fasta_file.GetSequences(),
      fileio.GetFileBasename(fasta_filename_1),
      10000000,
      BeastParameterFile::TreePrior::coalescent_constant_population
    );
    const std::string temp_filename{"tmp.txt"};
    {
      std::ofstream f(temp_filename.c_str());
      f << beast_file;
    }
    if (fileio.FileToVector(temp_filename) != fileio.FileToVector(coalescent_constant_population_1))
    {
      std::stringstream cmd; cmd << "diff " << temp_filename << " " << coalescent_constant_population_1;
      const int error{std::system(cmd.str().c_str())};
      if (error)
      {
        std::clog << __FILE__ << ": error " << error << '\n';
      }

    }
    assert(
      fileio.FileToVector(temp_filename) == fileio.FileToVector(coalescent_constant_population_1)
    );
  }
}
#endif

