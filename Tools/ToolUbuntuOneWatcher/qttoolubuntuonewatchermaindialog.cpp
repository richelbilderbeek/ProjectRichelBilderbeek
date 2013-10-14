//---------------------------------------------------------------------------
/*
UbuntuOneWatcher, tool to see what Ubuntu One is doing
Copyright (C) 2010 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolUbuntuOneWatcher.htm
//---------------------------------------------------------------------------
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"

#include <boost/foreach.hpp>

#include <QDesktopWidget>
#include <QFile>

#include "fileio.h"
#include "qtaboutdialog.h"
#include "qttoolubuntuonewatchermaindialog.h"
#include "ui_qttoolubuntuonewatchermaindialog.h"

#pragma GCC diagnostic pop

ribi::QtUbuntuOneWatcherMainDialog::QtUbuntuOneWatcherMainDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtUbuntuOneWatcherMainDialog)
{
  ui->setupUi(this);
  QObject::connect(ui->button_find_out,&QPushButton::clicked,
    this,&ribi::QtUbuntuOneWatcherMainDialog::OnFindOut);

  //Put the dialog in the screen center
  const QRect screen = QApplication::desktop()->screenGeometry();
  this->setGeometry(0,0,screen.width() * 3 / 4, screen.height() * 3 / 4);
  this->move( screen.center() - this->rect().center() );
}

ribi::QtUbuntuOneWatcherMainDialog::~QtUbuntuOneWatcherMainDialog() noexcept
{
  delete ui;
}

void ribi::QtUbuntuOneWatcherMainDialog::OnFindOut()
{
  ui->text->clear();
  //List the current state
  {
    std::system("u1sdtool -s > tmp.txt");
    ui->text->appendHtml("Ubuntu One current state:");
    const std::vector<std::string> v = ribi::fileio::FileToVector("tmp.txt");
    BOOST_FOREACH(const std::string& s,v)
    {
      ui->text->appendHtml(s.c_str());
    }
  }
  //List the current transfers
  {
    std::system("u1sdtool --current-transfers > tmp.txt");
    ui->text->appendHtml("List of current transfers:");
    const std::vector<std::string> v = ribi::fileio::FileToVector("tmp.txt");
    BOOST_FOREACH(const std::string& s,v)
    {
      ui->text->appendHtml(s.c_str());
    }
  }
  //List the synched folders
  {
    std::system("u1sdtool --list-folders > tmp.txt");
    ui->text->appendHtml("List of synchronized folders:");
    const std::vector<std::string> v = ribi::fileio::FileToVector("tmp.txt");
    BOOST_FOREACH(const std::string& s,v)
    {
      ui->text->appendHtml(s.c_str());
    }
  }

  //List the synched folders
  {
    std::system("u1sdtool --waiting-content > tmp.txt");
    ui->text->appendHtml("List of content waiting to be synchronized:");
    const std::vector<std::string> v = ribi::fileio::FileToVector("tmp.txt");
    BOOST_FOREACH(const std::string& s,v)
    {
      ui->text->appendHtml(s.c_str());
    }
  }
}
