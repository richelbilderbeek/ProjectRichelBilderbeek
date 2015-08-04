//---------------------------------------------------------------------------
/*
RichelbilderbeekNlSitemapGenerator, generates the richelbilderbeek.nl sitemap
Copyright (C) 2010-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolRichelbilderbeekNlSitemapGenerator.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtsitemapgeneratormaindialog.h"

#include <cassert>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <boost/lexical_cast.hpp>
#include <boost/lambda/lambda.hpp>

#include <QKeyEvent>

#include "fileio.h"
#include "trace.h"
#include "testtimer.h"
#include "ui_qtsitemapgeneratormaindialog.h"
#include "sitemapgeneratormenudialog.h"
#pragma GCC diagnostic pop

ribi::QtSitemapGeneratorMainDialog::QtSitemapGeneratorMainDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtSitemapGeneratorMainDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtSitemapGeneratorMainDialog::~QtSitemapGeneratorMainDialog() noexcept
{
  delete ui;
}

void ribi::QtSitemapGeneratorMainDialog::keyPressEvent(QKeyEvent * e)
{
  if (e->key()  == Qt::Key_Escape) { close(); return; }
  QtHideAndShowDialog::keyPressEvent(e);
}



std::string ribi::QtSitemapGeneratorMainDialog::GetCurrentFolder(const std::string& s)
{
  return ribi::fileio::FileIo().GetPath(s);
}

std::string ribi::QtSitemapGeneratorMainDialog::GetCurrentFolder()
{
  QString s = QApplication::applicationDirPath();
  return s.toStdString();
}



void ribi::QtSitemapGeneratorMainDialog::on_button_start_clicked()
{
  std::vector<std::string> args;
  args.push_back("--page");
  args.push_back(ui->edit_website->text().toStdString());
  args.push_back("--exe");
  args.push_back(GetCurrentFolder());

  ui->text_output->clear();

  SitemapGeneratorMenuDialog d;
  d.m_signal_log.connect(
    boost::bind(&ribi::QtSitemapGeneratorMainDialog::OnLogMessage,this,boost::lambda::_1)
  );
  const int result = d.Execute(args);
  const std::string text {
    "SitemapGeneratorMenuDialog returned with error code "
    + boost::lexical_cast<std::string>(result)
  };
  ui->text_output->appendPlainText(text.c_str());
}

void ribi::QtSitemapGeneratorMainDialog::OnLogMessage(const std::string& msg) noexcept
{
  ui->text_output->appendPlainText(msg.c_str());
}

#ifndef NDEBUG
void ribi::QtSitemapGeneratorMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    SitemapGeneratorMenuDialog();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
