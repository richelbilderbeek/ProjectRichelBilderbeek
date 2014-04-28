//---------------------------------------------------------------------------
/*
WtShapeGroupWidget, Wt widget for displaying Shapes
Copyright (C) 2011-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppWtShapeGroupWidget.htm
//---------------------------------------------------------------------------
#include <algorithm>
#include <iostream>
#include <numeric>


//#include <boost/numeric/conversion/bounds.hpp>
//#include <boost/bind.hpp>
//#include <boost/lambda/bind.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/math/constants/constants.hpp>

#include <Wt/WBrush>
#include <Wt/WEvent>
#include <Wt/WPaintDevice>
#include <Wt/WPainter>
#include <Wt/WPen>

#include "shape.h"
#include "wtgroupwidget.h"
#include "wtshapegroupwidget.h"
#include "wtshapewidget.h"

ribi::WtShapeGroupWidget::WtShapeGroupWidget()
  : m_v{}
{
  this->resize(100,100);
}

void ribi::WtShapeGroupWidget::DoRepaint()
{
  this->update();
}

const std::string ribi::WtShapeGroupWidget::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> ribi::WtShapeGroupWidget::GetVersionHistory()
{
  return {
    "2011-08-25: version 1.0: initial version"
  };
}

void ribi::WtShapeGroupWidget::paintEvent(Wt::WPaintDevice *paintDevice)
{
  Wt::WPainter painter(paintDevice);
  const int width  = this->width().toPixels();
  const int height = this->height().toPixels();
  //Draw a background rectangle
  {
    Wt::WPen pen = painter.pen();
    pen.setColor(Wt::WColor(1,1,1));
    painter.setPen(pen);
    painter.setBrush(Wt::WBrush(Wt::WColor(254,254,254)));
    painter.drawRect(0.0,0.0,width,height);
  }

  if (m_v.empty()) return;

  const double mid_x = 0.5 * boost::numeric_cast<double>(width);
  const double mid_y = 0.5 * boost::numeric_cast<double>(height);
  const double ray_center = std::min(mid_x,mid_y);
  const double ray_group  = 0.33 * ray_center;
  const double ray_member = 0.33 * ray_group;
  const int n_groups = boost::numeric_cast<double>(m_v.size());

  for (int group=0; group!=n_groups; ++group)
  {
    //Draw the larger (group) circles first
    //Set the pen to black
    {
      Wt::WPen pen = painter.pen();
      pen.setColor(Wt::WColor(1,1,1));
      painter.setPen(pen);
    }
    const double f_group
     = (n_groups != 0
     ? static_cast<double>(group) / static_cast<double>(n_groups)
     : 1.0);

    //Set the brush to the group's index
    {
      double r,g,b;
      Rainbow(f_group,r,g,b);
      painter.setBrush(Wt::WBrush(Wt::WColor(r*255.0,g*255.0,b*255.0)));
    }
    const double angle = 2.0 * boost::math::constants::pi<double>() * f_group;
    const double group_mid_x = mid_x + (std::sin(angle) * 0.66 * ray_center);
    const double group_mid_y = mid_y - (std::cos(angle) * 0.66 * ray_center);
    //Draw the group ellipse
    painter.drawEllipse(
      group_mid_x - ray_group,
      group_mid_y - ray_group,
      2.0 * ray_group,
      2.0 * ray_group);
    const std::vector<const Shape*>& members = m_v[group];
    const int n_members = boost::numeric_cast<int>(members.size());
    for (int member=0; member!=n_members;++member)
    {
      const double f_member
       = (n_members != 0
       ? static_cast<double>(member) / static_cast<double>(n_members)
       :  1.0);
      const double angle = 2.0 * boost::math::constants::pi<double>() * f_member;
      const double member_mid_x = group_mid_x + (std::sin(angle) * 0.66 * ray_group);
      const double member_mid_y = group_mid_y - (std::cos(angle) * 0.66 * ray_group);
      //Draw the member his/her Shape ellipse
      WtShapeWidget::DrawShape(painter,
        member_mid_x - ray_member,
        member_mid_y - ray_member,
        2.0 * ray_member,
        2.0 * ray_member,
        members[member]);
    }
  }
}

//From http://www.richelbilderbeek.nl/CppRainbow.htm
void ribi::WtShapeGroupWidget::Rainbow(
  const double x,
  double& r,
  double& g,
  double& b)
{
  const double f_r = std::max(0.0,
    (x < 0.5
    ? std::cos(x * 1.5 * boost::math::constants::pi<double>())
    : -std::sin(x * 1.5 * boost::math::constants::pi<double>())
    ) );
  const double f_g = std::max(0.0, std::sin( x * 1.5 * boost::math::constants::pi<double>() ) );
  const double f_b = std::max(0.0, -std::cos( x * 1.5 * boost::math::constants::pi<double>() ) );
  const double max = std::max(f_r, std::max(f_g,f_b));
  assert(max!=0);

  r = f_r / max;
  g = f_g / max;
  b = f_b / max;
}

void ribi::WtShapeGroupWidget::SetShapes(const std::vector<std::vector<const Shape*> >& v)
{
  m_v = v;
  update();
}

