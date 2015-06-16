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
#include "qtpvdbassessormenudialog.h"

#include <QFileDialog>
#include <QKeyEvent>

#include "qtpvdbaboutdialog.h"
//#include "pvdbmenudialog.h"
#include "qtconceptmaprateconceptdialognewname.h"
#include "qtpvdbcreateassessmentcompletedialog.h"
#include "qtpvdbcreateassessmentmenudialog.h"
#include "qtpvdbrateconceptmapdialog.h"
#include "qtpvdbfiledialog.h"
#include "trace.h"


#include "ui_qtpvdbassessormenudialog.h"
#pragma GCC diagnostic pop

ribi::pvdb::QtPvdbAssessorMenuDialog::QtPvdbAssessorMenuDialog(QWidget* parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtPvdbAssessorMenuDialog)
{
  ui->setupUi(this);
}

ribi::pvdb::QtPvdbAssessorMenuDialog::~QtPvdbAssessorMenuDialog() noexcept
{
  delete ui;
}

void ribi::pvdb::QtPvdbAssessorMenuDialog::keyPressEvent(QKeyEvent* e)
{
  if (e->key()  == Qt::Key_Escape) { close(); return; }
}

void ribi::pvdb::QtPvdbAssessorMenuDialog::on_button_create_assessment_clicked()
{
  QtPvdbCreateAssessmentMenuDialog d;
  this->ShowChild(&d);
}


void ribi::pvdb::QtPvdbAssessorMenuDialog::on_button_about_clicked()
{
  const auto d(QtPvdbAboutDialog::Get());
  this->hide();
  d->exec();
  this->show();
}

void ribi::pvdb::QtPvdbAssessorMenuDialog::on_button_quit_clicked()
{
  close();
}

void ribi::pvdb::QtPvdbAssessorMenuDialog::on_button_assess_result_clicked()
{
  //Load assessent file
  const auto d = pvdb::QtFileDialog::GetOpenFileDialog();
  d->setWindowTitle("Kies een assessment bestand");
  const int status = d->exec();
  if (status == QDialog::Rejected) return;
  const auto v = d->selectedFiles();
  if (!v.isEmpty())
  {
    assert(v.size() == 1);
    const std::string filename = v[0].toStdString();
    const boost::shared_ptr<pvdb::File> file(pvdb::File::Load(filename));
    assert(file);
    QtPvdbRateConceptMapDialog d(file);
    this->ShowChild(&d);
  }
}
