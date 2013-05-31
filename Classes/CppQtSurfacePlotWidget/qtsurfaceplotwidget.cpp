//---------------------------------------------------------------------------
/*
QtSurfacePlotWidget, Qt widget for displaying a surface plot
Copyright (C) 2012 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppQtSurfacePlotWidget.htm
//---------------------------------------------------------------------------
#include <algorithm>
#include <cassert>
#include <vector>
//---------------------------------------------------------------------------
#include <QPainter>
//---------------------------------------------------------------------------
#include "qtsurfaceplotwidget.h"
//---------------------------------------------------------------------------
QtSurfacePlotWidget::QtSurfacePlotWidget(QWidget *parent)
  : QWidget(parent)
{
  std::vector<std::vector<unsigned char> > v(128,std::vector<unsigned char>(128));
  for(int y=0; y!=128; ++y)
  {
    for (int x=0; x!=128; ++x)
    {
      v[y][x] = x + y;
    }
  }
  SetSurfaceGrey(v);
}
//---------------------------------------------------------------------------
const std::string QtSurfacePlotWidget::GetVersion()
{
  return "1.0";
}
//---------------------------------------------------------------------------
const std::vector<std::string> QtSurfacePlotWidget::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2012-07-14: version 1.0: initial version");
  return v;
}
//---------------------------------------------------------------------------
void QtSurfacePlotWidget::SetSurfaceGrey(const std::vector<std::vector<double> >& v)
{
  //Get the size
  const int maxx = v[0].size();
  const int maxy = v.size();
  //Minimum and maximum are not given, so these need to be calculated
  double min_val = *(std::min_element(v[0].begin(),v[0].end()));
  double max_val = *(std::max_element(v[0].begin(),v[0].end()));
  for (int y=1; y!=maxy; ++y) //1, because 0 gets know the lines above
  {
    const double local_min_val = *(std::min_element(v[y].begin(),v[y].end()));
    const double local_max_val = *(std::max_element(v[y].begin(),v[y].end()));
    if (local_min_val < min_val) min_val = local_min_val;
    if (local_max_val > max_val) max_val = local_max_val;
  }
  //Create a black surface of type unsigned char
  std::vector<std::vector<unsigned char> > w(maxy,std::vector<unsigned char>(maxx,0));
  if (min_val == max_val)
  {
    //Keep black surface in w black
  }
  else
  {
    for (int y=0; y!=maxy; ++y)
    {
      const std::vector<double>& line_in = v[y];
      std::vector<unsigned char>& line_out = w[y];
      for (int x=0; x!=maxx; ++x)
      {
        assert(min_val != max_val);
        assert(min_val < max_val);
        assert(x < static_cast<int>(line_in.size()));
        const double grey_double = (line_in[x] - min_val) / (max_val - min_val);
        assert(grey_double >= 0.0 && grey_double <= 1.0);
        const unsigned char grey = grey_double * 255.0;
        assert(x < static_cast<int>(line_out.size()));
        line_out[x] = grey;
      }
    }
  }
  SetSurfaceGrey(w);
}
//---------------------------------------------------------------------------
void QtSurfacePlotWidget::SetSurfaceGrey(const std::vector<std::vector<unsigned char> >& surface)
{
  m_surface = surface;
  this->repaint();
}
//---------------------------------------------------------------------------
void QtSurfacePlotWidget::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  assert(!m_surface.empty());
  const int maxy = m_surface.size();
  assert(maxy > 0);
  const int maxx = m_surface[0].size();
  assert(maxx > 0);
  QImage image (maxx,maxy,QImage::Format::Format_RGB32);

  for (int y=0; y!=maxy; ++y)
  {
    std::vector<unsigned char>& line = m_surface[y];
    for (int x=0; x!=maxx; ++x)
    {
      assert(x < static_cast<int>(line.size()));
      const unsigned char grey = line[x];
      image.setPixel(x,y,qRgb(grey,grey,grey));
    }
  }
  painter.drawPixmap(0,0,this->width(),this->height(),QPixmap::fromImage(image));

}
//---------------------------------------------------------------------------
void QtSurfacePlotWidget::resizeEvent(QResizeEvent *)
{
  this->repaint();
}
//---------------------------------------------------------------------------
