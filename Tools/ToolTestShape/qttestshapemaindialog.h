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
#ifndef QTTESTSHAPEMAINDIALOG_H
#define QTTESTSHAPEMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestShapeMainDialog;
}

namespace ribi {

struct TestShapeMainDialog;
struct QtShapeWidget;

class QtTestShapeMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestShapeMainDialog(QWidget *parent = 0);
  QtTestShapeMainDialog(const QtTestShapeMainDialog&) = delete;
  QtTestShapeMainDialog& operator=(const QtTestShapeMainDialog&) = delete;
  ~QtTestShapeMainDialog() noexcept;

private:
  Ui::QtTestShapeMainDialog *ui;
  boost::scoped_ptr<TestShapeMainDialog> m_dialog;
  std::vector<boost::shared_ptr<QtShapeWidget> > m_widgets;

  ///Test this class
  static void Test() noexcept;
};

} //~namespace ribi

#endif // QTTESTSHAPEMAINDIALOG_H
