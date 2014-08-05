#include "grabber.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QImage>
#include <QPixmap>

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
  return "1.0";
}

std::vector<std::string> ribi::Grabber::GetVersionHistory() noexcept
{
  return {
    "2014-08-04: Version 1.0: initial version",
  };
}

void ribi::Grabber::Grab() const noexcept
{
  const QImage screenshot{QPixmap::grabWindow(m_win_id).toImage()};
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
