//---------------------------------------------------------------------------
/*
TriangleMeshCreator, creates a 3D mesh using Triangle,
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
//From http://www.richelbilderbeek.nl/ToolTriangleMeshCreator.htm
//---------------------------------------------------------------------------
#include "trianglemeshcreatormenudialog.h"

#include <cassert>
#include <iostream>
#include <memory>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/lexical_cast.hpp>

#include "fileio.h"
#include "geometry.h"
#include "plane.h"
#include "richelbilderbeekprogram.h"
#include "trace.h"
#pragma GCC diagnostic pop

int ribi::TriangleMeshCreatorMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

ribi::About ribi::TriangleMeshCreatorMenuDialog::GetAbout() const noexcept
{
  
  About a(
    "Richel Bilderbeek",
    "TriangleMeshCreator",
    "Create a 3D mesh using Triangle",
    "the 25th of April 2014",
    "2014-2014",
    "http://www.richelbilderbeek.nl/ToolTriangleMeshCreator.htm",
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
  return a;
}

ribi::Help ribi::TriangleMeshCreatorMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::TriangleMeshCreatorMenuDialog::GetProgram() const noexcept
{
  boost::shared_ptr<const ribi::Program> p {
    new ribi::ProgramTriangleMeshCreator
  };
  assert(p);
  return p;
}

std::string ribi::TriangleMeshCreatorMenuDialog::GetVersion() const noexcept
{
  return "1.4";
}

std::vector<std::string> ribi::TriangleMeshCreatorMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2014-xx-xx: version 1.0: initial version, named 'TestTriangleMesh', console version only",
    "2014-03-07: version 1.1: initial versioning",
    "2014-04-25: version 1.2: renamed to 'TriangleMeshCreator'",
    "2014-04-28: version 1.3: bugfixes",
    "2014-05-06: version 1.4: added desktop version"
  };
}

#ifndef NDEBUG
void ribi::TriangleMeshCreatorMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::TriangleMeshCreatorMenuDialog::Test");
  TriangleMeshCreatorMenuDialog d;
  d.Execute( {"TriangleMeshCreator" } );
  TRACE("Finished ribi::TriangleMeshCreatorMenuDialog::Test successfully");
}
#endif
