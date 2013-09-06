//---------------------------------------------------------------------------
/*
TestShape, tool to test the Shape and ShapeWidget classes
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
//From http://www.richelbilderbeek.nl/ToolTestShape.htm
//---------------------------------------------------------------------------
#ifndef QTTESTSHAPEMENUDIALOG_H
#define QTTESTSHAPEMENUDIALOG_H

#include <boost/scoped_ptr.hpp>

#include <QDialog>

namespace Ui {
class QtTestShapeMenuDialog;
}

namespace ribi {

struct TestShapeMenuDialog;

class QtTestShapeMenuDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtTestShapeMenuDialog(QWidget *parent = 0);
  ~QtTestShapeMenuDialog();

private slots:
  void on_button_start_clicked();
  void on_button_about_clicked();
  void on_button_quit_clicked();

private:
  Ui::QtTestShapeMenuDialog *ui;
  boost::scoped_ptr<TestShapeMenuDialog> m_dialog;

  ///Test this class
  static void Test();
};

} //~namespace ribi

#endif // QTTESTSHAPEMENUDIALOG_H
