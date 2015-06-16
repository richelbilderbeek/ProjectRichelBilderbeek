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
#include "qtpvdbcreateassessmentcompletedialog.h"

#include <QKeyEvent>
#include <QFileDialog>
#include "conceptmap.h"
#include "pvdbfile.h"
#include "conceptmapfactory.h"
#include "qtpvdbfiledialog.h"

#include "ui_qtpvdbcreateassessmentcompletedialog.h"

#include "trace.h"
#pragma GCC diagnostic pop

ribi::pvdb::QtPvdbCreateAssessmentCompleteDialog::QtPvdbCreateAssessmentCompleteDialog(QWidget* parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtPvdbCreateAssessmentCompleteDialog),
    m_back_to_menu(false)
{
  ui->setupUi(this);
}

ribi::pvdb::QtPvdbCreateAssessmentCompleteDialog::~QtPvdbCreateAssessmentCompleteDialog() noexcept
{
  delete ui;
}

std::string ribi::pvdb::QtPvdbCreateAssessmentCompleteDialog::GetQuestion() const noexcept
{
  return ui->edit->text().toStdString();
}

void ribi::pvdb::QtPvdbCreateAssessmentCompleteDialog::keyPressEvent(QKeyEvent* e)
{
  if (e->key()  == Qt::Key_Escape) close();
}

void ribi::pvdb::QtPvdbCreateAssessmentCompleteDialog::on_button_save_clicked()
{
  const auto d = pvdb::QtFileDialog::GetSaveFileDialog(pvdb::QtFileDialog::FileType::cmp);
  d->setWindowTitle("Sla het assessment invoer-bestand op");
  const int status = d->exec();
  if (status == QDialog::Rejected)
  {
    this->show();
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

  m_back_to_menu = true;
  close();
}

void ribi::pvdb::QtPvdbCreateAssessmentCompleteDialog::Save(const std::string& filename) const
{
  assert(filename.size() > 3
    && filename.substr( filename.size() - 3, 3 ) == pvdb::File::GetFilenameExtension()
    && "File must have correct file extension name");
  const std::string question = ui->edit->text().toStdString();
  const boost::shared_ptr<pvdb::File> file(new pvdb::File);
  file->SetQuestion(question);
  assert(file->GetQuestion() == question);
  file->Save(filename);
}

void ribi::pvdb::QtPvdbCreateAssessmentCompleteDialog::SetQuestion(const std::string& question)
{
  ui->edit->setText(question.c_str());
}

void ribi::pvdb::QtPvdbCreateAssessmentCompleteDialog::on_edit_textChanged(const QString &arg1)
{
  assert(ui->edit->text() == arg1);
  ui->button_save->setEnabled(!arg1.isEmpty());

}
