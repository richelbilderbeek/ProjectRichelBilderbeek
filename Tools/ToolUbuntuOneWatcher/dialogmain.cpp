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
//---------------------------------------------------------------------------
#include <boost/foreach.hpp>
//---------------------------------------------------------------------------
#include <QDesktopWidget>
#include <QFile>
//---------------------------------------------------------------------------
#include "dialogabout.h"
#include "dialogmain.h"
#include "ui_dialogmain.h"
//---------------------------------------------------------------------------
DialogMain::DialogMain(QWidget *parent) :
    QDialog(parent, Qt::Window),
    ui(new Ui::DialogMain)
{
  ui->setupUi(this);
  QObject::connect(ui->button_about,SIGNAL(clicked()),
    this,SLOT(OnAbout()));
  QObject::connect(ui->button_find_out,SIGNAL(clicked()),
    this,SLOT(OnFindOut()));

  //Put the dialog in the screen center
  const QRect screen = QApplication::desktop()->screenGeometry();
  this->setGeometry(0,0,screen.width() * 3 / 4, screen.height() * 3 / 4);
  this->move( screen.center() - this->rect().center() );
}
//---------------------------------------------------------------------------
DialogMain::~DialogMain()
{
  delete ui;
}
//---------------------------------------------------------------------------
void DialogMain::changeEvent(QEvent *e)
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
//---------------------------------------------------------------------------
void DialogMain::OnAbout()
{
  DialogAbout d;
  hide();
  d.exec();
  show();
}
//---------------------------------------------------------------------------
void DialogMain::OnFindOut()
{
  ui->text->clear();
  //List the current state
  {
    std::system("u1sdtool -s > tmp.txt");
    ui->text->appendHtml("Ubuntu One current state:");
    const std::vector<std::string> v = FileToVector("tmp.txt");
    BOOST_FOREACH(const std::string& s,v)
    {
      ui->text->appendHtml(s.c_str());
    }
  }
  //List the current transfers
  {
    std::system("u1sdtool --current-transfers > tmp.txt");
    ui->text->appendHtml("List of current transfers:");
    const std::vector<std::string> v = FileToVector("tmp.txt");
    BOOST_FOREACH(const std::string& s,v)
    {
      ui->text->appendHtml(s.c_str());
    }
  }
  //List the synched folders
  {
    std::system("u1sdtool --list-folders > tmp.txt");
    ui->text->appendHtml("List of synchronized folders:");
    const std::vector<std::string> v = FileToVector("tmp.txt");
    BOOST_FOREACH(const std::string& s,v)
    {
      ui->text->appendHtml(s.c_str());
    }
  }

  //List the synched folders
  {
    std::system("u1sdtool --waiting-content > tmp.txt");
    ui->text->appendHtml("List of content waiting to be synchronized:");
    const std::vector<std::string> v = FileToVector("tmp.txt");
    BOOST_FOREACH(const std::string& s,v)
    {
      ui->text->appendHtml(s.c_str());
    }
  }




}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppFileToVector.htm
const std::vector<std::string> FileToVector(const std::string& fileName)
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
//---------------------------------------------------------------------------
