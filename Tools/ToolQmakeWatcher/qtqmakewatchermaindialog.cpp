//---------------------------------------------------------------------------
/*
QmakeWatcher, tool to watch qmake's .pro to Makefile conversion
Copyright (C) 2010-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolQmakeWatcher.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtqmakewatchermaindialog.h"

#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include <QDesktopWidget>
#include <QFile>

#include "fileio.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qtqmakewatchermaindialog.h"
#pragma GCC diagnostic pop

ribi::QtQmakeWatcherMainDialog::QtQmakeWatcherMainDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtQmakeWatcherMainDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
  ui->edit_pro->setWordWrapMode(QTextOption::NoWrap);
  ui->edit_makefile->setWordWrapMode(QTextOption::NoWrap);
  ui->edit_diff->setWordWrapMode(QTextOption::NoWrap);

  QObject::connect(ui->button_qmake,&QPushButton::clicked,
    this,&ribi::QtQmakeWatcherMainDialog::OnQmake
  );



  //Put the dialog in the screen center
  const QRect screen = QApplication::desktop()->screenGeometry();
  this->setGeometry(0,0,screen.width() * 8 / 10,screen.height() * 8 / 10);
  this->move( screen.center() - this->rect().center() );
}

ribi::QtQmakeWatcherMainDialog::~QtQmakeWatcherMainDialog() noexcept
{
  delete ui;
}

void ribi::QtQmakeWatcherMainDialog::OnQmake() noexcept
{
  //Save text to file
  {
    const std::string s = ui->edit_pro->document()->toPlainText().toStdString();
    std::ofstream f("tmp.pro");
    f << s << '\n';
  }
  //Execute commands
  {
    const bool has_error = std::system("cp Makefile oldmake");
    assert(!has_error);
    if (has_error) throw std::runtime_error("'cp Makefile oldmake' failed");
  }
  {
    const bool has_error = std::system("qmake tmp.pro");
    assert(!has_error);
    if (has_error) throw std::runtime_error("'qmake tmp.pro' failed");
  }
  {
    const bool has_error = std::system("diff Makefile oldmake > tmp.txt");
    assert(!has_error);
    if (has_error) throw std::runtime_error("'diff Makefile oldmake > tmp.txt' failed");
  }
  //Display Makefile
  {
    ui->edit_makefile->clear();
    const std::vector<std::string> v(ribi::fileio::FileIo().FileToVector("Makefile"));
    for(const std::string& s: v)
    {
      ui->edit_makefile->appendPlainText(QString(s.c_str()));
    }
  }
  //Display diff
  {
    ui->edit_diff->clear();
    const std::vector<std::string> v(ribi::fileio::FileIo().FileToVector("tmp.txt"));
    for(const std::string& s: v)
    {
      std::string t = s;
      if (!s.empty() && s[0] == '>')
      {
        //Old
        t = "<font color=#0000FF>&lt;"
          + s.substr(1,s.size()-1)
          + "</font>";
      }
      if (!s.empty() && s[0] == '<')
      {
        //New
        t = "<b><font color=#FF0000>&gt;"
          + s.substr(1,s.size()-1)
          + "</font></b>";
      }
      ui->edit_diff->appendHtml(QString(t.c_str()));
    }
  }
}

#ifndef NDEBUG
void ribi::QtQmakeWatcherMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
