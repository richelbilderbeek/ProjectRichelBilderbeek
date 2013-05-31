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
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtrichelbilderbeekgallerymenudialog.h"

#include <fstream>
#include <boost/filesystem.hpp>
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

QtRichelBilderbeekGalleryMenuDialog::QtRichelBilderbeekGalleryMenuDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtRichelBilderbeekGalleryMenuDialog)
{
  #ifndef NDEBUG
  RichelBilderbeek::GalleryMenuDialog::Test();
  #endif
  ui->setupUi(this);
}

QtRichelBilderbeekGalleryMenuDialog::~QtRichelBilderbeekGalleryMenuDialog()
{
  delete ui;
}

void QtRichelBilderbeekGalleryMenuDialog::keyPressEvent(QKeyEvent* e)
{
  if (e->key()  == Qt::Key_Escape) close();
}

void QtRichelBilderbeekGalleryMenuDialog::on_button_about_clicked()
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

void QtRichelBilderbeekGalleryMenuDialog::on_button_quit_clicked()
{
  close();
}

void QtRichelBilderbeekGalleryMenuDialog::on_button_start_clicked()
{
  QtRichelBilderbeekGalleryDialog d;
  ShowChild(&d);
}



void QtRichelBilderbeekGalleryMenuDialog::on_button_create_html_clicked()
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
  const std::string s = boost::filesystem::path( qApp->argv()[0]).parent_path().string();
  box.setWindowTitle( this->windowTitle() );
  box.setText( (std::string("HTML pages have been created in folder ") + s).c_str());
  box.exec();
}
