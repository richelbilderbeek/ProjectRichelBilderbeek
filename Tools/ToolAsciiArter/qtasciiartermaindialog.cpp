//---------------------------------------------------------------------------
/*
AsciiArter, tool to create ASCII art
Copyright (C) 2006-2013 Richel Bilderbeek

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

#include "asciiarter.h"
#include "asciiartermaindialog.h"
#include "fileio.h"
#include "qtaboutdialog.h"
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
  if (!fileio::IsRegularFile(GetFilename()))
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

  if (!fileio::IsRegularFile(filename))
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

void ribi::QtAsciiArterMainDialog::on_edit_width_textChanged(QString)
{
  OnAnyChange();

}

