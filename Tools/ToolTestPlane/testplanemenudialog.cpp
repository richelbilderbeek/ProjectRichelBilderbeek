#include "testplanemenudialog.h"

#include <cassert>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/lexical_cast.hpp>

#include "fparser.hh"

#include "coordinat3d.h"
#include "geometry.h"
#include "plane.h"
#include "trace.h"
#pragma GCC diagnostic pop

int ribi::TestPlaneMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

  if (argc == 5)
  {
    std::cout << "Construct plane from coefficients" << '\n';
    const Plane p(
      boost::lexical_cast<double>(argv[1]),
      boost::lexical_cast<double>(argv[2]),
      boost::lexical_cast<double>(argv[3]),
      boost::lexical_cast<double>(argv[4])
    );
  }
  else if (argc == 10)
  {
    std::cout << "Construct plane from three points" << '\n';
    const Plane p(
      boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>(
        boost::lexical_cast<double>(argv[1]),
        boost::lexical_cast<double>(argv[2]),
        boost::lexical_cast<double>(argv[3])
      ),
      boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>(
        boost::lexical_cast<double>(argv[4]),
        boost::lexical_cast<double>(argv[5]),
        boost::lexical_cast<double>(argv[6])
      ),
      boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>(
        boost::lexical_cast<double>(argv[7]),
        boost::lexical_cast<double>(argv[8]),
        boost::lexical_cast<double>(argv[9])
      )
    );
    std::cout
      << "Coefficients: " << '\n'
      << "  a: " << '\n'
      << p.GetCoefficients()[0] << '\n'
      << "  b: " << '\n'
      << p.GetCoefficients()[1] << '\n'
      << "  c: " << '\n'
      << p.GetCoefficients()[2] << '\n'
      << "  d: " << '\n'
      << p.GetCoefficients()[3] << '\n'
      << "Function: " << '\n'
      << p.ToFunction() << '\n'
    ;
  }


  return 0;
}

ribi::About ribi::TestPlaneMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TestPlane",
    "tests the Plane class",
    "the 7th of March 2014",
    "2014",
    "http://www.richelbilderbeek.nl/ToolTestPlane.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Coordinat3D version: " + Coordinat3D().GetVersion());
  a.AddLibrary("Plane version: " + Plane().GetVersion());
  a.AddLibrary("Geometry version: " + Geometry().GetVersion());
  a.AddLibrary("Warp's FunctionParser version: 4.4.3");
  return a;
}

ribi::Help ribi::TestPlaneMenuDialog::GetHelp() const noexcept
{
  return ribi::Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {

    },
    {

    }
  );
}

boost::shared_ptr<const ribi::Program> ribi::TestPlaneMenuDialog::GetProgram() const noexcept
{
  boost::shared_ptr<const ribi::Program> p {
    new ribi::ProgramTestPlane
  };
  assert(p);
  return p;
}

std::string ribi::TestPlaneMenuDialog::GetVersion() const noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::TestPlaneMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2014-03-07: version 1.0: initial version"
  };
}

#ifndef NDEBUG
void ribi::TestPlaneMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::TestPlaneMenuDialog::Test");
  TestPlaneMenuDialog d;
  d.Execute( {"TestPlane" } );
  d.Execute( {"TestPlane","30.0","-48.0","17.0","15.0"} );

  d.Execute(
    {
      "TestPlane",
      "1.0","1.0","10.0",
      "1.0","2.0","13.0",
      "2.0","1.0","12.0"
    }
  );
  //a_expected { -2.0 };
  //b_expected { -3.0 };
  //c_expected {  1.0 };
  //d_expected {  5.0 };
  assert(1==2);

  TRACE("Finished ribi::TestPlaneMenuDialog::Test successfully");
}
#endif
