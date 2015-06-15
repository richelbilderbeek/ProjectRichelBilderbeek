//---------------------------------------------------------------------------
/*
TestExercise, tool to test the Exercise class
Copyright (C) 2011-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestExercise.htm
//---------------------------------------------------------------------------
#include <cstdio>
#include <fstream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <Wt/WBreak>
#include <Wt/WLabel>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WTextArea>

#include "exercise.h"
#include "multiplechoicequestion.h"
#include "multiplechoicequestiondialog.h"
#include "openquestion.h"
#include "openquestiondialog.h"
#include "questiondialog.h"
//#include "trace.h"
#include "wtaboutdialog.h"
#include "wtmultiplechoicequestiondialog.h"
#include "wtopenquestiondialog.h"
#include "wtexercise.h"
#include "wttestexercisemaindialog.h"
#pragma GCC diagnostic pop

ribi::WtTestExerciseMainDialog::Ui::Ui()
  : m_area_input(new Wt::WTextArea),
    m_button_submit(new Wt::WPushButton),
    m_edit_wait_correct(new Wt::WLineEdit),
    m_edit_wait_incorrect(new Wt::WLineEdit),
    m_label_status(new Wt::WLabel),
    m_exercise_dialog(new WtExercise)
{

}

ribi::WtTestExerciseMainDialog::WtTestExerciseMainDialog()
  : ui{}
{
  this->addWidget(new Wt::WLabel("Waiting time correct (msecs)"));
  this->addWidget(ui.m_edit_wait_correct);
  this->addWidget(new Wt::WBreak);
  this->addWidget(new Wt::WLabel("Waiting time incorrect (msecs)"));
  this->addWidget(ui.m_edit_wait_incorrect);
  this->addWidget(new Wt::WBreak);
  this->addWidget(new Wt::WBreak);
  this->addWidget(ui.m_area_input);
  this->addWidget(new Wt::WBreak);
  this->addWidget(ui.m_button_submit);
  this->addWidget(new Wt::WBreak);
  this->addWidget(ui.m_exercise_dialog);

  ui.m_button_submit->setText("Submit");
  ui.m_button_submit->clicked().connect(this,&ribi::WtTestExerciseMainDialog::OnSubmit);

  ui.m_edit_wait_correct->setText("1000");
  ui.m_edit_wait_incorrect->setText("5000");
  ui.m_exercise_dialog->setMinimumSize(600,400);
  ui.m_area_input->setMinimumSize(800,100);
  ui.m_area_input->setText(
    "-,1+1=?,2/two/Two\n"
    "-,1+1=?,2,1,3,4\n"
    "ToolTestExerciseQuestion.png,The solution of this equation is:,2/two/Two\n"
    "ToolTestExerciseQuestion.png,The solution of this equation is:,2,1,3,4");
}

void ribi::WtTestExerciseMainDialog::OnSubmit()
{
  //Test input
  {
    const std::string s = ui.m_edit_wait_correct->text().toUTF8();
    try
    {
      const int i = boost::lexical_cast<int>(s);
      if (i < 0)
      {
        ui.m_button_submit->setText("Waiting time correct must be a positive integer");
        return;
      }
    }
    catch (boost::bad_lexical_cast&)
    {
      ui.m_button_submit->setText("Waiting time correct must be an integer");
      return;
    }
  }
  {
    const std::string s = ui.m_edit_wait_incorrect->text().toUTF8();
    try
    {
      const int i = boost::lexical_cast<int>(s);
      if (i < 0)
      {
        ui.m_button_submit->setText("Waiting time incorrect must be a positive integer");
        return;
      }
    }
    catch (boost::bad_lexical_cast&)
    {
      ui.m_button_submit->setText("Waiting time incorrect must be an integer");
      return;
    }
  }
  ui.m_button_submit->setText("Submit");


  //Process valid input
  const std::string filename = "tmp.txt";
  //Save text to file
  {
    std::ofstream f(filename.c_str());
    assert(ui.m_area_input);
    f << ui.m_area_input->text().toUTF8();
  }
  //Read the WtExercise from file
  assert(ui.m_exercise_dialog);
  ui.m_exercise_dialog->SetQuestions(filename.c_str());
  ui.m_exercise_dialog->SetWaitingTimeCorrect(
    boost::lexical_cast<int>(ui.m_edit_wait_correct->text().toUTF8()));
  ui.m_exercise_dialog->SetWaitingTimeIncorrect(
    boost::lexical_cast<int>(ui.m_edit_wait_incorrect->text().toUTF8()));
  //Remove the file
  std::remove(filename.c_str());
  //Display info about the WtExercise
  {
    const std::string s
      = std::string("Loaded ")
      + boost::lexical_cast<std::string>(ui.m_exercise_dialog->GetExercise()->GetNumberOfQuestions())
      + std::string(" questions");
    ui.m_label_status->setText(s.c_str());
  }
}

