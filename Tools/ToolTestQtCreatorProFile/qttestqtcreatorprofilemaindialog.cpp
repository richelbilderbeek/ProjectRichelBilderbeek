//---------------------------------------------------------------------------
/*
TestQtCreatorProFile, tool to test the QtCreatorProFile class
Copyright (C) 2010-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestQtCreatorProFile.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qttestqtcreatorprofilemaindialog.h"

#include <sstream>

#include <QFile>
#include <QFileDialog>

#include "qtcreatorprofile.h"
#include "testqtcreatorprofilemenudialog.h"
#include "trace.h"
#include "ui_qttestqtcreatorprofilemaindialog.h"
#pragma GCC diagnostic pop

ribi::QtTestQtCreatorProFileMainDialog::QtTestQtCreatorProFileMainDialog(QWidget *parent)
 : QtHideAndShowDialog(parent),
   ui(new Ui::QtTestQtCreatorProFileMainDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtTestQtCreatorProFileMainDialog::~QtTestQtCreatorProFileMainDialog() noexcept
{
  delete ui;
}

void ribi::QtTestQtCreatorProFileMainDialog::on_button_select_clicked()
{
  const std::string filename
    = QFileDialog::getOpenFileName(
      this,"Please select a .pro file",
      QString(),
      "Qt Project files (*.pro)"
      ).toStdString();

  if (!QFile::exists(filename.c_str()))
  {
    ui->text_result->clear();
    const std::string text = "File '" + filename + "' does not exist.";
    ui->text_result->setPlainText(text.c_str());
    return;
  }

  const boost::shared_ptr<const QtCreatorProFile> p(new QtCreatorProFile(filename));

  std::stringstream s;
  s << p;

  ui->text_result->clear();
  ui->text_result->setPlainText(s.str().c_str());
}

#ifndef NDEBUG
void ribi::QtTestQtCreatorProFileMainDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtTestQtCreatorProFileMainDialog::Test");

  TRACE("Finished ribi::QtTestQtCreatorProFileMainDialog::Test successfully");
}
#endif
