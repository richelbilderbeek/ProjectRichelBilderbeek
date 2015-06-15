//---------------------------------------------------------------------------
/*
GTST, Game Theory Server
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
//From http://www.richelbilderbeek.nl/ProjectGtst.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/numeric/conversion/cast.hpp>
#include <boost/math/constants/constants.hpp>
#include "gtstchatshapefactory.h"
#include "rainbow.h"
#include "shape.h"
#include "shapewidget.h"
#pragma GCC diagnostic pop

boost::scoped_ptr<ribi::gtst::ChatShapeFactory> ribi::gtst::ChatShapeFactory::m_instance;

ribi::gtst::ChatShapeFactory::ChatShapeFactory()
  : m_widgets(CreateWidgets(56)),
    m_i(0)
{

}

///Obtain a nice series of ShapeWidgets
const std::vector<boost::shared_ptr<ribi::ShapeWidget> > ribi::gtst::ChatShapeFactory::CreateWidgets(const int n)
{
  const int width  = 24;
  const int height = 24;

  const std::vector<int> n_corners = {   0 /*,  3,  4,  5,   3,        4,  6,  7 */ };
  const std::vector<double> angles = { 0.0 /*,0.0,0.0,0.0,boost::math::constants::pi<double>(),0.25*boost::math::constants::pi<double>(),0.0,0.0 */ };
  assert(n_corners.size() == angles.size());
  const int n_colors_per_shape = 1 + (n / static_cast<int>(n_corners.size()));
  const int n_shape_types = static_cast<int>(n_corners.size());

  std::vector<boost::shared_ptr<ShapeWidget> > v;

  for (int shape_type = 0; shape_type!= n_shape_types; ++shape_type)
  {
    for (int color = 0; color!=n_colors_per_shape; ++color)
    {
      double f_color = static_cast<double>(color) / static_cast<double>(n_colors_per_shape);
      double r,g,b;
      Rainbow::GetRgb(f_color,r,g,b);
      boost::shared_ptr<ShapeWidget> shape(
        new ShapeWidget(
          n_corners[shape_type],
          angles[shape_type],
        0,0,width,height,
        boost::numeric_cast<unsigned char>(r * 255.0),
        boost::numeric_cast<unsigned char>(g * 255.0),
        boost::numeric_cast<unsigned char>(b * 255.0)));
      v.push_back(shape);
    }
  }
  std::random_shuffle(v.begin(),v.end());
  return v;
}

ribi::gtst::ChatShapeFactory * ribi::gtst::ChatShapeFactory::Get()
{
  if (!m_instance) m_instance.reset(new ChatShapeFactory);
  return m_instance.get();
}

///Obtain the next ShapeWidget
const boost::shared_ptr<ribi::ShapeWidget> ribi::gtst::ChatShapeFactory::GetNextWidget()
{
  assert(m_i >= 0);
  assert(m_i < boost::numeric_cast<int>(m_widgets.size()));
  boost::shared_ptr<ShapeWidget> widget = m_widgets[m_i];
  ++m_i;
  if (m_i == boost::numeric_cast<int>(m_widgets.size()))
  {
    m_i = 0;
  }
  return widget;
}

void ribi::gtst::ChatShapeFactory::Reset()
{
  m_i = 0;
}

