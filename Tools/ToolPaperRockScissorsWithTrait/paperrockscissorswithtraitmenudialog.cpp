#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "paperrockscissorswithtraitmenudialog.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <tuple>

#include <boost/lexical_cast.hpp>

#include <QFile>

#include "paperrockscissors.h"
#include "paperrockscissorswithtraitsimulation.h"
#include "fileio.h"
#include "richelbilderbeekprogram.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::prswt::MenuDialog::MenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::prswt::MenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc == 1)
  {
    std::cout << GetHelp() << '\n';
    return 0;
  }
  //Width
  int width = -1;
  {
    const auto i = std::find_if(std::begin(argv),std::end(argv),
      [](const std::string& s) { return s == "-x" || s == "--width"; }
    );
    if (i == std::end(argv))
    {
      std::cout << "Please specify a parameter for width" << std::endl;
      return 1;
    }
    auto j = i; ++j;
    if (j == std::end(argv))
    {
      std::cout << "Please specify a value for width" << std::endl;
      return 1;
    }
    const std::string s = *j;
    try
    {
      width = std::stoi(s);
    }
    catch (std::exception& e)
    {
      std::cout << "Please specify an integer for width" << std::endl;
      return 1;
    }
    if (width < 1)
    {
      std::cout << "Please specify a non-zero positive integer for width" << std::endl;
      return 1;
    }
  }
  assert(width >= 1);

  //Height
  int height = -1;
  {
    const auto i = std::find_if(std::begin(argv),std::end(argv),
      [](const std::string& s) { return s == "-y" || s == "--height"; }
    );
    if (i == std::end(argv))
    {
      std::cout << "Please specify a parameter for height" << std::endl;
      return 1;
    }
    auto j = i; ++j;
    if (j == std::end(argv))
    {
      std::cout << "Please specify a value for height" << std::endl;
      return 1;
    }
    const std::string s = *j;
    try
    {
      height = std::stoi(s);
    }
    catch (std::exception& e)
    {
      std::cout << "Please specify an integer for height" << std::endl;
      return 1;
    }
    if (height < 1)
    {
      std::cout << "Please specify a non-zero positive integer for height" << std::endl;
      return 1;
    }
  }
  assert(height >= 1);

  //Initialization
  Initialization initialization = Initialization::random;
  {
    const auto i = std::find_if(std::begin(argv),std::end(argv),
      [](const std::string& s) { return s == "-n" || s == "--initialization"; }
    );
    if (i == std::end(argv))
    {
      std::cout << "Please specify a parameter for initialization" << std::endl;
      return 1;
    }
    auto j = i; ++j;
    if (j == std::end(argv))
    {
      std::cout << "Please specify a value for initialization" << std::endl;
      return 1;
    }
    const std::string s = *j;
    try
    {
      initialization = ToInitialization(s);
    }
    catch (std::logic_error&)
    {
      std::cout << "Please specify an valid initialization" << std::endl;
      return 1;
    }
  }

  //rng_seed
  int rng_seed = -1;
  {
    const auto i = std::find_if(std::begin(argv),std::end(argv),
      [](const std::string& s) { return s == "-r" || s == "--rng_seed"; }
    );
    if (i == std::end(argv))
    {
      std::cout << "Please specify a parameter for rng_seed" << std::endl;
      return 1;
    }
    auto j = i; ++j;
    if (j == std::end(argv))
    {
      std::cout << "Please specify a value for rng_seed" << std::endl;
      return 1;
    }
    const std::string s = *j;
    try
    {
      rng_seed = std::stoi(s);
    }
    catch (std::exception& e)
    {
      std::cout << "Please specify an integer for rng_seed" << std::endl;
      return 1;
    }
  }

  //Height
  int n_timesteps = -1;
  {
    const auto i = std::find_if(std::begin(argv),std::end(argv),
      [](const std::string& s) { return s == "-t" || s == "--n_timesteps"; }
    );
    if (i == std::end(argv))
    {
      std::cout << "Please specify a parameter for n_timesteps" << std::endl;
      return 1;
    }
    auto j = i; ++j;
    if (j == std::end(argv))
    {
      std::cout << "Please specify a value for n_timesteps" << std::endl;
      return 1;
    }
    const std::string s = *j;
    try
    {
      n_timesteps = std::stoi(s);
    }
    catch (std::exception& e)
    {
      std::cout << "Please specify an integer for n_timesteps" << std::endl;
      return 1;
    }
    if (n_timesteps < 1)
    {
      std::cout << "Please specify a non-zero positive integer for n_timesteps" << std::endl;
      return 1;
    }
  }
  assert(n_timesteps >= 1);


  const Parameters parameters(
    width,
    height,
    initialization,
    rng_seed
  );

  std::cout << parameters << '\n';

  Simulation simulation(parameters);

  {
    std::cout << "0 "; //t
    const auto v = simulation.GetLastPopSizes();
    std::cout
      << std::get<0>(v) << " "
      << std::get<1>(v) << " "
      << std::get<2>(v) << " "
    ;
    const auto w = simulation.GetLastMeanTraits();
    std::cout
      << std::get<0>(w) << " "
      << std::get<1>(w) << " "
      << std::get<2>(w) << " "
    ;
    std::cout << '\n';
  }


  for (int t=0; t!=n_timesteps; ++t)
  {
    simulation.Next();

    std::cout << t << " ";
    const auto v = simulation.GetLastPopSizes();
    std::cout
      << std::get<0>(v) << " "
      << std::get<1>(v) << " "
      << std::get<2>(v) << " "
    ;
    const auto w = simulation.GetLastMeanTraits();
    std::cout
      << std::get<0>(w) << " "
      << std::get<1>(w) << " "
      << std::get<2>(w) << " "
    ;
    std::cout << '\n';
  }

  return 0;
}

