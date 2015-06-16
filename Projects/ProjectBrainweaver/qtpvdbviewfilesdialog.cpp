//---------------------------------------------------------------------------
/*
Brainweaver, tool to create and assess concept maps
Copyright (C) 2012-2015 The Brainweaver Team

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
//From http://www.richelbilderbeek.nl/ProjectBrainweaver.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtpvdbviewfilesdialog.h"

#include <cassert>
#include <iterator>
#include <QFileDialog>
#include <QKeyEvent>
#include "fileio.h"
#include "pvdbhelper.h"
#include "qtpvdbfiledialog.h"
#include "ui_qtpvdbviewfilesdialog.h"
#pragma GCC diagnostic pop

ribi::pvdb::QtPvdbViewFilesDialog::QtPvdbViewFilesDialog(QWidget* parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtPvdbViewFilesDialog)
{
  ui->setupUi(this);
}

ribi::pvdb::QtPvdbViewFilesDialog::~QtPvdbViewFilesDialog() noexcept
{
  delete ui;
}

void ribi::pvdb::QtPvdbViewFilesDialog::OnTimerLeft()
{
}

void ribi::pvdb::QtPvdbViewFilesDialog::OnTimerRight()
{

}

void ribi::pvdb::QtPvdbViewFilesDialog::on_button_left_clicked()
{
  const auto d = pvdb::QtFileDialog::GetOpenFileDialog();
  d->setWindowTitle("Select a file to view");
  const int status = d->exec();
  if (status == QDialog::Rejected) return;
  const auto filenames = d->selectedFiles();
  if (filenames.isEmpty()) return;
  assert(filenames.size() == 1);
  const std::string filename = filenames[0].toStdString();
  assert(fileio::FileIo().IsRegularFile(filename));
  assert(!pvdb::SafeFileToVector(filename).empty());

  const std::vector<std::string> v = pvdb::XmlToPretty(pvdb::SafeFileToVector(filename)[0]);
  std::string text;
  std::for_each(v.begin(),v.end(),
    [&text](std::string s)
    {
      text+=s;
      text+="\n";
    }
  );
  ui->text_left->clear();
  ui->text_left->setPlainText(text.c_str());
}

void ribi::pvdb::QtPvdbViewFilesDialog::keyPressEvent(QKeyEvent* event)
{
  if (event->key()  == Qt::Key_Escape) { close(); return; }
  QDialog::keyPressEvent(event);
}

void ribi::pvdb::QtPvdbViewFilesDialog::on_button_right_clicked()
{
  const auto d = pvdb::QtFileDialog::GetOpenFileDialog();
  d->setWindowTitle("Select a file to view");
  const int status = d->exec();
  if (status == QDialog::Rejected) return;
  const auto filenames = d->selectedFiles();
  if (filenames.isEmpty()) return;
  assert(filenames.size() == 1);
  const std::string filename = filenames[0].toStdString();
  assert(fileio::FileIo().IsRegularFile(filename));
  assert(!ribi::fileio::FileIo().FileToVector(filename).empty());
  const std::vector<std::string> v = pvdb::XmlToPretty(ribi::fileio::FileIo().FileToVector(filename)[0]);
  std::string text;
  std::for_each(v.begin(),v.end(),
    [&text](std::string s)
    {
      text+=s;
      text+="\n";
    }
  );

  ui->text_right->clear();
  ui->text_right->setPlainText(text.c_str());
}
