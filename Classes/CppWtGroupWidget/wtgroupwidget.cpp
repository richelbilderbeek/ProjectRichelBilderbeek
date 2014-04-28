//---------------------------------------------------------------------------
/*
WtGroupWidget, Wt widget for displaying groups
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
//From http://www.richelbilderbeek.nl/CppWtGroupWidget.htm

#include <algorithm>
#include <iostream>
#include <numeric>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
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

#include "rainbow.h"
#include "wtgroupwidget.h"
#pragma GCC diagnostic pop

ribi::WtGroupWidget::WtGroupWidget()
  : m_v{}
{
  this->resize(100,100);
}

void ribi::WtGroupWidget::DoRepaint()
{
  this->update();
}

int ribi::WtGroupWidget::GetMax(const std::vector<std::vector<int> >& v)
{
  assert(!v.empty());
  int max = 0;
  for(const auto w:v)
  {
    if (w.empty()) continue;
    const int x = *std::max_element(w.begin(),w.end());
    if (x > max) max = x;
  }
  return max;
}

const std::string ribi::WtGroupWidget::GetVersion()
{
  return "1.2";
}

const std::vector<std::string> ribi::WtGroupWidget::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("YYYY-MM-DD: version X.Y: [description]");
  v.push_back("2011-06-12: version 1.0: initial version");
  v.push_back("2011-06-16: version 1.1: allow display of empty groups");
  v.push_back("2011-06-22: version 1.2: allow display of zero groups");
  return v;
}

void ribi::WtGroupWidget::paintEvent(Wt::WPaintDevice *paintDevice)
{
  Wt::WPainter p(paintDevice);
  const int width  = this->width().toPixels();
  const int height = this->height().toPixels();
  //Draw a background rectangle
  {
    Wt::WPen pen = p.pen();
    pen.setColor(Wt::WColor(1,1,1));
    p.setPen(pen);
    p.setBrush(Wt::WBrush(Wt::WColor(254,254,254)));
    p.drawRect(0.0,0.0,width,height);
  }

  if (m_v.empty()) return;

  const double mid_x = 0.5 * boost::numeric_cast<double>(width);
  const double mid_y = 0.5 * boost::numeric_cast<double>(height);
  const double ray_center = std::min(mid_x,mid_y);
  const double ray_group  = 0.33 * ray_center;
  const double ray_member = 0.33 * ray_group;
  const int n_groups = boost::numeric_cast<double>(m_v.size());
  const int max_id = GetMax(m_v);

  for (int group=0; group!=n_groups; ++group)
  {
    //Draw the larger (group) circles first
    //Set the pen to black
    {
      Wt::WPen pen = p.pen();
      pen.setColor(Wt::WColor(1,1,1));
      p.setPen(pen);
    }
    const double f_group
     = (n_groups != 0
     ? static_cast<double>(group) / static_cast<double>(n_groups)
     : 1.0);

    //Set the brush to the group's index
    {
      double r,g,b;
      Rainbow::GetRgb(f_group,r,g,b);
      p.setBrush(Wt::WBrush(Wt::WColor(r*255.0,g*255.0,b*255.0)));
    }

    const double angle = 2.0 * boost::math::constants::pi<double>() * f_group;
    const double group_mid_x = mid_x + (std::sin(angle) * 0.66 * ray_center);
    const double group_mid_y = mid_y - (std::cos(angle) * 0.66 * ray_center);
    //Draw the group ellipse
    p.drawEllipse(
      group_mid_x - ray_group,
      group_mid_y - ray_group,
      2.0 * ray_group,
      2.0 * ray_group);
    const std::vector<int>& members = m_v[group];
    const int n_members = boost::numeric_cast<int>(members.size());
    for (int member=0; member!=n_members;++member)
    {
      //Set the brush to the members's index
      {
        const double f_id
          = (max_id != 0.0
          ? boost::numeric_cast<double>(members[member])
            / boost::numeric_cast<double>(max_id)
          : 1.0);
        double r,g,b;
        Rainbow::GetRgb(f_id,r,g,b);
        p.setBrush(Wt::WBrush(Wt::WColor(r*255.0,g*255.0,b*255.0)));
      }
      const double f_member
       = (n_members != 0
       ? static_cast<double>(member) / static_cast<double>(n_members)
       :  1.0);
      const double angle = 2.0 * boost::math::constants::pi<double>() * f_member;
      const double member_mid_x = group_mid_x + (std::sin(angle) * 0.66 * ray_group);
      const double member_mid_y = group_mid_y - (std::cos(angle) * 0.66 * ray_group);
      //Draw the member his/her ellipse
      p.drawEllipse(
        member_mid_x - ray_member,
        member_mid_y - ray_member,
        2.0 * ray_member,
        2.0 * ray_member);

    }
  }
}

void ribi::WtGroupWidget::SetIds(const std::vector<std::vector<int> >& v)
{
  m_v = v;
  update();
}

