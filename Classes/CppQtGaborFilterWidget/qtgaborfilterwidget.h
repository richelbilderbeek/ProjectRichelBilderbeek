//---------------------------------------------------------------------------
/*
QtGaborFilterWidget, Qt widget for displaying the GaborFilter class
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
//From http://www.richelbilderbeek.nl/CppQtGaborFilterWidget.htm
//---------------------------------------------------------------------------
#ifndef QTGABORFILTERWIDGET_H
#define QTGABORFILTERWIDGET_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/scoped_ptr.hpp>

#include <QWidget>

#include "gaborfilter.h"         //Needed by MOC
#include "gaborfilterwidget.h"   //Needed by MOC
#pragma GCC diagnostic pop

namespace ribi {

class QtGaborFilterWidget : public QWidget
{
  Q_OBJECT
public:
  explicit QtGaborFilterWidget(
    QWidget *parent = 0,
    const double intensity    = 0.0,
    const unsigned char red   = 255,
    const unsigned char green =   0,
    const unsigned char blue  =   0);
  const GaborFilterWidget * GetWidget() const { return m_widget.get(); }
  GaborFilterWidget * GetWidget() { return m_widget.get(); }

  ///Draw a GaborFilter from a GaborFilter
  static void DrawGaborFilter(
    QPainter& painter,
    const int left, const int top,
    const int width, const int height,
    const GaborFilter * const gabor_filter);

  ///Draw a GaborFilter from a GaborFilterWidget
  static void DrawGaborFilter(
    QPainter& painter,
    const GaborFilterWidget * const widget);

protected:
  void paintEvent(QPaintEvent *);
  void resizeEvent(QResizeEvent *);

private:
  boost::scoped_ptr<GaborFilterWidget> m_widget;

  ///OnResize is called when the geometry of the GaborFilterWidget is changed
  void OnResize();

public:
  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

};

} //~namespace ribi

#endif // QTGABORFILTERWIDGET_H
