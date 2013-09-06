//---------------------------------------------------------------------------
/*
RichelBilderbeekGallery, gallery of Richel Bilderbeek's work
Copyright (C) 2012 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolRichelBilderbeekGallery.htm
//---------------------------------------------------------------------------


#include "qtrichelbilderbeekgallerymenudialog.h"

#include <fstream>

#include <QApplication>
#include <QKeyEvent>
#include <QMessageBox>

#include "about.h"
#include "qtaboutdialog.h"
#include "qtrichelbilderbeekgallerydialog.h"
//#include "qtrichelbilderbeekgalleryresources.h"
#include "richelbilderbeekgallerymenudialog.h"
#include "ui_qtrichelbilderbeekgallerymenudialog.h"

#include <QBitmap>
#include <QPainter>
#include <QPixmap>

ribi::QtRichelBilderbeekGalleryMenuDialog::QtRichelBilderbeekGalleryMenuDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtRichelBilderbeekGalleryMenuDialog)
{
  #ifndef NDEBUG
  RichelBilderbeek::GalleryMenuDialog::Test();
  #endif
  ui->setupUi(this);
}

ribi::QtRichelBilderbeekGalleryMenuDialog::~QtRichelBilderbeekGalleryMenuDialog()
{
  delete ui;
}


const std::string ribi::QtRichelBilderbeekGalleryMenuDialog::GetPath(const std::string& filename)
{
  const int a = filename.rfind("\\",filename.size());
  const int b = filename.rfind("/",filename.size());
  const int i = std::max(a,b);
  assert(i < static_cast<int>(filename.size()));
  return filename.substr(0,i);
}

void ribi::QtRichelBilderbeekGalleryMenuDialog::keyPressEvent(QKeyEvent* e)
{
  if (e->key()  == Qt::Key_Escape) close();
}

void ribi::QtRichelBilderbeekGalleryMenuDialog::on_button_about_clicked()
{
  this->hide();
  About a = RichelBilderbeek::GalleryMenuDialog::GetAbout();
  a.AddLibrary("QtRichelBilderbeekGalleryDialog version: " + QtRichelBilderbeekGalleryDialog::GetVersion());
  //a.AddLibrary("QtRichelBilderbeekResources version: " + RichelBilderbeek::QtResources::GetVersion());
  QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  d.exec();
  this->show();
}

void ribi::QtRichelBilderbeekGalleryMenuDialog::on_button_quit_clicked()
{
  close();
}

void ribi::QtRichelBilderbeekGalleryMenuDialog::on_button_start_clicked()
{
  QtRichelBilderbeekGalleryDialog d;
  ShowChild(&d);
}



void ribi::QtRichelBilderbeekGalleryMenuDialog::on_button_create_html_clicked()
{
  {
    const std::vector<std::string> v = RichelBilderbeek::GalleryMenuDialog::CreateHtmlClassGallery();
    std::ofstream f("CppClassGallery.htm");
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(f,"\n"));
  }
  {
    const std::vector<std::string> v = RichelBilderbeek::GalleryMenuDialog::CreateHtmlGameGallery();
    std::ofstream f("GameGallery.htm");
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(f,"\n"));
  }
  {
    const std::vector<std::string> v = RichelBilderbeek::GalleryMenuDialog::CreateHtmlProjectGallery();
    std::ofstream f("ProjectGallery.htm");
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(f,"\n"));
  }
  {
    const std::vector<std::string> v = RichelBilderbeek::GalleryMenuDialog::CreateHtmlToolGallery();
    std::ofstream f("ToolGallery.htm");
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(f,"\n"));
  }
  {
    const std::vector<std::string> v = RichelBilderbeek::GalleryMenuDialog::CreateHtmlStatus();
    std::ofstream f("CppRichelBilderbeekStatus.htm");
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(f,"\n"));
  }
  QMessageBox box;
  box.setWindowIcon(this->windowIcon());
  box.setStyleSheet(this->styleSheet());
  const std::string s = GetPath( qApp->arguments()[0].toStdString() );
  box.setWindowTitle( this->windowTitle() );
  box.setText( (std::string("HTML pages have been created in folder ") + s).c_str());
  box.exec();
}
