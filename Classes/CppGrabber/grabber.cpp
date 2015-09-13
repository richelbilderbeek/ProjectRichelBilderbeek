#include "grabber.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QImage>
#include <QPixmap>
#include <QScreen>
#include <QApplication>
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::Grabber::Grabber(
  const int win_id,
  const std::string& filename
)
  : m_filename{filename},
    m_win_id{win_id}
{

}

ribi::Grabber::~Grabber() noexcept
{

}

std::string ribi::Grabber::GetVersion() noexcept
{
  return "1.2";
}

std::vector<std::string> ribi::Grabber::GetVersionHistory() noexcept
{
  return {
    "2014-08-04: Version 1.0: initial version",
    "2015-08-21: Version 1.1: replaced deprecated construct",
    "2015-09-13: Version 1.2: support both Qt4 and Qt5",
  };
}

void ribi::Grabber::Grab() const noexcept
{
  #if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
  const auto screens = QApplication::screens();
  const int n_screens = screens.size();
  if (n_screens == 0)
  {
    std::stringstream s;
    s << "WARNING: no screens, so no screenshot";
    TRACE(s.str());
    return;
  }
  if (n_screens != 1)
  {
    std::stringstream s;
    s << "WARNING: number of screens " << n_screens << " (instead of just one), taking screenshot of first";
    TRACE(s.str());
  }
  const QImage screenshot{screens[0]->grabWindow(m_win_id).toImage()};
  #else
  const QImage screenshot{QPixmap::grabWindow(m_win_id).toImage()};
  #endif

  screenshot.save(m_filename.c_str());
}

#ifndef NDEBUG
void ribi::Grabber::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  const bool verbose{false};
  if (verbose) { TRACE("Default-construction of Grabber"); }
  {
    const Grabber g(0);
  }
}
#endif
