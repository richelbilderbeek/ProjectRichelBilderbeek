//---------------------------------------------------------------------------
/*
Hometrainer, exercise and survey suite
Copyright (C) 2009-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolHometrainer.htm
//---------------------------------------------------------------------------
#include "wthometrainerstartexercisedialog.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#pragma GCC diagnostic ignored "-Wcomment"
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <Wt/WBreak>
#include <Wt/WFileUpload>
#include <Wt/WGroupBox>
#include <Wt/WLabel>
#include <Wt/WLineEdit>
#include <Wt/WMenu>
#include <Wt/WMenuItem>
#include <Wt/WPushButton>
#include <Wt/WStackedWidget>

#include "exercise.h"
#include "multiplechoicequestion.h"
#include "multiplechoicequestiondialog.h"
#include "openquestion.h"
#include "openquestiondialog.h"
#include "questiondialog.h"
#include "wtaboutdialog.h"
#include "wtexercise.h"
#include "wtopenquestiondialog.h"
#include "wtmultiplechoicequestiondialog.h"
#pragma GCC diagnostic pop

ribi::WtHometrainerStartExerciseDialog::Ui::Ui()
  : m_box_exercise(new Wt::WGroupBox)
{

}

ribi::WtHometrainerStartExerciseDialog::WtHometrainerStartExerciseDialog()
  : ui{}
{
  ui.m_box_exercise->addWidget(new Wt::WLabel("No exercise loaded: select a file from the 'Load Exercise' menu item"));
  this->addWidget(ui.m_box_exercise);
}

void ribi::WtHometrainerStartExerciseDialog::LoadExercise(const std::string& filename)
{
  WtExercise * const exercise = new WtExercise;
  ui.m_box_exercise->clear();
  exercise->SetQuestions(filename);
  ui.m_box_exercise->addWidget(exercise);
}

