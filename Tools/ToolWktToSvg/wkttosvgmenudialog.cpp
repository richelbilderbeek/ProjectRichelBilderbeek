//---------------------------------------------------------------------------
/*
WktToSvg, tool to convert WKT to SVG
Copyright (C) 2014-2014 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolWktToSvg.htm
//---------------------------------------------------------------------------
#include "wkttosvgmenudialog.h"

#include <cassert>
#include <iostream>
#include <memory>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/lexical_cast.hpp>

#include <QRegExp>

#include "fileio.h"
#include "richelbilderbeekprogram.h"
#include "trace.h"
#include "wkttosvgmaindialog.h"
#pragma GCC diagnostic pop

ribi::WktToSvgMenuDialog::WktToSvgMenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::WktToSvgMenuDialog::ExecuteSpecific(const std::vector<std::string>& args) noexcept
{
  const int argc = static_cast<int>(args.size());

  //Verbosity
  bool verbose = false;
  if (std::count(args.begin(),args.end(),"-b") || std::count(args.begin(),args.end(),"--verbose"))
  {
    verbose = true;
    std::cout << "Verbose mode" << std::endl;
  }

  std::string wkt = "";
  for (int i=0; i!=argc-1; ++i)
  {
    if (args[i] == "-w" || args[i] == "--wkt" || args[i] == "--WKT")
    {
      wkt = args[i+1];
      break;
    }
  }
  if (wkt.empty())
  {
    std::cerr << "Please supply a WKT, e.g. 'POLYGON((1 1,1 -1,1 -1))" << std::endl;
    return 1;

  }
  if (verbose)
  {
    std::cout << "WKT: " << wkt << '\n';
  }

  try
  {
    const WktToSvgMainDialog d(
      wkt,
      verbose
    );
    std::cout << "SVG: " << d.GetSvg() << std::endl;
    return 0;
  }
  catch (std::exception& e)
  {
    std::cerr << "ERROR: Exception caught: " << e.what() << std::endl;
    return 1;
  }
  catch (...)
  {
    std::cerr << "ERROR: Unknown exception caught!" << std::endl;
    return 1;
  }
}

ribi::About ribi::WktToSvgMenuDialog::GetAbout() const noexcept
{
  
  About a(
    "Richel Bilderbeek",
    "WktToSvg",
    "tool to convert WKT to SVG",
    "the 10th of June 2014",
    "2014-2014",
    "http://www.richelbilderbeek.nl/ToolWktToSvg.htm",
    GetVersion(),
    GetVersionHistory()
  );
  a.AddLibrary("FileIo version: " + fileio::FileIo().GetVersion());
  return a;
}

ribi::Help ribi::WktToSvgMenuDialog::GetHelp() const noexcept
{
  return Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {
      Help::Option('w',"wkt","the WTK string"),
      Help::Option('b',"verbose","generate more output")
    },
    {
      GetAbout().GetFileTitle() + " --wtk POLYGON((1 1,-1 1,-1 -1,1 -1)) --verbose",
      GetAbout().GetFileTitle() + " -w POLYGON((0 1,-1 -1,1 -1)),POLYGON((0 -1,-1 1,1 1)) -b",
    }
  );
}

std::string ribi::WktToSvgMenuDialog::GetPolygonRegex()
{
  return
    "(POLYGON\\(\\(.*\\)\\))"
  ;
}

boost::shared_ptr<const ribi::Program> ribi::WktToSvgMenuDialog::GetProgram() const noexcept
{
  boost::shared_ptr<const ribi::Program> p {
    new ribi::ProgramWktToSvg
  };
  assert(p);
  return p;
}

//From http://www.richelbilderbeek.nl/CppGetRegexMatches.htm
std::vector<std::string> ribi::WktToSvgMenuDialog::GetRegexMatches(
  const std::string& s,
  const QRegExp& r_original
) noexcept
{
  QRegExp r(r_original);
  r.setMinimal(true); //QRegExp must be non-greedy
  std::vector<std::string> v;
  int pos = 0;
  while ((pos = r.indexIn(s.c_str(), pos)) != -1)
  {
    const QString q = r.cap(1);
    if (q.isEmpty()) break;
    v.push_back(q.toStdString());
    pos += r.matchedLength();
  }

  return v;
}

std::string ribi::WktToSvgMenuDialog::GetVersion() const noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::WktToSvgMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2014-06-10: version 1.0: initial version, supports polygon only"
  };
}

#ifndef NDEBUG
void ribi::WktToSvgMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::WktToSvgMenuDialog::Test");
  {
    WktToSvgMenuDialog d;
    d.Execute( {"WktToSvgMenuDialog", "--help" } );
    d.Execute(
      {
        "WktToSvgMenuDialog",
        "--wkt", "POLYGON((1 1,-1 1,-1 -1,1 -1))",
        "--verbose",
      }
    );
    d.Execute(
      {
        "WktToSvgMenuDialog",
        "-w", "POLYGON((0 1,-1 -1,1 -1)),POLYGON((0 -1,-1 1,1 1))",
        "-b"
      }
    );
  }
  TRACE("Finished ribi::WktToSvgMenuDialog::Test successfully");
}
#endif
