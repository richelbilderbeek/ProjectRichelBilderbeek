#include "testtrianglemeshmenudialog.h"

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
#include "trace.h"
#pragma GCC diagnostic pop

int ribi::TestTriangleMeshMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

ribi::About ribi::TestTriangleMeshMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TestTriangleMesh",
    "tests the TriangleMesh class",
    "the 7th of March 2014",
    "2014",
    "http://www.richelbilderbeek.nl/ToolTestTriangleMesh.htm",
    GetVersion(),
    GetVersionHistory());
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

ribi::Help ribi::TestTriangleMeshMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::TestTriangleMeshMenuDialog::GetProgram() const noexcept
{
  boost::shared_ptr<const ribi::Program> p {
    new ribi::ProgramTestTriangleMesh
  };
  assert(p);
  return p;
}

std::string ribi::TestTriangleMeshMenuDialog::GetVersion() const noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::TestTriangleMeshMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2014-xx-xx: version 1.0: initial version"
    "2014-03-07: version 1.1: initial versioning"
  };
}

#ifndef NDEBUG
void ribi::TestTriangleMeshMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::TestTriangleMeshMenuDialog::Test");
  TestTriangleMeshMenuDialog d;
  d.Execute( {"TestTriangleMesh" } );
  TRACE("Finished ribi::TestTriangleMeshMenuDialog::Test successfully");
}
#endif
