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
#include "qtpvdbstudentmenudialog.h"

#include <cassert>

#include <QKeyEvent>
#include <QFileDialog>

#include "pvdbfile.h"
#include "qtpvdbaboutdialog.h"
#include "qtpvdbfiledialog.h"
#include "qtpvdbstudentstartcompletedialog.h"
#include "trace.h"
#include "ui_qtpvdbstudentmenudialog.h"
#pragma GCC diagnostic pop

ribi::pvdb::QtPvdbStudentMenuDialog::QtPvdbStudentMenuDialog(const boost::shared_ptr<pvdb::File> file, QWidget* parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtPvdbStudentMenuDialog),
    m_file(file)
{
  ui->setupUi(this);
  assert(m_file);
  if (!m_file->GetStudentName().empty())
  {
    SetName(m_file->GetStudentName());
  }
  on_edit_name_textChanged(ui->edit_name->text());
}

ribi::pvdb::QtPvdbStudentMenuDialog::~QtPvdbStudentMenuDialog() noexcept
{
  delete ui;
}

std::string ribi::pvdb::QtPvdbStudentMenuDialog::GetName() const noexcept
{
  return ui->edit_name->text().toStdString();
}

void ribi::pvdb::QtPvdbStudentMenuDialog::keyPressEvent(QKeyEvent* e)
{
  if (e->key()  == Qt::Key_Escape) { close(); return; }
  if ((e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_S) { on_button_save_clicked(); return; }
  QDialog::keyPressEvent(e);
}

void ribi::pvdb::QtPvdbStudentMenuDialog::on_button_about_clicked()
{
  const auto d(QtPvdbAboutDialog::Get());
  this->hide();
  d->exec();
  this->show();
}

void ribi::pvdb::QtPvdbStudentMenuDialog::on_button_quit_clicked()
{
  close();
}

void ribi::pvdb::QtPvdbStudentMenuDialog::on_button_start_clicked()
{
  m_file->SetStudentName(ui->edit_name->text().toStdString());
  QtPvdbStudentStartCompleteDialog d(m_file);
  this->ShowChild(&d);
}

void ribi::pvdb::QtPvdbStudentMenuDialog::on_edit_name_textChanged(const QString &arg1)
{
  //Enable start button when student has entered at least two characters
  assert(ui->edit_name->text() == arg1);
  if (arg1.size() > 1)
  {
    ui->button_start->setEnabled(true);
  }
  else
  {
    ui->button_start->setEnabled(false);
  }
}

void ribi::pvdb::QtPvdbStudentMenuDialog::on_button_save_clicked()
{
  const auto d = pvdb::QtFileDialog::GetSaveFileDialog(pvdb::QtFileDialog::FileType::cmp);
  d->setWindowTitle("Sla de concept map op");
  const int status = d->exec();
  if (status == QDialog::Rejected)
  {
    return;
  }
  assert(d->selectedFiles().size() == 1);
  const std::string filename_raw = d->selectedFiles()[0].toStdString();
  assert(!filename_raw.empty());

  const std::string filename
    =  (filename_raw.size() < pvdb::File::GetFilenameExtension().size()
      || filename_raw.substr( filename_raw.size() - 3, 3 ) != pvdb::File::GetFilenameExtension()
     ? filename_raw + "." + pvdb::File::GetFilenameExtension()
     : filename_raw);
  assert(filename.size() > 3
    && filename.substr( filename.size() - 3, 3 ) == pvdb::File::GetFilenameExtension()
    && "File must have correct file extension name");
  Save(filename);
}

void ribi::pvdb::QtPvdbStudentMenuDialog::Save(const std::string& filename) const
{
  m_file->SetStudentName(ui->edit_name->text().toStdString());

  assert(filename.size() > 3
    && filename.substr( filename.size() - 3, 3 ) == pvdb::File::GetFilenameExtension()
    && "File must have correct file extension name");
  m_file->Save(filename);
  //{ const std::string debug_str = "File saved as " + filename; TRACE(debug_str); }
}

void ribi::pvdb::QtPvdbStudentMenuDialog::SetName(const std::string& name)
{
  ui->edit_name->setText(name.c_str());
}
