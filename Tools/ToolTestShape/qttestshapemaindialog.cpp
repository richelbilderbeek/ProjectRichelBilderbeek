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
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "testshapemaindialog.h"

#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include "qtaboutdialog.h"
#include "qttestshapemaindialog.h"
#include "qtshapewidget.h"
#include "trace.h"
#include "ui_qttestshapemaindialog.h"

QtTestShapeMainDialog::QtTestShapeMainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtTestShapeMainDialog),
    m_dialog(new TestShapeMainDialog)
{
  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  #endif
  int i=0;
  BOOST_FOREACH(boost::shared_ptr<ShapeWidget>& widget,
    m_dialog->GetShapes())
  {
    boost::shared_ptr<QtShapeWidget> w(new QtShapeWidget(widget));

    ui->my_layout->addWidget(w.get(),i/8,i%8,1,1);
    //If the QtShapeWidget is not stored, no glory
    m_widgets.push_back(w);
    ++i;
  }
}

QtTestShapeMainDialog::~QtTestShapeMainDialog()
{
  delete ui;
}

void QtTestShapeMainDialog::changeEvent(QEvent *e)
{
  QDialog::changeEvent(e);
  switch (e->type()) {
  case QEvent::LanguageChange:
    ui->retranslateUi(this);
    break;
  default:
    break;
  }
}

void QtTestShapeMainDialog::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  {
    boost::scoped_ptr<TestShapeMainDialog> dialog(new TestShapeMainDialog);
    boost::shared_ptr<QtShapeWidget> widget(new QtShapeWidget);
  }
}
