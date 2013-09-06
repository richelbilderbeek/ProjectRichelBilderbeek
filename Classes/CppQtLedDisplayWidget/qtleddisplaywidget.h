//---------------------------------------------------------------------------
/*
QtLedWidget, Qt widget for displaying the Led class
Copyright (C) 2011 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppQtLedWidget.htm
//---------------------------------------------------------------------------
#ifndef QTLEDDISPLAYWIDGET_H
#define QTLEDDISPLAYWIDGET_H

#include <string>
#include <vector>

#include <boost/scoped_ptr.hpp>

#include <QWidget>

#include "ledwidget.h" //Needed by MOC

namespace ribi {

///QtLedDisplayWidget displays a Led without
///managing it.
class QtLedDisplayWidget : public QWidget
{
  Q_OBJECT
public:
  explicit QtLedDisplayWidget(
    QWidget *parent = 0,
    LedWidget * const widget = 0);
  void SetLed(const LedWidget * const led);
protected:
  void paintEvent(QPaintEvent *);

private:
  const LedWidget * m_widget;

public:
static const std::string GetVersion();
static const std::vector<std::string> GetVersionHistory();

};

} //~namespace ribi

#endif // QTLEDDISPLAYWIDGET_H
