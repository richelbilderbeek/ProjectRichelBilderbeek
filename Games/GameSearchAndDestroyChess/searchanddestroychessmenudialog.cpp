#include "searchanddestroychessmenudialog.h"

#include <algorithm>
#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"

#ifdef SADC_USE_THREADS
#include <thread>
#endif

#include "chessgame.h"
#include "trace.h"

#include <QFile>
#pragma GCC diagnostic pop

ribi::sadc::MenuDialog::MenuDialog()
{
  /*
  const std::vector<std::string> filenames = Chess::Resources::GetFilenames();

  std::for_each(filenames.begin(),filenames.end(),
    [](const std::string& filename)
  {
    if (!QFile::exists(filename.c_str()))
    {
      QFile f( (std::string(":/images/") + filename).c_str() );
        f.copy(filename.c_str());
    }
  } );

  #ifndef NDEBUG
  std::for_each(filenames.begin(),filenames.end(),
    [](const std::string& filename) { assert(QFile::exists(filename.c_str())); } );
  #endif
  */
}

const ribi::About ribi::sadc::MenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "SearchAndDestroyChess",
    "Kriegspiel",
    "the 23rd of Februari 2013",
    "2011",
    "http://www.richelbilderbeek.nl/GameSearchAndDestroyChess.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Artwork from GNU XBoard");
  //a.AddLibrary("Chess::Board2d version: " + Chess::Board2d::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

const std::string ribi::sadc::MenuDialog::GetVersion() const noexcept
{
  return "1.1";
}

const std::vector<std::string> ribi::sadc::MenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2011-06-28: Version 1.0: initial version",
    "2013-02-24: Version 1.1: testing done in seperate thread"
  };
}

#ifndef NDEBUG
void ribi::sadc::MenuDialog::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  #ifdef SADC_USE_THREADS
  std::thread t(
    []
  #endif
    {
      FTRACE("Testing MenuDialog");
      MenuDialog();
      Chess::Game();
    }
  #ifdef SADC_USE_THREADS
  );
  t.detach();
  #endif
}
#endif
