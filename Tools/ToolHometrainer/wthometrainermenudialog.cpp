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
#include "wthometrainermenudialog.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <cassert>

#include <boost/lambda/lambda.hpp>

#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WGroupBox>
#include <Wt/WImage>
#include <Wt/WLabel>
#include <Wt/WStackedWidget>
#include <Wt/WMenu>
#include <Wt/WMenuItem>

#include "hometrainermenudialog.h"
#include "hometrainerresources.h"
#include "wtaboutdialog.h"
#include "wtautoconfig.h"
#include "wtexercise.h"
#include "wthometrainerloadexercisedialog.h"
#include "wthometrainerstartexercisedialog.h"
#include "wtmultiplechoicequestiondialog.h"
#include "wtopenquestiondialog.h"
#include "wtquestiondialog.h"
#include "wtselectfiledialog.h"

#include <QFile>
#pragma GCC diagnostic pop

ribi::WtHometrainerMenuDialog::Ui::Ui()
  : m_load_exercise(new WtHometrainerLoadExerciseDialog),
    m_start_exercise(new WtHometrainerStartExerciseDialog)
{

}

ribi::WtHometrainerMenuDialog::WtHometrainerMenuDialog()
  : ui{}
{
  HometrainerResources();
  ui.m_load_exercise->DoRefresh();

  this->setContentAlignment(Wt::AlignCenter);
  {
    Wt::WLabel * const title = new Wt::WLabel("Hometrainer");
    title->setStyleClass("title");
    this->addWidget(title);
  }
  //Menu
  {
    Wt::WStackedWidget * const contents = new Wt::WStackedWidget;
    Wt::WMenu * const menu = new Wt::WMenu(contents,Wt::Horizontal);
    menu->setStyleClass("menu");
    {
      Wt::WMenuItem * const item = new Wt::WMenuItem(
        "Welcome",
        CreateNewWelcomeDialog());
      menu->addItem(item);
    }
    {
      Wt::WMenuItem * const item = new Wt::WMenuItem(
        "Load exercise",
        ui.m_load_exercise);
      menu->addItem(item);
    }
    {
      Wt::WMenuItem * const item = new Wt::WMenuItem(
        "Start exercise",
        ui.m_start_exercise);
      menu->addItem(item);
    }
    {
      Wt::WMenuItem * const item = new Wt::WMenuItem(
        "About",
        CreateNewAboutDialog());
      menu->addItem(item);
    }
    //Display menu on top
    this->addWidget(menu);
    this->addWidget(new Wt::WBreak);
    //Display contents below menu
    this->addWidget(contents);
  }

  ui.m_load_exercise->m_signal_selected_file.connect(
    boost::bind(&ribi::WtHometrainerMenuDialog::OnSelectedFile,this,boost::lambda::_1));
}

Wt::WWidget * ribi::WtHometrainerMenuDialog::CreateNewAboutDialog() const
{
  HometrainerMenuDialog dialog;
  About a = dialog.GetAbout();
  a.AddLibrary("WtAutoConfig version: " + WtAutoConfig::GetVersion());
  a.AddLibrary("WtExercise version: " + WtExercise::GetVersion());
  a.AddLibrary("WtMultipleChoiceQuestionDialog version: " + WtMultipleChoiceQuestionDialog::GetVersion());
  a.AddLibrary("WtOpenQuestionDialog version: " + WtOpenQuestionDialog::GetVersion());
  a.AddLibrary("WtQuestionDialog version: " + WtQuestionDialog::GetVersion());
  a.AddLibrary("WtSelectFileDialog version: " + WtSelectFileDialog::GetVersion());
  WtAboutDialog * const d = new WtAboutDialog(a,false);
  assert(d);
  return d;
}

Wt::WWidget * ribi::WtHometrainerMenuDialog::CreateNewWelcomeDialog() const
{
  Wt::WContainerWidget * const dialog = new Wt::WContainerWidget;
  dialog->setContentAlignment(Wt::AlignCenter);
  dialog->addWidget(new Wt::WBreak);
  new Wt::WLabel("Welcome to Hometrainer",dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  new Wt::WLabel("Hometrainer is an exercise and survey suite",dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
   Wt::WGroupBox * const box = new Wt::WGroupBox("Explanation",dialog);
  box->addWidget(new Wt::WImage("ToolHometrainerWelcome.png"));
  return dialog;
}

void ribi::WtHometrainerMenuDialog::OnSelectedFile(const std::string filename)
{
  ui.m_start_exercise->LoadExercise(filename);
}


