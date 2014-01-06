//---------------------------------------------------------------------------
/*
QtSurfacePlotWidget, Qt widget for displaying a surface plot
Copyright (C) 2012-2014 Richel Bilderbeek

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
#ifndef QTSURFACEPLOTWIDGET_H
#define QTSURFACEPLOTWIDGET_H

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QWidget>
#pragma GCC diagnostic pop

namespace ribi {

struct QtSurfacePlotWidget : public QWidget
{
  Q_OBJECT
public:
  explicit QtSurfacePlotWidget(QWidget *parent = 0);

  ///Sets the image of the surface plot to the values of the vector
  ///The doubles can be in any range
  void SetSurfaceGrey(const std::vector<std::vector<double> >& surface);

  //Sets the image of the surface plot to the values of the vector
  //Assumes that the chars are in the range [0,255] (a char's range)
  //If the chars are in a shorter range, they will NOT be rescaled to [0,255]
  void SetSurfaceGrey(const std::vector<std::vector<unsigned char> >& surface);

  ///Obtain the version of this class
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();

protected:
  void paintEvent(QPaintEvent *);
  void resizeEvent(QResizeEvent *);

private:
  std::vector<std::vector<unsigned char> > m_surface;
};

} //~namespace ribi

#endif //QTSURFACEPLOTWIDGET_H
