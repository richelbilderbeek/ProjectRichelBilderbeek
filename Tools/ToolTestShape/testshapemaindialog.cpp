//---------------------------------------------------------------------------
/*
TestShape, tool to test the Shape and ShapeWidget classes
Copyright (C) 2011-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestShape.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"

#include "testshapemaindialog.h"

#include <boost/numeric/conversion/cast.hpp>
#include <boost/math/constants/constants.hpp>

#include "shape.h"
#include "testtimer.h"
#include "shapewidget.h"
#include "trace.h"

#pragma GCC diagnostic pop

ribi::TestShapeMainDialog::TestShapeMainDialog()
  : m_shapes(CreateShapes())
{
  #ifndef NDEBUG
  Test();
  #endif

}

std::vector<boost::shared_ptr<ribi::ShapeWidget> > ribi::TestShapeMainDialog::CreateShapes()
{
  std::vector<boost::shared_ptr<ShapeWidget> > v;
  for (int n_corners=0; n_corners!=8; ++n_corners)
  {
    for (int angle=0; angle!=8; ++angle)
    {
      #if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
      const double pi = M_PI;
      #else
      const double pi = boost::math::constants::pi<double>();
      #endif
      const double rotation = (boost::numeric_cast<double>(angle) / 8.0) * 2.0 * pi;
      const int r_i = (n_corners           * 32) % 256;
      const int g_i = (angle               * 32) % 256;
      const int b_i = ((n_corners + angle) * 32) % 256;
      const unsigned char r = boost::numeric_cast<unsigned char>(r_i);
      const unsigned char g = boost::numeric_cast<unsigned char>(g_i);
      const unsigned char b = boost::numeric_cast<unsigned char>(b_i);
      boost::shared_ptr<ShapeWidget> w(new ShapeWidget(
        n_corners,rotation,0,0,32,32,r,g,b));
      v.push_back(w);
    }
  }

  //std::random_shuffle(std::begin(v),std::end(v));
  return v;
}

#ifndef NDEBUG
void ribi::TestShapeMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
