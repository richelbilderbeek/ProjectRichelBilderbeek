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
#include "qttestshapemenudialog.h"

#include "about.h"
#include "qtaboutdialog.h"
#include "qtshapewidget.h"
#include "qttestshapemaindialog.h"
#include "shape.h"
#include "shapewidget.h"
#include "testshapemenudialog.h"
#include "ui_qttestshapemenudialog.h"
#pragma GCC diagnostic pop

ribi::QtTestShapeMenuDialog::QtTestShapeMenuDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtTestShapeMenuDialog),
  m_dialog(new TestShapeMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtTestShapeMenuDialog::~QtTestShapeMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtTestShapeMenuDialog::on_button_start_clicked()
{
  hide();
  QtTestShapeMainDialog d;
  d.exec();
  show();
}

void ribi::QtTestShapeMenuDialog::on_button_about_clicked()
{
  hide();
  About a = m_dialog->GetAbout();
  a.AddLibrary("QtShapeWidget version: " + QtShapeWidget::GetVersion());
  QtAboutDialog d(a);
  d.exec();
  show();
}

void ribi::QtTestShapeMenuDialog::on_button_quit_clicked()
{
  close();
}

void ribi::QtTestShapeMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    const QtTestShapeMainDialog d;
  }
  {
    const TestShapeMenuDialog d;
  }
}


