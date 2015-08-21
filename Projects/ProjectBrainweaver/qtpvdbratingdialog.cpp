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
#include "qtpvdbratingdialog.h"

#include <cassert>

#include <boost/lexical_cast.hpp>

#include <QKeyEvent>
#include <QFileDialog>
#include <QDesktopWidget>
#include <QPainter>
#include <QPrinter>

#include "conceptmap.h"
#include "qtconceptmap.h"
#include "qtpvdbprintratingdialog.h"
#include "qtconceptmap.h"
#include "qtpvdbdisplay.h"
#include "qtpvdbfiledialog.h"
#include "qtconceptmapdisplaystrategy.h"
#include "pvdbfile.h"
#include "trace.h"
#include "ui_qtpvdbratingdialog.h"
#pragma GCC diagnostic pop

ribi::pvdb::QtPvdbRatingDialog::QtPvdbRatingDialog(
  const boost::shared_ptr<pvdb::File> file,
  QWidget* parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtPvdbRatingDialog),
    m_back_to_menu(false),
    m_file(file)
{
  ui->setupUi(this);
  assert(file);
  assert(file->GetConceptMap());
  //Student name
  {
    const std::string s = "Naam student: " + file->GetStudentName();
    ui->label_student_name->setText(s.c_str());
  }
  //Assessor name
  {
    ui->label_assessor_name->setText("Naam assessor: ");
    if (!file->GetAssessorName().empty())
    {
      ui->edit_name->setText(file->GetAssessorName().c_str());
      //ui->edit_name->setReadOnly(true); //TVDB request
      ui->button_print->setEnabled(true);
    }
    else
    {
      ui->button_print->setEnabled(false);
    }
  }

  pvdb::QtDisplay::DisplayRatedConcepts(file,ui->table_concepts);
  pvdb::QtDisplay::DisplayExamples(file,ui->table_examples);
  pvdb::QtDisplay::DisplayValues(file,ui->table_values);

  //Center the dialog
  {
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(screen.adjusted(64,64,-64,-64));
    this->move( screen.center() - this->rect().center() );
  }
}

ribi::pvdb::QtPvdbRatingDialog::~QtPvdbRatingDialog() noexcept
{
  delete ui;
}

void ribi::pvdb::QtPvdbRatingDialog::keyPressEvent(QKeyEvent* e)
{
  if (e->key() == Qt::Key_Escape) { close(); }
}

void ribi::pvdb::QtPvdbRatingDialog::on_button_save_clicked()
{
  //Temporarily disable to widget, otherwise saving cannot succeed
  this->hide();

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
  this->m_back_to_menu = true;
  close();
}

void ribi::pvdb::QtPvdbRatingDialog::Save(const std::string& filename) const
{
  assert(filename.size() > 3
    && filename.substr( filename.size() - 3, 3 ) == pvdb::File::GetFilenameExtension()
    && "File must have correct file extension name");

  m_file->Save(filename);
  //{ const std::string debug_str = "File saved as " + filename; TRACE(debug_str); }
}



void ribi::pvdb::QtPvdbRatingDialog::on_button_print_clicked()
{
  QtPvdbPrintRatingDialog d(this->m_file);

  //Center the dialog
  {
    const QRect screen = QApplication::desktop()->screenGeometry();
    d.setGeometry(screen.adjusted(64,64,-64,-64));
    d.move( screen.center() - d.rect().center() );
  }

  this->ShowChild(&d);
}

void ribi::pvdb::QtPvdbRatingDialog::on_edit_name_textEdited(const QString &arg1)
{
  if (arg1.size() > 1)
  {
    m_file->SetAssessorName(arg1.toStdString());
    ui->button_print->setEnabled(true);
  }
  else
  {
    ui->button_print->setEnabled(false);
  }
}
