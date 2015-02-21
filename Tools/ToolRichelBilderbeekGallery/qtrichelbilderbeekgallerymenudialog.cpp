//---------------------------------------------------------------------------
/*
RichelBilderbeekGallery, gallery of Richel Bilderbeek's work
Copyright (C) 2012-2015 Richel Bilderbeek

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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtrichelbilderbeekgallerymenudialog.h"

#include <cassert>
#include <fstream>

#include <QApplication>
#include <QKeyEvent>
#include <QMessageBox>
#include <QBitmap>
#include <QPainter>
#include <QPixmap>

#include "about.h"
#include "fileio.h"
#include "qtaboutdialog.h"
#include "qtrichelbilderbeekgallerymenudialog.h"
#include "qtrichelbilderbeekgallerydialog.h"
#include "testtimer.h"
#include "richelbilderbeekgallerymenudialog.h"
#include "trace.h"
#include "ui_qtrichelbilderbeekgallerymenudialog.h"

#pragma GCC diagnostic pop

ribi::QtRichelBilderbeekGalleryMenuDialog::QtRichelBilderbeekGalleryMenuDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtRichelBilderbeekGalleryMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtRichelBilderbeekGalleryMenuDialog::~QtRichelBilderbeekGalleryMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtRichelBilderbeekGalleryMenuDialog::keyPressEvent(QKeyEvent* e)
{
  if (e->key()  == Qt::Key_Escape) close();
}

void ribi::QtRichelBilderbeekGalleryMenuDialog::on_button_about_clicked()
{
  this->hide();
  About a = GalleryMenuDialog().GetAbout();
  a.AddLibrary("QtRichelBilderbeekGalleryDialog version: "
    + QtRichelBilderbeekGalleryMenuDialog::GetVersion());
  //a.AddLibrary("QtRichelBilderbeekResources version: " + QtResources::GetVersion());
  QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
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
    const std::vector<std::string> v = GalleryMenuDialog().CreateMarkdownClassGallery();
    std::ofstream f("CppClassGallery.md");
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(f,"\n"));
  }

  {
    const std::vector<std::string> v = GalleryMenuDialog().CreateMarkdownGameGallery();
    std::ofstream f("GameGallery.md");
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(f,"\n"));
  }
  {
    const std::vector<std::string> v = GalleryMenuDialog().CreateMarkdownProjectGallery();
    std::ofstream f("ProjectGallery.md");
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(f,"\n"));
  }
  {
    const std::vector<std::string> v = GalleryMenuDialog().CreateMarkdownToolGallery();
    std::ofstream f("ToolGallery.md");
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(f,"\n"));
  }
  {
    const std::vector<std::string> v = GalleryMenuDialog().CreateHtmlClassGallery();
    std::ofstream f("CppClassGallery.htm");
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(f,"\n"));
  }
  {
    const std::vector<std::string> v = GalleryMenuDialog().CreateHtmlGameGallery();
    std::ofstream f("GameGallery.htm");
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(f,"\n"));
  }
  {
    const std::vector<std::string> v = GalleryMenuDialog().CreateHtmlProjectGallery();
    std::ofstream f("ProjectGallery.htm");
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(f,"\n"));
  }
  {
    const std::vector<std::string> v = GalleryMenuDialog().CreateHtmlToolGallery();
    std::ofstream f("ToolGallery.htm");
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(f,"\n"));
  }
  {
    const std::vector<std::string> v = GalleryMenuDialog().CreateHtmlStatus();
    std::ofstream f("CppRichelBilderbeekStatus.htm");
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(f,"\n"));
  }
  this->ui->button_create_html->setText("DONE!");
  this->ui->button_create_html->setEnabled(false);
  /*
  QMessageBox box;
  box.setWindowIcon(this->windowIcon());
  box.setStyleSheet(this->styleSheet());
  const std::string s = fileio::FileIo().GetPath( qApp->arguments()[0].toStdString() );
  box.setWindowTitle( this->windowTitle() );
  box.setText( ("HTML pages have been created in folder " + s).c_str());
  box.exec();
  */
}

#ifndef NDEBUG
void ribi::QtRichelBilderbeekGalleryMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  QtRichelBilderbeekGalleryDialog();
  QtRichelBilderbeekGalleryMenuDialog().on_button_create_html_clicked();
}
#endif
