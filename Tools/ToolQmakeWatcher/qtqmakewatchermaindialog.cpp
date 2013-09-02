//---------------------------------------------------------------------------
/*
QmakeWatcher, tool to watch qmake's .pro to Makefile conversion
Copyright (C) 2010-2013 Richel Bilderbeek

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
//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtqmakewatchermaindialog.h"

#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/foreach.hpp>
#pragma GCC diagnostic pop

#include <QDesktopWidget>
#include <QFile>

#include "ui_qtqmakewatchermaindialog.h"

QtQmakeWatcherMainDialog::QtQmakeWatcherMainDialog(QWidget *parent) :
    QDialog(parent, Qt::Window),
    ui(new Ui::QtQmakeWatcherMainDialog)
{
  ui->setupUi(this);
  ui->edit_pro->setWordWrapMode(QTextOption::NoWrap);
  ui->edit_makefile->setWordWrapMode(QTextOption::NoWrap);
  ui->edit_diff->setWordWrapMode(QTextOption::NoWrap);

  QObject::connect(ui->button_qmake,SIGNAL(clicked()),
    this,SLOT(OnQmake()));



  //Put the dialog in the screen center
  const QRect screen = QApplication::desktop()->screenGeometry();
  this->setGeometry(0,0,screen.width() * 8 / 10,screen.height() * 8 / 10);
  this->move( screen.center() - this->rect().center() );
}

QtQmakeWatcherMainDialog::~QtQmakeWatcherMainDialog()
{
  delete ui;
}

void QtQmakeWatcherMainDialog::changeEvent(QEvent *e)
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

const std::vector<std::string> QtQmakeWatcherMainDialog::FileToVector(const std::string& fileName)
{

  assert(QFile::exists(fileName.c_str()));
  std::vector<std::string> myVector;
  std::ifstream in(fileName.c_str());
  std::string myString;
  for (int i=0; !in.eof(); ++i)
  {
    std::getline(in,myString);
    myVector.push_back(myString);
  }
  return myVector;
}


void QtQmakeWatcherMainDialog::OnQmake()
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
    const std::vector<std::string> v(FileToVector("Makefile"));
    BOOST_FOREACH(const std::string& s, v)
    {
      ui->edit_makefile->appendPlainText(QString(s.c_str()));
    }
  }
  //Display diff
  {
    ui->edit_diff->clear();
    const std::vector<std::string> v(FileToVector("tmp.txt"));
    BOOST_FOREACH(const std::string& s, v)
    {
      std::string t = s;
      if (!s.empty() && s[0] == '>')
      {
        //Old
        t = std::string("<font color=#0000FF>&lt;")
          + s.substr(1,s.size()-1)
          + std::string("</font>");
      }
      if (!s.empty() && s[0] == '<')
      {
        //New
        t = std::string("<b><font color=#FF0000>&gt;")
          + s.substr(1,s.size()-1)
          + std::string("</font></b>");
      }
      ui->edit_diff->appendHtml(QString(t.c_str()));
    }
  }
}
