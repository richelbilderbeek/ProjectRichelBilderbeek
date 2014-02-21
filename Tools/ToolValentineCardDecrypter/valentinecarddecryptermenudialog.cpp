#include "valentinecarddecryptermenudialog.h"

#include <cassert>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/math/constants/constants.hpp>

#include <QFile>

#include "fileio.h"
//#include "imagecanvas.h"
#include "valentinecarddecryptermaindialog.h"
#include "valentinecardsymbols.h"
#include "valentinecardsymbol.h"
#include "textcanvas.h"

#include "trace.h"
#pragma GCC diagnostic pop

int ribi::ValentineCardDecrypterMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

  for (auto s: ValentineCardSymbols::CreateAlphabet().left)
  {

    std::cout << s.first << "\n" << (*s.second.ToTextCanvas()) << std::endl;
  }
  return 0;
}

const ribi::About ribi::ValentineCardDecrypterMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "ValentineCardDecrypter",
    "tool to decrypt a valentine card",
    "the 18th of February 2014",
    "2014",
    "http://www.richelbilderbeek.nl/ToolValentineCardDecrypter.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Canvas version: " + Canvas::GetVersion());
  a.AddLibrary("TextCanvas version: " + TextCanvas::GetVersion());
  return a;
}

const ribi::Help ribi::ValentineCardDecrypterMenuDialog::GetHelp() const noexcept
{
  return ribi::Help(
    GetAbout().GetFileTitle(),
    GetAbout().GetFileDescription(),
    {
    },
    {
    }
  );
}

const boost::shared_ptr<const ribi::Program> ribi::ValentineCardDecrypterMenuDialog::GetProgram() const noexcept
{
  boost::shared_ptr<const ribi::Program> p {
    //new ribi::ProgramValentineCardDecrypter
  };
  assert(p);
  return p;
}

const std::string ribi::ValentineCardDecrypterMenuDialog::GetVersion() const noexcept
{
  return "1.0";
}

const std::vector<std::string> ribi::ValentineCardDecrypterMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2014-02-18: version 1.0: initial version"
  };
}

#ifndef NDEBUG
void ribi::ValentineCardDecrypterMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::ValentineCardDecrypterMenuDialog::Test");
  //ValentineCardDecrypterMenuDialog d;
  TRACE("Finished ribi::ValentineCardDecrypterMenuDialog::Test successfully");
}
#endif
