#include "testmulticanvasmenudialog.h"

#include <cassert>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QFile>

#include "drawcanvas.h"
#include "fileio.h"
#include "imagecanvas.h"
#include "multicanvas.h"
#include "testtimer.h"
#include "richelbilderbeekprogram.h"
#include "textcanvas.h"
#include "trace.h"
#pragma GCC diagnostic pop

int ribi::TestMultiCanvasMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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
  /*
  const int maxx = 79;
  const int maxy = 23;

  for (int i=0; i!=4; ++i)
  {
    const ribi::CanvasColorSystem color_system
      = i % 2 ? ribi::CanvasColorSystem::normal : ribi::CanvasColorSystem::invert;
    const ribi::CanvasCoordinatSystem coordinat_system
      = i / 2 ? ribi::CanvasCoordinatSystem::graph : ribi::CanvasCoordinatSystem::screen;
    ribi::MultiCanvas c( maxx, maxy, color_system, coordinat_system);

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
  */
  return 0;
}

ribi::About ribi::TestMultiCanvasMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TestMultiCanvas",
    "tests the MultiCanvas class",
    "the 13th of January 2014",
    "2014-2015",
    "http://www.richelbilderbeek.nl/ToolTestMultiCanvas.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Canvas version: " + Canvas::GetVersion());
  a.AddLibrary("MultiCanvas version: " + MultiCanvas::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::TestMultiCanvasMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::TestMultiCanvasMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const Program> p {
    new ProgramTestMultiCanvas
  };
  assert(p);
  return p;
}

std::string ribi::TestMultiCanvasMenuDialog::GetVersion() const noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::TestMultiCanvasMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2014-01-13: version 1.0: initial desktop version",
  };
}

#ifndef NDEBUG
void ribi::TestMultiCanvasMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  boost::shared_ptr<Canvas> draw_canvas;
  const int n_cols = 78;
  {
    draw_canvas.reset(new DrawCanvas);
  }
  boost::shared_ptr<Canvas> image_canvas;
  {
    const std::string filename { fileio::FileIo().GetTempFileName() };
    QFile file(":/ToolTestMultiCanvas/images/R.png");
    file.copy(filename.c_str());
    assert(fileio::FileIo().IsRegularFile(filename));
    image_canvas.reset(
      new ImageCanvas(
        filename,
        n_cols
      )
    );
    //Note: cannot delete the file!
  }
  boost::shared_ptr<Canvas> text_canvas;
  {
    text_canvas.reset(new TextCanvas);
  }
  const std::vector<boost::shared_ptr<Canvas>> canvases { text_canvas, draw_canvas, image_canvas };
  const boost::shared_ptr<ribi::MultiCanvas> multi_canvas {
    new MultiCanvas(canvases)
  };
  std::stringstream s;
  s << (*multi_canvas);
  TRACE(*multi_canvas);
}
#endif
