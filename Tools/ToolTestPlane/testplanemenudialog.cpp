//---------------------------------------------------------------------------
/*
TestPlane, tests the Plane class
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
//From http://www.richelbilderbeek.nl/ToolTestPlane.htm
//---------------------------------------------------------------------------
#include "testplanemenudialog.h"

#include <cassert>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/lexical_cast.hpp>

#include "container.h"
#include "fileio.h"

#include "geometry.h"
#include "plane.h"
#include "richelbilderbeekprogram.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::TestPlaneMenuDialog::TestPlaneMenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::TestPlaneMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  typedef apfloat Apfloat;
  typedef boost::geometry::model::point<Apfloat,3,boost::geometry::cs::cartesian> Point3D;

  const int argc = static_cast<int>(argv.size());
  if (argc == 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  /*
  if (argc == 5)
  {
    std::stringstream s;
    s << "Construct plane from coefficients" << '\n';
    try
    {
      const Plane p(
        boost::lexical_cast<double>(argv[1]),
        boost::lexical_cast<double>(argv[2]),
        boost::lexical_cast<double>(argv[3]),
        boost::lexical_cast<double>(argv[4])
      );
    }
    catch (std::logic_error& e)
    {
      s << "Exception: " << e.what() << '\n';
    }
    std::cout << s.str() << '\n';
  }
  else
  */
  if (argc == 10)
  {
    std::stringstream s;
    s << "Construct plane from three points" << '\n';

    const Point3D p1(
      boost::lexical_cast<double>(argv[1]),
      boost::lexical_cast<double>(argv[2]),
      boost::lexical_cast<double>(argv[3])
    );

    s << "Point 1: " << Geometry().ToStr(p1) << '\n';

    const Point3D p2(
      boost::lexical_cast<double>(argv[4]),
      boost::lexical_cast<double>(argv[5]),
      boost::lexical_cast<double>(argv[6])
    );

    s << "Point 2: " << Geometry().ToStr(p2) << '\n';

    const Point3D p3(
      boost::lexical_cast<double>(argv[7]),
      boost::lexical_cast<double>(argv[8]),
      boost::lexical_cast<double>(argv[9])
    );

    s << "Point 3: " << Geometry().ToStr(p3) << '\n';

    const boost::shared_ptr<ribi::Plane> plane(new ribi::Plane(p1,p2,p3));
    try
    {
      s << "Function (X): " << '\n' //<< plane->ToFunctionX() << '\n'
        << "Coefficients (X): " << '\n'
        << " - A: " << plane->GetCoefficientsX()[0] << '\n'
        << " - B: " << plane->GetCoefficientsX()[1] << '\n'
        << " - C: " << plane->GetCoefficientsX()[2] << '\n'
        << " - D: " << plane->GetCoefficientsX()[3] << '\n'
      ;
    }
    catch (std::logic_error& e)
    {
      s << "Exception: " << e.what() << '\n';
    }

    try
    {
      s << "Function (Y): " << '\n' //plane->ToFunctionY() << '\n'
        << "Coefficients (Y): " << '\n'
        << " - A: " << plane->GetCoefficientsY()[0] << '\n'
        << " - B: " << plane->GetCoefficientsY()[1] << '\n'
        << " - C: " << plane->GetCoefficientsY()[2] << '\n'
        << " - D: " << plane->GetCoefficientsY()[3] << '\n'
      ;
    }
    catch (std::logic_error& e)
    {
      s << "Exception: " << e.what() << '\n';
    }

    try
    {
      s << "Function (Z): " << '\n' //plane->ToFunctionZ() << '\n'
        << "Coefficients (Z): " << '\n'
        << " - A: " << plane->GetCoefficientsZ()[0] << '\n'
        << " - B: " << plane->GetCoefficientsZ()[1] << '\n'
        << " - C: " << plane->GetCoefficientsZ()[2] << '\n'
        << " - D: " << plane->GetCoefficientsZ()[3] << '\n'
      ;
    }
    catch (std::logic_error& e)
    {
      s << "Exception: " << e.what() << '\n';
    }
    std::cout << s.str() << '\n';
  }


  return 0;
}

ribi::About ribi::TestPlaneMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TestPlane",
    "tests the Plane class",
    "the 7th of July 2014",
    "2014",
    "http://www.richelbilderbeek.nl/ToolTestPlane.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Container version: " + Container().GetVersion());
  a.AddLibrary("FileIo version: " + fileio::FileIo().GetVersion());
  a.AddLibrary("Geometry version: " + Geometry().GetVersion());
  a.AddLibrary("Plane version: " + Plane::GetVersion());
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
  return "1.5";
}

std::vector<std::string> ribi::TestPlaneMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2014-03-07: version 1.0: initial version",
    "2014-06-13: version 1.1: allow setting a high precision in desktop version",
    "2014-06-13: version 1.2: use of operator<< instead of ToStr",
    "2014-06-16: version 1.3: use of QDoubleSpinBox instead of QSlider in desktop version",
    "2014-07-07: version 1.4: investigate Plane::IsInPlane in desktop version",
    "2014-07-10: version 1.5: use of apfloat in Plane"
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
  TRACE("Finished ribi::TestPlaneMenuDialog::Test successfully");
}


#endif
