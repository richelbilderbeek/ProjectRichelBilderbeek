//---------------------------------------------------------------------------
/*
QtLedWidget, Qt widget for displaying the Led class
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
//From http://www.richelbilderbeek.nl/CppQtLedWidget.htm
//---------------------------------------------------------------------------
#ifndef QTLEDDIALOG_H
#define QTLEDDIALOG_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtLedWidgetDialog;
}

namespace ribi {

struct LedWidget;

///Displays an LED as a dialog
class QtLedWidgetDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtLedWidgetDialog(QWidget *parent = 0);
  QtLedWidgetDialog(const QtLedWidgetDialog&) = delete;
  QtLedWidgetDialog& operator=(const QtLedWidgetDialog&) = delete;
  ~QtLedWidgetDialog();

  void SetWidget(const boost::shared_ptr<LedWidget>& widget) noexcept;
  boost::shared_ptr<LedWidget> GetWidget() const noexcept { return m_widget; }


private:
  Ui::QtLedWidgetDialog *ui;

  ///The widget to work on
  boost::shared_ptr<LedWidget> m_widget;
};

} //~namespace ribi

#endif // QTLEDDIALOG_H
