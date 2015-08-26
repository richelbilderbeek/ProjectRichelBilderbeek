//---------------------------------------------------------------------------
/*
PicToCode, tool to convert a picture to C++ code
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
//From http://www.richelbilderbeek.nl/ToolPicToCode.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtpictocodemaindialog.h"

#include <cassert>

#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <QBitmap>
#include <QDesktopWidget>
#include <QFileDialog>

#include "pictocodemaindialog.h"
#include "pictocodemenudialog.h"
#include "qtsprites.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qtpictocodemaindialog.h"
#pragma GCC diagnostic pop

ribi::p2c::QtMainDialog::QtMainDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtPicToCodeMainDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
  ui->edit_code->setWordWrapMode(QTextOption::NoWrap);
  ui->label_picture->setPixmap(QtSprites::DrawR());

  //Put the dialog in the screen center
  const QRect screen = QApplication::desktop()->screenGeometry();
  this->setGeometry(0,0,screen.width() * 8 / 10,screen.height() * 8 / 10);
  this->move( screen.center() - this->rect().center() );
}

ribi::p2c::QtMainDialog::~QtMainDialog() noexcept
{
  delete ui;
}



void ribi::p2c::QtMainDialog::on_button_select_file_clicked()
{
  QFileDialog d;
  //Select only picture files
  {
    QStringList filters;
    filters
      << "*.png" << "*.PNG"
      << "*.bmp" << "*.BMP";
    d.setNameFilters(filters);
  }
  d.setFileMode(QFileDialog::ExistingFile);
  d.exec();
  if (d.selectedFiles().size()==0) return;
  assert(d.selectedFiles().size()==1);
  const QString filename = d.selectedFiles().operator[](0);
  ui->label_picture->setPixmap(QPixmap(filename));
}

void ribi::p2c::QtMainDialog::on_button_convert_clicked()
{
  const std::vector<std::string> v
    = (ui->radio_nds->isChecked()
    ? PicToNdsCode(ui->label_picture->pixmap()->toImage())
    : PicToQtCode(ui->label_picture->pixmap()->toImage())
    );

  ui->edit_code->clear();
  for(const std::string& s: v)
  {
    ui->edit_code->appendPlainText(s.c_str());
  }

}

std::vector<std::string> ribi::p2c::QtMainDialog::PicToNdsCode(const QImage& qimage) const
{
  MainDialog d;
  d.SetInputImage(qimage);
  d.SetGraphicsLibrary(GraphicsLibrary::nds);
  std::vector<std::string> v = d.ToHeaderFile();
  v.push_back("");
  {
    const auto w = d.ToImplementationFile();
    std::copy(std::begin(w),std::end(w),std::back_inserter(v));
  }
  return v;
}

std::vector<std::string> ribi::p2c::QtMainDialog::PicToQtCode(const QImage& qimage) const
{
  MainDialog d;
  d.SetInputImage(qimage);
  d.SetGraphicsLibrary(GraphicsLibrary::qt);
  std::vector<std::string> v = d.ToHeaderFile();
  v.push_back("");
  {
    const auto w = d.ToImplementationFile();
    std::copy(std::begin(w),std::end(w),std::back_inserter(v));
  }
  return v;
}

#ifndef NDEBUG
void ribi::p2c::QtMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    MainDialog();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
