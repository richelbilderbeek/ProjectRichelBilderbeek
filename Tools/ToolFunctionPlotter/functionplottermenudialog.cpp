#include "functionplottermenudialog.h"

#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/math/constants/constants.hpp>

#include "drawcanvas.h"
#include "functionplottermaindialog.h"
#include "testtimer.h"
#include "richelbilderbeekprogram.h"
#include "trace.h"
#pragma GCC diagnostic pop

int ribi::FunctionPlotterMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
  const int argc = static_cast<int>(argv.size());
  if (argc != 3 || (argv[1] != "-e" && argv[1] != "--equation"))
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }

  const std::string formula { argv[2] };
  const int n_cols = 78;
  const double x_min = 0.0;
  const double x_max = static_cast<double>(n_cols);
  const int n_rows = 20;

  try
  {
    const FunctionPlotterMainDialog d(
      formula,
      x_min,
      x_max,
      n_cols
    );

    const std::vector<double> xs { d.GetXs() };
    const std::vector<double> ys { d.GetYs() };
    assert(xs.size() == ys.size());

    boost::shared_ptr<DrawCanvas> canvas {
      new DrawCanvas(n_cols,n_rows,CanvasColorSystem::invert)
    };
    const int sz = static_cast<int>(xs.size());
    for (int i=0; i!=sz; ++i)
    {
      canvas->DrawDot(xs[i],ys[i]);
    }
    std::cout << (*canvas) << std::endl;
    return 0;
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
    return 1;
  }
}

ribi::About ribi::FunctionPlotterMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "FunctionPlotter",
    "plots a function",
    "the 6th of February 2014",
    "2013-2015",
    "http://www.richelbilderbeek.nl/FunctionPlotter.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Canvas version: " + Canvas::GetVersion());
  a.AddLibrary("DrawCanvas version: " + DrawCanvas::GetVersion());
  a.AddLibrary("TestTimer version: " + TestTimer::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  a.AddLibrary("Warp's FunctionParser version: 4.4.3");
  return a;
}

ribi::Help ribi::FunctionPlotterMenuDialog::GetHelp() const noexcept
{
  return ribi::Help(
    GetAbout().GetFileTitle(),
    GetAbout().GetFileDescription(),
    {
      Help::Option('e',"equation","an equation")
    },
    {
      GetAbout().GetFileTitle() + " -e \"10 + (8 * sin(x / 10))\"",
      GetAbout().GetFileTitle() + " --equation \"10 + (8 * sin(x / 10))\""
    }
  );
}

boost::shared_ptr<const ribi::Program> ribi::FunctionPlotterMenuDialog::GetProgram() const noexcept
{
  boost::shared_ptr<const ribi::Program> p {
    new ribi::ProgramFunctionPlotter
  };
  assert(p);
  return p;
}

std::string ribi::FunctionPlotterMenuDialog::GetVersion() const noexcept
{
  return "2.2";
}

std::vector<std::string> ribi::FunctionPlotterMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2010-xx-xx: version 1.0: initial Windows-only version",
    "2010-xx-xx: version 1.1: added integration",
    "2013-12-05: version 2.0: port to Qt"
    "2014-02-06: version 2.1: added command-line version"
    "2014-07-04: version 2.2: desktop version plots nothing if function cannot be parsed"
  };
}

#ifndef NDEBUG
void ribi::FunctionPlotterMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
