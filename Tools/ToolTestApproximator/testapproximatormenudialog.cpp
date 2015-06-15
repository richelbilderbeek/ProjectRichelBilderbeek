#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "testapproximatormenudialog.h"

#include <cassert>
#include <iostream>

#include <boost/units/unit.hpp>
#include <boost/units/systems/si.hpp>

#include "approximator.h"
#include "canvas.h"
#include "drawcanvas.h"
#include "richelbilderbeekprogram.h"
#include "trace.h"
#include "testtimer.h"

#pragma GCC diagnostic pop

ribi::ToolTestApproximatorMenuDialog::ToolTestApproximatorMenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::ToolTestApproximatorMenuDialog::ExecuteSpecific(const std::vector<std::string>& /*argv*/) noexcept
{
  /*
  const int argc = static_cast<int>(argv.size());
  if (argc == 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  assert(!"TODO");
  return 1;
  */

  //Use Boost.Units to thoroughly check if Approximation is a good template:
  //If it even compiles with Boost.Units, it probably is
  {
    typedef boost::units::quantity<boost::units::si::time> Time;
    typedef boost::units::quantity<boost::units::si::velocity> Velocity;
    Approximator<Time,Velocity> a;
    a.Add(0.0 * boost::units::si::second,0.0 * boost::units::si::meters_per_second);
    a.Add(2.0 * boost::units::si::second,2.0 * boost::units::si::meters_per_second);
    #ifndef NDEBUG
    const Velocity v = a.Approximate(1.0 * boost::units::si::second);
    assert(v >= 0.99 * boost::units::si::meters_per_second
        && v <= 1.01 * boost::units::si::meters_per_second);
    #endif
  }

  typedef Approximator<double,int> Approximator_t;
  Approximator_t a;
  a.Add(20, 5);
  a.Add(30,15);
  a.Add(40, 5);
  a.Add(50,15);

  const int max_x = 78;
  const int max_y = 20;
  DrawCanvas c(
    max_x,
    max_y,
    CanvasColorSystem::invert,
    CanvasCoordinatSystem::graph
  );
  c.DrawLine(0.0,0.0,max_x,0.0);
  c.DrawLine(0.0,0.0,0.0,max_y);

  //Plot values (note: these won't be visible in Canvas)
  {
    std::vector<double> xs;
    std::vector<double> ys;
    for (const auto& p: a.Get())
    {
      c.DrawDot(
        static_cast<double>(p.first),
        static_cast<double>(p.second)
      );
    }
  }

  //Plot approximation
  {
    for (int t=0; t != max_x; ++t)
    {
      try
      {
        const double x = static_cast<double>(t);
        const double y = a.Approximate(x);
        c.DrawDot(x,y);
      }
      catch (ExceptionNoExtrapolation<Approximator_t::key_type>& e)
      {
        //X value not in range. OK not to plot then...
      }
    }
  }
  std::cout << c << std::endl;
  return 0;
}

ribi::About ribi::ToolTestApproximatorMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "ToolTestApproximator",
    "tests the Approximator class",
    "the 28th of August 2013",
    "2013-2015",
    "http://www.richelbilderbeek.nl/ToolTestApproximator.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Approximator version: " + Approximator<>::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::ToolTestApproximatorMenuDialog::GetHelp() const noexcept
{
  return Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {

    },
    {

    }
  );
}

boost::shared_ptr<const ribi::Program> ribi::ToolTestApproximatorMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const Program> p {
    new ProgramTestApproximator
  };
  assert(p);
  return p;
}

std::string ribi::ToolTestApproximatorMenuDialog::GetVersion() const noexcept
{
  return "1.2";
}

std::vector<std::string> ribi::ToolTestApproximatorMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2013-08-28: version 1.0: initial version",
    "2013-09-05: version 1.1: transition to namespace ribi",
    "2013-11-05: version 1.2: conformized for ProjectRichelBilderbeekConsole"
  };
}

#ifndef NDEBUG
void ribi::ToolTestApproximatorMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    Approximator<int,int>::Test();

  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
