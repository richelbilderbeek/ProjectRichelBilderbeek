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
#include "qtpvdbcreateassessmentmenudialog.h"

#include <QKeyEvent>

#include "qtpvdbcreateassessmentcompletedialog.h"
#include "qtpvdbcreateassessmentpartialdialog.h"
#include "trace.h"


#include "ui_qtpvdbcreateassessmentmenudialog.h"

#include "pvdbfile.h"
#pragma GCC diagnostic pop

ribi::pvdb::QtPvdbCreateAssessmentMenuDialog::QtPvdbCreateAssessmentMenuDialog(QWidget* parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtPvdbCreateAssessmentMenuDialog),
    m_back_to_menu{false},
    m_question{}
{
  ui->setupUi(this);
}

ribi::pvdb::QtPvdbCreateAssessmentMenuDialog::~QtPvdbCreateAssessmentMenuDialog() noexcept
{
  delete ui;
}

void ribi::pvdb::QtPvdbCreateAssessmentMenuDialog::keyPressEvent(QKeyEvent* e)
{
  if (e->key()  == Qt::Key_Escape) close();
}

void ribi::pvdb::QtPvdbCreateAssessmentMenuDialog::on_button_create_assessment_complete_clicked()
{
  QtPvdbCreateAssessmentCompleteDialog d;
  d.SetQuestion(m_question);
  this->ShowChild(&d);
  m_question = d.GetQuestion();
  if (d.GoBackToMenu())
  {
    this->close();
  }
}
