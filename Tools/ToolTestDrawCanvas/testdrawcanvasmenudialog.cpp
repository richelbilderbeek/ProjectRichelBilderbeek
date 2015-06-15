#include "testdrawcanvasmenudialog.h"

#include <cassert>
#include <iostream>

#include "drawcanvas.h"
#include "richelbilderbeekprogram.h"
#include "trace.h"
#include "testtimer.h"

int ribi::TestDrawCanvasMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
  const int argc = static_cast<int>(argv.size());
  if (argc != 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  //Specify the dimensions of the canvas equal to the screen
  //Coordinat (0,0) is the top-left coordinat
  //Coordinat (79,23) is the bottom-right coordinat
  const int maxx = 79;
  const int maxy = 23;

  for (int i=0; i!=4; ++i)
  {
    const ribi::CanvasColorSystem color_system
      = i % 2 ? ribi::CanvasColorSystem::normal : ribi::CanvasColorSystem::invert;
    const ribi::CanvasCoordinatSystem coordinat_system
      = i / 2 ? ribi::CanvasCoordinatSystem::graph : ribi::CanvasCoordinatSystem::screen;
    ribi::DrawCanvas c( maxx, maxy, color_system, coordinat_system);

    //Draw smiley to Canvas

    //Determine and calculate dimensions and coordinats of smiley
    const double maxxD = static_cast<double>(maxx);
    const double maxyD = static_cast<double>(maxy);
    const double midX        = 0.50 * maxxD;
    const double midY        = 0.50 * maxyD;
    const double headRay     = 0.50 * maxyD;
    const double eyeLeftX    = 0.50 * maxxD - (0.35 * headRay) ;
    const double eyeLeftY    = 0.50 * maxyD - (0.25 * headRay) ;
    const double eyeRightX   = 0.50 * maxxD + (0.35 * headRay) ;
    const double eyeRightY   = 0.50 * maxyD - (0.25 * headRay) ;
    const double eyeRay      = 0.30 * headRay;
    const double mouthLeftX  = 0.50 * maxxD - (0.7 * headRay) ;
    const double mouthMidX   = 0.50 * maxxD;
    const double mouthRightX = 0.50 * maxxD + (0.7 * headRay) ;
    const double mouthLeftY  = 0.50 * maxyD + (0.2 * headRay) ;
    const double mouthMidY   = 0.50 * maxyD + (0.7 * headRay) ;
    const double mouthRightY = 0.50 * maxyD + (0.2 * headRay) ;
    //Draw the image on Canvas
    c.DrawCircle(midX, midY, headRay);
    c.DrawCircle(eyeLeftX, eyeLeftY, eyeRay);
    c.DrawDot(eyeLeftX, eyeLeftY);
    c.DrawCircle(eyeRightX, eyeRightY, eyeRay);
    c.DrawDot(eyeRightX, eyeRightY);
    c.DrawLine(mouthLeftX, mouthLeftY, mouthMidX, mouthMidY);
    c.DrawLine(mouthMidX, mouthMidY, mouthRightX, mouthRightY);
    c.DrawLine(mouthRightX, mouthRightY, mouthLeftX, mouthLeftY);
    //Display the image
    std::cout << c;
    std::cout << std::endl;
  }
  return 0;
}

ribi::About ribi::TestDrawCanvasMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TestDrawCanvas",
    "tests the DrawCanvas class",
    "the 10th of January 2014",
    "2013-2015",
    "http://www.richelbilderbeek.nl/ToolTestDrawCanvas.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Canvas version: " + Canvas::GetVersion());
  a.AddLibrary("DrawCanvas version: " + DrawCanvas::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::TestDrawCanvasMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::TestDrawCanvasMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const Program> p {
    new ProgramTestDrawCanvas
  };
  assert(p);
  return p;
}

std::string ribi::TestDrawCanvasMenuDialog::GetVersion() const noexcept
{
  return "1.2";
}

std::vector<std::string> ribi::TestDrawCanvasMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2013-08-28: version 1.0: initial desktop version, originally called TestCanvas",
    "2013-11-05: version 1.1: conformized for ProjectRichelBilderbeekConsole",
    "2014-01-10: version 1.2: renamed TestCanvas to TestDrawCanvas"
  };
}

#ifndef NDEBUG
void ribi::TestDrawCanvasMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  ribi::DrawCanvas();
}
#endif
