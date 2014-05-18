//---------------------------------------------------------------------------
/*
TestTriangle, compare Triangle to its C++ equivalent
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
//From http://www.richelbilderbeek.nl/ToolTestTriangle.htm
//---------------------------------------------------------------------------
#include "testtrianglemenudialog.h"

#include <cassert>
#include <iostream>
#include <memory>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/lexical_cast.hpp>

#include "fileio.h"
#include "geometry.h"
#include "plane.h"
#include "richelbilderbeekprogram.h"
#include "trace.h"
#include "trianglefile.h"
#pragma GCC diagnostic pop

int ribi::TestTriangleMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
  const int argc = static_cast<int>(argv.size());
  if (argc == 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  return 1;
}

ribi::About ribi::TestTriangleMenuDialog::GetAbout() const noexcept
{
  
  About a(
    "Richel Bilderbeek",
    "TestTriangle",
    "compare Triangle to its C++ equivalent",
    "the 18th of May 2014",
    "2014-2014",
    "http://www.richelbilderbeek.nl/ToolTestTriangle.htm",
    GetVersion(),
    GetVersionHistory()
  );
  a.AddLibrary("FileIo version: " + fileio::FileIo().GetVersion());
  a.AddLibrary("Geometry version: " + Geometry().GetVersion());
  const std::unique_ptr<Plane> plane(
    new Plane(
      Plane::Coordinat3D(0.0,0.0,0.0),
      Plane::Coordinat3D(1.0,0.0,0.0),
      Plane::Coordinat3D(0.0,1.0,0.0)
    )
  );
  assert(plane);
  a.AddLibrary("Plane version: " + plane->GetVersion());
  a.AddLibrary("Triangle version 1.6, by Jonathan Richard Shewchuk (http://www.cs.cmu.edu/~quake/triangle.html)");
  a.AddLibrary("TriangleFile version: " + TriangleFile::GetVersion());
  return a;
}

ribi::Help ribi::TestTriangleMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::TestTriangleMenuDialog::GetProgram() const noexcept
{
  boost::shared_ptr<const ribi::Program> p {
    new ribi::ProgramTestTriangle
  };
  assert(p);
  return p;
}

std::string ribi::TestTriangleMenuDialog::GetVersion() const noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::TestTriangleMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2014-05-09: version 1.0: initial version, uses Windows executable only",
    "2014-05-18: version 1.1: uses Linux executable additionally"
  };
}

#ifndef NDEBUG
void ribi::TestTriangleMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::TestTriangleMenuDialog::Test");
  TestTriangleMenuDialog d;
  d.Execute( {"TestTriangle" } );
  TRACE("Finished ribi::TestTriangleMenuDialog::Test successfully");
}
#endif
