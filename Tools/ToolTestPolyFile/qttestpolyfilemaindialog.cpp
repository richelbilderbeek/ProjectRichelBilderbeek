//---------------------------------------------------------------------------
/*
TestPolyFile, tool to test the PolyFile class
Copyright (C) 2014-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolTestPolyFile.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qttestpolyfilemaindialog.h"

#include <fstream>
#include <sstream>

#include <QFileDialog>

#include "fileio.h"
#include "polyfile.h"
#include "testpolyfilemenudialog.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qttestpolyfilemaindialog.h"
#pragma GCC diagnostic pop

ribi::QtTestPolyFileMainDialog::QtTestPolyFileMainDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtTestPolyFileMainDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  ui->edit->setText("Classes/CppPolyFile/polyfile1.poly");
}

ribi::QtTestPolyFileMainDialog::~QtTestPolyFileMainDialog() noexcept
{
  delete ui;
}

void ribi::QtTestPolyFileMainDialog::on_edit_textChanged(const QString &arg1)
{
  ui->text_result->clear();

  const std::string filename = "../../" + arg1.toStdString();
  if (!fileio::FileIo().IsRegularFile(filename))
  {
    const std::string text = "File '" + filename + "' does not exist.";
    ui->text_result->setPlainText(text.c_str());
    return;
  }


  std::stringstream s;
  try
  {
    PolyFile p(filename);
    s << p;
  }
  catch (std::exception& e)
  {
    s << "Error: " << e.what();
  }
  ui->text_result->setPlainText(s.str().c_str());

}

#ifndef NDEBUG
void ribi::QtTestPolyFileMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
