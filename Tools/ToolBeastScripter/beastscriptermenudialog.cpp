#include "beastscriptermenudialog.h"

#include <cassert>
#include <iostream>
#include <iterator>
#include <sstream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>

#include <QFile>

#include "container.h"
#include "dnasequence.h"
#include "fastafile.h"
#include "fileio.h"
#include "testtimer.h"
#include "richelbilderbeekprogram.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::BeastScripterMenuDialog::BeastScripterMenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::BeastScripterMenuDialog::ExecuteSpecific(const std::vector<std::string>& args) noexcept
{
  const int argc = static_cast<int>(args.size());
  if (argc == 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }

  bool silent{false};
  if (std::count(std::begin(args),std::end(args),"-e") || std::count(std::begin(args),std::end(args),"--silent"))
  {
    silent = true;
  }
  if (std::count(std::begin(args),std::end(args),"-f") == 0 && std::count(std::begin(args),std::end(args),"--fasta") == 0)
  {
    std::cout
      << "Please specify the FASTA filename you want to work with, "
      << "using the -f or --fasta flag"
      << std::endl
    ;
    return 1;
  }
  if (std::count(std::begin(args),std::end(args),"-f") + std::count(std::begin(args),std::end(args),"--fasta") == 2)
  {
    std::cout
      << "Please specify the FASTA filename you want to work with, "
      << "using either the -f or the --fasta flag"
      << std::endl
    ;
    return 1;
  }
  std::string fasta_filename = "";
  for (int i=1; i!=argc-1; ++i)
  {
    if (args[i] == "-f" || args[i] == "--fasta")
    {
      const int j{i+1};
      assert(j < argc);
      fasta_filename = args[j];
      break;
    }
  }
  if (fasta_filename == "")
  {
    std::cout
      << "After the -f or --fasta flag, please specify a filename"
      << std::endl
    ;
    return 1;
  }
  if (!fileio::FileIo().IsRegularFile(fasta_filename))
  {
    std::cout
      << "Could not find the FASTA file '" << fasta_filename << "', "
      << "please specify an existing file after the -f or --fasta flag"
      << std::endl
    ;
    return 1;
  }
  std::cout << "FASTA filename: " << fasta_filename << std::endl;












  if (std::count(std::begin(args),std::end(args),"-m") == 0 && std::count(std::begin(args),std::end(args),"--mcmc_length") == 0)
  {
    std::cout
      << "Please specify the MCMC chain length you want to use, "
      << "using the -m or --mcmc_length flag"
      << std::endl
    ;
    return 1;
  }
  if (std::count(std::begin(args),std::end(args),"-m") + std::count(std::begin(args),std::end(args),"--mcmc_length") == 2)
  {
    std::cout
      << "Please specify the MCMC chain length you want to use, "
      << "using either the -m or --mcmc_length flag"
      << std::endl
    ;
    return 1;
  }
  int mcmc_chain_length = 0;
  for (int i=1; i!=argc-1; ++i)
  {
    if (args[i] == "-m" || args[i] == "--mcmc_length")
    {
      const int j{i+1};
      assert(j < argc);
      try
      {
        mcmc_chain_length = std::stoi(args[j]);
      }
      catch (std::exception&)
      {
        std::cout
          << "Please specify the MCMC chain length you want to use, "
          << "by supplying a number after the -m or --mcmc_length flag"
          << std::endl
        ;
        return 1;
      }
      break;
    }
  }
  if (mcmc_chain_length <= 0)
  {
    std::cout
      << "Please supplying a non-zero positive number for the "
      << "MCMC chain length you want to use"
      << std::endl
    ;
    return 1;
  }
  std::cout << "MCMC chain length: " << mcmc_chain_length << std::endl;


  assert(!"Green in main");
  //    "-t", "birth_death"


  return 0;
}

ribi::About ribi::BeastScripterMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "BeastScripter",
    "tool to work with BEAST using scripts",
    "the 24th of September 2015",
    "2015-2015",
    "http://www.richelbilderbeek.nl/ToolBeastScripter.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Container version: " + Container().GetVersion());
  a.AddLibrary("FileIo version: " + fileio::FileIo().GetVersion());
  a.AddLibrary("TestTimer version: " + TestTimer::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::BeastScripterMenuDialog::GetHelp() const noexcept
{
  return ribi::Help(
    GetAbout().GetFileTitle(),
    GetAbout().GetFileDescription(),
    {
      Help::Option('e',"silent","Produce no output"),
      Help::Option('f',"fasta","FASTA filename"),
      Help::Option('m',"mcmc_length","MCMC chain length"),
      Help::Option('t',"tree_prior","Tree prior"),
    },
    {
      "BeastScripter -f myfile.fas -m 100000 -t birth_death",
    }
  );
}

boost::shared_ptr<const ribi::Program> ribi::BeastScripterMenuDialog::GetProgram() const noexcept
{
  //const boost::shared_ptr<const ribi::Program> p(new ProgramBeastScripter);
  //assert(p);
  boost::shared_ptr<const ribi::Program> p;
  return p;
}

std::string ribi::BeastScripterMenuDialog::GetVersion() const noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::BeastScripterMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2015-09-24: version 1.0: initial version",
  };
}

#ifndef NDEBUG
void ribi::BeastScripterMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    Container();
    fileio::FileIo();
    DnaSequence("description","ACGT");
    FastaFile( std::vector<ribi::DnaSequence>() );
    BeastScripterMenuDialog().GetHelp();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  const std::string temp_filename{fileio::FileIo().GetTempFileName(".fas")};
  {
    QFile f(":CppBeast/test_output_0.fas");
    f.copy(temp_filename.c_str());
    const FastaFile fasta_file(temp_filename);
    assert(!fasta_file.GetSequences().empty());
  }
  BeastScripterMenuDialog d;
  d.Execute(
    {
      "BeastScripter",
      "-f", temp_filename,
      "-m", "100000",
      "-t", "birth_death"
    }
  );

  //Command line tests
  {

    //BeastParameterFile(
    //  FastaFile().GetSequences
    //  base of FastaFileName
    //  const std::string& alignment_base_filename,
    //  const int mcmc_chainlength,
    //  const TreePrior tree_prior
    //);

    d.Execute( { "BeastScripter", "--text", "\"Hello world\"", "-s", "0", "--silent" } );
  }
  //BeastScripter -f myfile.fas -m 100000 -t birth_death

  fileio::FileIo().DeleteFile(temp_filename);
  assert(!"Green");
}
#endif