ribi::About ribi::prswt::MenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "PaperRockScissors with trait",
    "paper-rock-scissors simulation with neutral trait",
    "the 24th of May 2015",
    "2015-2015",
    "http://www.richelbilderbeek.nl/ToolPaperRockScissors.htm",
    GetVersion(),
    GetVersionHistory()
  );
  a.AddLibrary("TestTimer version: " + TestTimer::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

boost::shared_ptr<const ribi::Program> ribi::prswt::MenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p(
    new ProgramPaperRockScissorsWithTrait
  );
  assert(p);
  return p;
}

std::string ribi::prswt::MenuDialog::GetVersion() const noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::prswt::MenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2015-05-03: Version 0.1: initial standalone version",
    "2015-05-11: Version 1.0: conformized version",
    "2015-05-24: Version 1.1: can run from command-line, put in namespace ribi::prswt"
  };
}

ribi::Help ribi::prswt::MenuDialog::GetHelp() const noexcept
{
  return ribi::Help(
    "PaperRockScissors",
    "paper-rock-scissors simulation",
    {
      Help::Option('x',"width","width of the grid"),
      Help::Option('y',"height","height of the grid"),
      Help::Option('n',"initialization","initialization of the grid"),
      Help::Option('r',"rng_seed","random number generator seed"),
      Help::Option('t',"n_timesteps","number of timesteps"),
      //No additional options
    },
    {
    }
  );
}

#ifndef NDEBUG
void ribi::prswt::MenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    fileio::FileIo();
    TestPaperRockScissors();
    Simulation(
      Parameters(
        1, //const int width,
        1, //const int height,
        Initialization::random,
        42 //const int rng_seed
      )
    );
    Help::Test();
  }

  const TestTimer test_timer(__func__,__FILE__,1.0);
  {
    const std::vector<std::string> v = {
      "-x","4",
      "-y","3",
      "-n","random",
      "-r","42",
      "-t","10",
    };
    MenuDialog m;
    assert(m.Execute(v) == 0);
  }
}
#endif
