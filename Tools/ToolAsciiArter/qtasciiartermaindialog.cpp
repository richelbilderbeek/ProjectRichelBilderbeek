//---------------------------------------------------------------------------
/*
AsciiArter, tool to create ASCII art
Copyright (C) 2006-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolAsciiArter.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtasciiartermaindialog.h"

//
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <QDesktopWidget>
#include <QFileDialog>
#include <QKeyEvent>
//#include <QImage>
#include <QPixmap>

#include "asciiartermaindialog.h"
#include "fileio.h"
#include "testtimer.h"
#include "qtaboutdialog.h"
#include "trace.h"
#include "ui_qtasciiartermaindialog.h"
#pragma GCC diagnostic pop

ribi::QtAsciiArterMainDialog::QtAsciiArterMainDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtAsciiArterMainDialog),
    m_dialog(new AsciiArterMainDialog("",80)),
    m_filename{}
{
  ui->setupUi(this);

  //Put the dialog in the screen center
  const QRect screen = QApplication::desktop()->screenGeometry();
  this->move( screen.center() - this->rect().center() );
}

ribi::QtAsciiArterMainDialog::~QtAsciiArterMainDialog() noexcept
{
  delete ui;
}

int ribi::QtAsciiArterMainDialog::GetWidth() const noexcept
{
  return ui->box_width->value();
}

void ribi::QtAsciiArterMainDialog::OnAnyChange()
{
  if (!fileio::FileIo().IsRegularFile(GetFilename()))
  {
    m_dialog.reset(nullptr);
    return;
  }

  m_dialog.reset(new AsciiArterMainDialog(GetFilename(),GetWidth()));
  const std::vector<std::string>& v = m_dialog->GetAsciiArt();
  ui->text->clear();

  for(const std::string& s: v)
  {
    ui->text->appendPlainText(s.c_str());
  }
}

void ribi::QtAsciiArterMainDialog::on_button_load_clicked()
{
  const std::string filename = QFileDialog::getOpenFileName().toStdString();

  if (!fileio::FileIo().IsRegularFile(filename))
  {
    m_filename = "";
    return;
  }
  m_filename = filename;
  OnAnyChange();
}

void ribi::QtAsciiArterMainDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) close();
}

#ifndef NDEBUG
void ribi::QtAsciiArterMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  const std::string tmp_filename { fileio::FileIo().GetTempFileName() };
  assert(!fileio::FileIo().IsRegularFile(tmp_filename));
  //Load image from resources, save to file
  {
    QPixmap p(":/ToolImageAsciiArter/images/R.png");
    assert(p.width() > 0);
    assert(p.height() > 0);
    p.save(tmp_filename.c_str());
  }
  assert(fileio::FileIo().IsRegularFile(tmp_filename));
  boost::scoped_ptr<AsciiArterMainDialog> dialog(
    new AsciiArterMainDialog(tmp_filename,40)
  );
  assert(dialog);
  const std::vector<std::string> v {
    dialog->GetAsciiArt()
  };
  assert(!v.empty());
  fileio::FileIo().DeleteFile(tmp_filename);
  assert(!fileio::FileIo().IsRegularFile(tmp_filename));
}
#endif

void ribi::QtAsciiArterMainDialog::on_box_width_valueChanged(int)
{
  OnAnyChange();
}
