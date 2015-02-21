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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "testshapemaindialog.h"

#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include "qtaboutdialog.h"
#include "qttestshapemaindialog.h"
#include "qtshapewidget.h"
#include "trace.h"
#include "ui_qttestshapemaindialog.h"
#pragma GCC diagnostic pop

ribi::QtTestShapeMainDialog::QtTestShapeMainDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtTestShapeMainDialog),
    m_dialog(new TestShapeMainDialog),
    m_widgets{}
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
  int i=0;
  for(boost::shared_ptr<ShapeWidget>& widget: m_dialog->GetShapes())
  {
    boost::shared_ptr<QtShapeWidget> w(new QtShapeWidget(widget));

    ui->my_layout->addWidget(w.get(),i/8,i%8,1,1);
    //If the QtShapeWidget is not stored, no glory
    m_widgets.push_back(w);
    ++i;
  }
}

ribi::QtTestShapeMainDialog::~QtTestShapeMainDialog() noexcept
{
  delete ui;
}

void ribi::QtTestShapeMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    boost::scoped_ptr<TestShapeMainDialog> dialog(new TestShapeMainDialog);
    boost::shared_ptr<QtShapeWidget> widget(new QtShapeWidget);
  }
}
