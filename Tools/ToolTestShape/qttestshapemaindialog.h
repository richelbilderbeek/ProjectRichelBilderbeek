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
#ifndef QTTESTSHAPEMAINDIALOG_H
#define QTTESTSHAPEMAINDIALOG_H

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include <QDialog>

namespace Ui {
  class QtTestShapeMainDialog;
}
struct TestShapeMainDialog;
struct QtShapeWidget;

class QtTestShapeMainDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtTestShapeMainDialog(QWidget *parent = 0);
  ~QtTestShapeMainDialog();

protected:
  void changeEvent(QEvent *e);

private:
  Ui::QtTestShapeMainDialog *ui;
  boost::scoped_ptr<TestShapeMainDialog> m_dialog;
  std::vector<boost::shared_ptr<QtShapeWidget> > m_widgets;

  ///Test this class
  static void Test();
};

#endif // QTTESTSHAPEMAINDIALOG_H
