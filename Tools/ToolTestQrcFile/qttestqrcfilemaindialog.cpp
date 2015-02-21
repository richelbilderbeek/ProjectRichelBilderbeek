//---------------------------------------------------------------------------
/*
TestQrcFile, tool to test the QrcFile class
Copyright (C) 2012-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestQrcFile.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qttestqrcfilemaindialog.h"

#include <fstream>
#include <sstream>

#include <QFileDialog>

#include "fileio.h"
#include "qrcfile.h"
#include "testtimer.h"
#include "testqrcfilemenudialog.h"
#include "trace.h"
#include "ui_qttestqrcfilemaindialog.h"
#pragma GCC diagnostic pop

ribi::QtTestQrcFileMainDialog::QtTestQrcFileMainDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtTestQrcFileMainDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  ui->edit->setText("Tools/ToolTestQrcFile/ToolTestQrcFile.qrc");
}

ribi::QtTestQrcFileMainDialog::~QtTestQrcFileMainDialog() noexcept
{
  delete ui;
}

void ribi::QtTestQrcFileMainDialog::on_edit_textChanged(const QString &arg1)
{
  const std::string filename = "../../" + arg1.toStdString();
  if (!fileio::FileIo().IsRegularFile(filename))
  {
    ui->text_result->clear();
    const std::string text = "File '" + filename + "' does not exist.";
    ui->text_result->setPlainText(text.c_str());
    return;
  }

  QrcFile p(filename);

  std::stringstream s;
  s << p;

  ui->text_result->clear();
  ui->text_result->setPlainText(s.str().c_str());
}

#ifndef NDEBUG
void ribi::QtTestQrcFileMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
