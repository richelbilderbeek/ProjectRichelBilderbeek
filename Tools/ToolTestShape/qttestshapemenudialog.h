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
#ifndef QTTESTSHAPEMENUDIALOG_H
#define QTTESTSHAPEMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/scoped_ptr.hpp>
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
class QtTestShapeMenuDialog;
}

namespace ribi {

struct TestShapeMenuDialog;

class QtTestShapeMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestShapeMenuDialog(QWidget *parent = 0);
  QtTestShapeMenuDialog(const QtTestShapeMenuDialog&) = delete;
  QtTestShapeMenuDialog& operator=(const QtTestShapeMenuDialog&) = delete;
  ~QtTestShapeMenuDialog() noexcept;

private slots:
  void on_button_start_clicked();
  void on_button_about_clicked();
  void on_button_quit_clicked();

private:
  Ui::QtTestShapeMenuDialog *ui;
  boost::scoped_ptr<TestShapeMenuDialog> m_dialog;

  ///Test this class
  static void Test() noexcept;
};

} //~namespace ribi

#endif // QTTESTSHAPEMENUDIALOG_H
