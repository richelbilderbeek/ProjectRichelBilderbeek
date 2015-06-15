//---------------------------------------------------------------------------
/*
Project Richel Bilderbeek, Richel Bilderbeek's work
Copyright (C) 2010-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ProjectRichelBilderbeek.htm
//---------------------------------------------------------------------------
#include "wtrichelbilderbeekmenudialog.h"

#include <string>
#include <tuple>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>

#include <boost/function.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include <Wt/WAnchor>
#include <Wt/WBreak>
#include <Wt/WHBoxLayout>
#include <Wt/WImage>
#include <Wt/WLabel>
#include <Wt/WMenu>
#include <Wt/WStackedWidget>
#include <Wt/WTable>
#include <Wt/WTextArea>
#include <Wt/WVBoxLayout>
#include <Wt/WBorderLayout>

#include "fileio.h"
#include "gtstmenudialog.h"
#include "ipaddress.h"
#include "qtrichelbilderbeekgalleryresources.h"
#include "richelbilderbeekmenudialog.h"
#include "richelbilderbeekprogram.h"
#include "richelbilderbeekprogramstatus.h"
#include "shinybutton.h"
#include "shinybuttonwidget.h"
#include "testentrancemenudialog.h"
#include "testserverpushermenudialog.h"
#include "timepollmenudialog.h"
#include "wtaboutdialog.h"
#include "wtasciiartermaindialog.h"
#include "wtautoconfig.h"
#include "wtcodetohtmlmenudialog.h"
#include "wtconnectthreemenudialog.h"
#include "wtconnectthreewidget.h"
#include "wtdialwidget.h"
#include "wtencrangermenudialog.h"
#include "wtentrance.h"
#include "wtexercise.h"
#include "wtgroupwidget.h"
#include "wthometrainermenudialog.h"
#include "wtledwidget.h"
#include "wtmultiplechoicequestiondialog.h"
#include "wtmysterymachinewidget.h"
#include "wtopenquestiondialog.h"
#include "wtrandomcodemenudialog.h"
#include "wtrichelbilderbeekgallerydialog.h"
#include "wtrubiksclockmenudialog.h"
#include "wtrubiksclockwidget.h"
#include "wtselectfiledialog.h"
#include "wtserverpusher.h"
#include "wtserverpusherclient.h"
#include "wtshapegroupwidget.h"
#include "wtshapewidget.h"
#include "wtshinybuttonwidget.h"
#include "wtsimmysterymachinemenudialog.h"
#include "wttestdialmenudialog.h"
#include "wttestentrancemenudialog.h"
#include "wttestexercisemenudialog.h"
#include "wttestfunctionparsermenudialog.h"
#include "wttestgroupwidgetmenudialog.h"
#include "wttestledmenudialog.h"
#include "wttestnewickvectordialog.h"
#include "wttestquestionmenudialog.h"
#include "wttestselectfiledialogmenudialog.h"
#include "wttestserverpushermenudialog.h"
#include "wttestshapemenudialog.h"
#include "wttestshinybuttonmenudialog.h"
#include "wttesttimedserverpushermenudialog.h"
#include "wttesttogglebuttonmenudialog.h"
#include "wttesttwodigitnewickdialog.h"
#include "wttictactoemenudialog.h"
#include "wttictactoewidget.h"
#include "wttimedserverpusher.h"
#include "wttimedserverpusherclient.h"
#include "wttimepollmenudialog.h"
#include "wttogglebuttonwidget.h"

#pragma GCC diagnostic pop

ribi::RichelBilderbeek::WtMenuDialog::Ui::Ui()
  : m_stack_about(new Wt::WStackedWidget),
    m_stack_classes(new Wt::WStackedWidget),
    m_stack_games(new Wt::WStackedWidget),
    m_stack_main(new Wt::WStackedWidget),
    m_stack_projects(new Wt::WStackedWidget),
    m_stack_tools(new Wt::WStackedWidget)
{

}

ribi::RichelBilderbeek::WtMenuDialog::WtMenuDialog(const std::string& ip_address)
  : ui{},
    m_about_menu_items(CreateAboutMenuItems()),
    m_button_height(20),
    m_button_width(120),
    m_classes_menu_items(CreateClassesMenuItems()),
    m_games_menu_items(CreateGamesMenuItems()),
    m_ip_address(ip_address),
    m_main_menu_items(CreateMainMenuItems()),
    m_projects_menu_items(CreateProjectsMenuItems()),
    m_tools_menu_items(CreateToolsMenuItems())
{
  QtResources();
  //Create the menu
  this->setContentAlignment(Wt::AlignCenter);
  {
    Wt::WLabel * const title = new Wt::WLabel("Project Richel Bilderbeek");
    title->setStyleClass("title");
    this->addWidget(title);
  }

  this->addWidget(new Wt::WBreak);

  const int n_menu_items = boost::numeric_cast<int>(m_main_menu_items.size());
  const double gradient = 1.0 / boost::numeric_cast<double>(n_menu_items + 1);
  for (int i=0; i!=n_menu_items; ++i)
  {
    const double color = (0.5 * gradient) + (boost::numeric_cast<double>(i) * gradient);
    WtShinyButtonWidget * const b = new WtShinyButtonWidget(color,gradient,m_main_menu_items[i]->GetCaption());
    b->GetWidget()->SetGeometry(0,0,m_button_width,m_button_height);
    this->addWidget(b);
    b->GetWidget()->m_signal_clicked.connect(
      boost::bind(&ribi::RichelBilderbeek::WtMenuDialog::OnMainItemClicked,this,boost::lambda::_1));
    ui.m_stack_main->insertWidget(i,m_main_menu_items[i]->GetCreateDialogFunction()(this));
  }

  this->addWidget(new Wt::WBreak);
  this->addWidget(ui.m_stack_main);

  //Display first screen
  m_main_menu_items[0]->GetStack()->setCurrentIndex(m_main_menu_items[0]->GetIndex());

}

std::vector<ribi::RichelBilderbeek::WtMenuDialog::Item_t> ribi::RichelBilderbeek::WtMenuDialog::CollectSubMenuItems() const
{
  std::vector<Item_t> v;
  std::copy(m_about_menu_items.begin(),m_about_menu_items.end(),std::back_inserter(v));
  std::copy(m_classes_menu_items.begin(),m_classes_menu_items.end(),std::back_inserter(v));
  std::copy(m_games_menu_items.begin(),m_games_menu_items.end(),std::back_inserter(v));
  std::copy(m_projects_menu_items.begin(),m_projects_menu_items.end(),std::back_inserter(v));
  std::copy(m_tools_menu_items.begin(),m_tools_menu_items.end(),std::back_inserter(v));
  return v;
}

std::vector<boost::shared_ptr<ribi::RichelBilderbeek::WtMenuItem> >
  ribi::RichelBilderbeek::WtMenuDialog::CreateAboutMenuItems() const
{
  Wt::WStackedWidget * const s = ui.m_stack_about;
  return {
    boost::shared_ptr<ribi::RichelBilderbeek::WtMenuItem>(
      new WtMenuItem("Program" ,s,0,&ribi::RichelBilderbeek::WtMenuDialog::CreateNewAboutProgramDialog)
    ),
    boost::shared_ptr<ribi::RichelBilderbeek::WtMenuItem>(
      new WtMenuItem("Statuses",s,1,&ribi::RichelBilderbeek::WtMenuDialog::CreateNewStatusesDialog)
    ),
    boost::shared_ptr<ribi::RichelBilderbeek::WtMenuItem>(
      new WtMenuItem("Bep"     ,s,2,&ribi::RichelBilderbeek::WtMenuDialog::CreateNewAboutBepDialog)
    )
  };
}

std::vector<boost::shared_ptr<ribi::RichelBilderbeek::WtMenuItem> > ribi::RichelBilderbeek::WtMenuDialog::CreateClassesMenuItems() const
{
  Wt::WStackedWidget * const s = ui.m_stack_classes;
  return {
    boost::shared_ptr<ribi::RichelBilderbeek::WtMenuItem>(
      new WtMenuItem("Dial"             ,s, 0,&ribi::RichelBilderbeek::WtMenuDialog::CreateNewTestDialDialog)
    ),
    boost::shared_ptr<ribi::RichelBilderbeek::WtMenuItem>(
      new WtMenuItem("Entrance"         ,s, 1,&ribi::RichelBilderbeek::WtMenuDialog::CreateNewTestEntranceDialog)
    ),
    boost::shared_ptr<ribi::RichelBilderbeek::WtMenuItem>(
      new WtMenuItem("Exercise"         ,s, 2,&ribi::RichelBilderbeek::WtMenuDialog::CreateNewTestExerciseDialog)
    ),
    boost::shared_ptr<ribi::RichelBilderbeek::WtMenuItem>(
      new WtMenuItem("FunctionParser"   ,s, 3,&ribi::RichelBilderbeek::WtMenuDialog::CreateNewTestFunctionParserDialog)
    ),
    boost::shared_ptr<ribi::RichelBilderbeek::WtMenuItem>(
      new WtMenuItem("GroupWidget"      ,s, 4,&ribi::RichelBilderbeek::WtMenuDialog::CreateNewTestGroupWidgetDialog)
    ),
    boost::shared_ptr<ribi::RichelBilderbeek::WtMenuItem>(
      new WtMenuItem("Led"              ,s, 5,&ribi::RichelBilderbeek::WtMenuDialog::CreateNewTestLedDialog)
    ),
    boost::shared_ptr<ribi::RichelBilderbeek::WtMenuItem>(
      new WtMenuItem("Question"         ,s, 6,&ribi::RichelBilderbeek::WtMenuDialog::CreateNewTestQuestionDialog)
    ),
    boost::shared_ptr<ribi::RichelBilderbeek::WtMenuItem>(
      new WtMenuItem("SelectFile"       ,s, 7,&ribi::RichelBilderbeek::WtMenuDialog::CreateNewTestSelectFileDialogDialog)
    ),
    boost::shared_ptr<ribi::RichelBilderbeek::WtMenuItem>(
      new WtMenuItem("ServerPusher"     ,s, 8,&ribi::RichelBilderbeek::WtMenuDialog::CreateNewTestServerPusherDialog)
    ),
    boost::shared_ptr<ribi::RichelBilderbeek::WtMenuItem>(
      new WtMenuItem("Shape"            ,s, 9,&ribi::RichelBilderbeek::WtMenuDialog::CreateNewTestShapeDialog)
    ),
    boost::shared_ptr<ribi::RichelBilderbeek::WtMenuItem>(
      new WtMenuItem("ShinyButton"      ,s,10,&ribi::RichelBilderbeek::WtMenuDialog::CreateNewTestShinyButtonDialog)
    ),
    boost::shared_ptr<ribi::RichelBilderbeek::WtMenuItem>(
      new WtMenuItem("TimedServerPusher",s,11,&ribi::RichelBilderbeek::WtMenuDialog::CreateNewTestTimedServerPusherDialog)
    ),
    boost::shared_ptr<ribi::RichelBilderbeek::WtMenuItem>(
      new WtMenuItem("ToggleButton"     ,s,12,&ribi::RichelBilderbeek::WtMenuDialog::CreateNewTestToggleButtonDialog)
    ),
    boost::shared_ptr<ribi::RichelBilderbeek::WtMenuItem>(
      new WtMenuItem("TimePoll"         ,s,13,&ribi::RichelBilderbeek::WtMenuDialog::CreateNewTimePollDialog)
    )
  };
}

std::vector<boost::shared_ptr<ribi::RichelBilderbeek::WtMenuItem> > ribi::RichelBilderbeek::WtMenuDialog::CreateGamesMenuItems() const
{
  Wt::WStackedWidget * const s = ui.m_stack_games;

  return {
    boost::shared_ptr<ribi::RichelBilderbeek::WtMenuItem>(
      new WtMenuItem("Connect Three",s, 0,&ribi::RichelBilderbeek::WtMenuDialog::CreateNewConnectThreeDialog)
    ),
    boost::shared_ptr<ribi::RichelBilderbeek::WtMenuItem>(
      new WtMenuItem("Rubik's Clock",s, 1,&ribi::RichelBilderbeek::WtMenuDialog::CreateNewRubiksClockDialog)
    ),
    boost::shared_ptr<ribi::RichelBilderbeek::WtMenuItem>(
      new WtMenuItem("Tic Tac Toe"  ,s, 2,&ribi::RichelBilderbeek::WtMenuDialog::CreateNewTicTacToeDialog)
    )
  };
}

std::vector<boost::shared_ptr<ribi::RichelBilderbeek::WtMenuItem> > ribi::RichelBilderbeek::WtMenuDialog::CreateMainMenuItems() const
{
  Wt::WStackedWidget * const s = ui.m_stack_main;
  return {
    boost::shared_ptr<ribi::RichelBilderbeek::WtMenuItem>(
      new WtMenuItem("Welcome" ,s,0,&ribi::RichelBilderbeek::WtMenuDialog::CreateNewWelcomeDialog)
    ),
    boost::shared_ptr<ribi::RichelBilderbeek::WtMenuItem>(
      new WtMenuItem("Classes" ,s,1,&ribi::RichelBilderbeek::WtMenuDialog::CreateNewClassesDialog)
    ),
    boost::shared_ptr<ribi::RichelBilderbeek::WtMenuItem>(
      new WtMenuItem("Games"   ,s,2,&ribi::RichelBilderbeek::WtMenuDialog::CreateNewGamesDialog)
    ),
    boost::shared_ptr<ribi::RichelBilderbeek::WtMenuItem>(
      new WtMenuItem("Projects",s,3,&ribi::RichelBilderbeek::WtMenuDialog::CreateNewProjectsDialog)
    ),
    boost::shared_ptr<ribi::RichelBilderbeek::WtMenuItem>(
      new WtMenuItem("Tools"   ,s,4,&ribi::RichelBilderbeek::WtMenuDialog::CreateNewToolsDialog)
    ),
    boost::shared_ptr<ribi::RichelBilderbeek::WtMenuItem>(
      new WtMenuItem("About"   ,s,5,&ribi::RichelBilderbeek::WtMenuDialog::CreateNewAboutDialog)
    )
  };
}

std::vector<boost::shared_ptr<ribi::RichelBilderbeek::WtMenuItem> > ribi::RichelBilderbeek::WtMenuDialog::CreateProjectsMenuItems() const
{
  Wt::WStackedWidget * const s = ui.m_stack_projects;

  return {
    boost::shared_ptr<ribi::RichelBilderbeek::WtMenuItem>(
      new WtMenuItem("GTST"          ,s,0,&ribi::RichelBilderbeek::WtMenuDialog::CreateNewGtstDialog)
    ),
    boost::shared_ptr<ribi::RichelBilderbeek::WtMenuItem>(
      new WtMenuItem("NewickVector"  ,s,1,&ribi::RichelBilderbeek::WtMenuDialog::CreateNewTestNewickVectorDialog)
    ),
    boost::shared_ptr<ribi::RichelBilderbeek::WtMenuItem>(
      new WtMenuItem("TwoDigitNewick",s,2,&ribi::RichelBilderbeek::WtMenuDialog::CreateNewTestTwoDigitNewickDialog)
    )
  };
}

std::vector<boost::shared_ptr<ribi::RichelBilderbeek::WtMenuItem> > ribi::RichelBilderbeek::WtMenuDialog::CreateToolsMenuItems() const
{
  Wt::WStackedWidget * const s = ui.m_stack_tools;

  return {
    boost::shared_ptr<ribi::RichelBilderbeek::WtMenuItem>(
      new WtMenuItem("AsciiArter"    ,s,0,&ribi::RichelBilderbeek::WtMenuDialog::CreateNewTestAsciiArterDialog)
    ),
    boost::shared_ptr<ribi::RichelBilderbeek::WtMenuItem>(
      new WtMenuItem("CodeToHtml"    ,s,1,&ribi::RichelBilderbeek::WtMenuDialog::CreateNewCodeToHtmlDialog)
    ),
    boost::shared_ptr<ribi::RichelBilderbeek::WtMenuItem>(
      new WtMenuItem("Encranger"     ,s,2,&ribi::RichelBilderbeek::WtMenuDialog::CreateNewEncrangerDialog)
    ),
    boost::shared_ptr<ribi::RichelBilderbeek::WtMenuItem>(
      new WtMenuItem("Hometrainer"   ,s,3,&ribi::RichelBilderbeek::WtMenuDialog::CreateNewHometrainerDialog)
    ),
    boost::shared_ptr<ribi::RichelBilderbeek::WtMenuItem>(
      new WtMenuItem("MysteryMachine",s,4,&ribi::RichelBilderbeek::WtMenuDialog::CreateNewSimMysteryMachineDialog)
    ),
    boost::shared_ptr<ribi::RichelBilderbeek::WtMenuItem>(
      new WtMenuItem("RandomCode"    ,s,5,&ribi::RichelBilderbeek::WtMenuDialog::CreateNewRandomCodeDialog)
    )
  };
}

Wt::WWidget * ribi::RichelBilderbeek::WtMenuDialog::CreateNewAboutDialog()
{

  Wt::WContainerWidget * const dialog = new Wt::WContainerWidget;
  const int n_menu_items = boost::numeric_cast<int>(m_main_menu_items.size());
  const double gradient = 1.0 / boost::numeric_cast<double>(n_menu_items + 1);
  const int i = 5; // Index in the main menu
  assert(m_main_menu_items[i]->GetCaption() == "About");
  const double main_color = (0.5 * gradient) + (boost::numeric_cast<double>(i) * gradient);
  const auto& v = m_about_menu_items;
  const int n_sub_menu_items = boost::numeric_cast<int>(v.size());
  const double sub_menu_gradient = gradient / boost::numeric_cast<double>(n_sub_menu_items);
  for (int j=0; j!=n_sub_menu_items; ++j)
  {
    const double sub_menu_color = main_color - (0.5 * gradient) + (boost::numeric_cast<double>(j) * sub_menu_gradient);
    WtShinyButtonWidget * const b = new WtShinyButtonWidget(sub_menu_color,sub_menu_gradient,v[j]->GetCaption());
    b->GetWidget()->SetGeometry(0,0,m_button_width,m_button_height);
    dialog->addWidget(b);
    b->GetWidget()->m_signal_clicked.connect(
      boost::bind(&ribi::RichelBilderbeek::WtMenuDialog::OnSubItemClicked,this,boost::lambda::_1));
    ui.m_stack_about->insertWidget(j,v[j]->GetCreateDialogFunction()(this));
  }

  dialog->addWidget(ui.m_stack_about);
  return dialog;
}

Wt::WWidget * ribi::RichelBilderbeek::WtMenuDialog::CreateNewAboutBepDialog() const
{
  Wt::WContainerWidget * dialog = new Wt::WContainerWidget;
  const std::string filename_bep = QtResources().GetBep();

  assert(fileio::FileIo().IsRegularFile(filename_bep));
  dialog->setContentAlignment(Wt::AlignCenter);
  dialog->addWidget(new Wt::WBreak);
  new Wt::WLabel("Bep is the name of my webserver running Project Richel Bilderbeek,",dialog);
  new Wt::WBreak(dialog);
  new Wt::WLabel("running Ubuntu Server Edition (Oneiric Ocelot)",dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  new Wt::WImage(filename_bep.c_str(),dialog);
  new Wt::WBreak(dialog);
  new Wt::WLabel("Picture of Bep (*)",dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  new Wt::WLabel("(*) Bep's name is enhanced in KolourPaint,",dialog);
  new Wt::WBreak(dialog);
  new Wt::WLabel("picture taken by Jean-Marc Bilderbeek.",dialog);
  return dialog;
}

Wt::WWidget * ribi::RichelBilderbeek::WtMenuDialog::CreateNewAboutProgramDialog() const
{
  About a = ProjectRichelBilderbeekMenuDialog().GetAbout();
  a.AddLibrary("Big Integer Library (by Matt McCutchen) version: 2010.04.30");
  a.AddLibrary("GTST version: " + ribi::gtst::MenuDialog::GetVersion());
  a.AddLibrary("TestEntrance version: " + ToolTestEntrance::MenuDialog().GetVersion());
  a.AddLibrary("TestServerPusher version: " + ToolTestServerPusher::MenuDialog::GetVersion());
  a.AddLibrary("TimePoll version: " + ToolTimePoll::TimePollMenuDialog::GetVersion());
  a.AddLibrary("WtAutoConfig version: " + WtAutoConfig::GetVersion());
  a.AddLibrary("WtConnectThreeWidget version: " + con3::WtConnectThreeWidget::GetVersion());
  a.AddLibrary("WtDialWidget version: " + WtDialWidget::GetVersion());
  a.AddLibrary("WtGroupWidget version: " + WtGroupWidget::GetVersion());
  a.AddLibrary("WtEntrance version: " + WtEntrance::GetVersion());
  a.AddLibrary("WtExercise version: " + WtExercise::GetVersion());
  a.AddLibrary("WtLedWidget version: " + WtLedWidget::GetVersion());
  a.AddLibrary("WtMultipleChoiceQuestionDialog version: " + WtMultipleChoiceQuestionDialog::GetVersion());
  a.AddLibrary("WtMysteryMachineWidget version: " + WtMysteryMachineWidget::GetVersion());
  a.AddLibrary("WtOpenQuestionDialog version: " + WtOpenQuestionDialog::GetVersion());
  a.AddLibrary("WtQuestionDialog version: " + WtOpenQuestionDialog::GetVersion());
  a.AddLibrary("WtRubiksClockWidget version: " + ruco::WtClockWidget::GetVersion());
  a.AddLibrary("WtServerPusher version: " + WtServerPusher::GetVersion());
  a.AddLibrary("WtServerPusherClient version: " + WtServerPusherClient::GetVersion());
  a.AddLibrary("WtSelectFileDialog version: " + WtSelectFileDialog::GetVersion());
  a.AddLibrary("WtShapeWidget version: " + WtShapeWidget::GetVersion());
  a.AddLibrary("WtShapeGroupWidget version: " + WtShapeGroupWidget::GetVersion());
  a.AddLibrary("WtShinyButtonWidget version: " + WtShinyButtonWidget::GetVersion());
  a.AddLibrary("WtTicTacToeWidget version: " + WtTicTacToeWidget::GetVersion());
  a.AddLibrary("WtTimedServerPusher version: " + WtTimedServerPusher::GetVersion());
  a.AddLibrary("WtTimedServerPusherClient version: " + WtTimedServerPusherClient::GetVersion());
  a.AddLibrary("WtToggleButtonWidget version: " + WtToggleButtonWidget::GetVersion());
  WtAboutDialog * const d = new WtAboutDialog(a,false);
  assert(d);
  return d;
}

Wt::WWidget * ribi::RichelBilderbeek::WtMenuDialog::CreateNewClassesDialog()
{
  Wt::WContainerWidget * const dialog = new Wt::WContainerWidget;
  const int n_menu_items = boost::numeric_cast<int>(m_main_menu_items.size());
  const double gradient = 1.0 / boost::numeric_cast<double>(n_menu_items + 1);
  const int i = 1; // Index in the main menu
  const double main_color = (0.5 * gradient) + (boost::numeric_cast<double>(i) * gradient);
  const auto& v = m_classes_menu_items;
  const int n_sub_menu_items = boost::numeric_cast<int>(v.size());
  const double sub_menu_gradient = gradient / boost::numeric_cast<double>(n_sub_menu_items);
  for (int j=0; j!=n_sub_menu_items; ++j)
  {
    const double sub_menu_color = main_color - (0.5 * gradient) + (boost::numeric_cast<double>(j) * sub_menu_gradient);
    WtShinyButtonWidget * const b = new WtShinyButtonWidget(sub_menu_color,sub_menu_gradient,v[j]->GetCaption());
    b->GetWidget()->SetGeometry(0,0,m_button_width,m_button_height);
    dialog->addWidget(b);
    b->GetWidget()->m_signal_clicked.connect(
      boost::bind(&ribi::RichelBilderbeek::WtMenuDialog::OnSubItemClicked,this,boost::lambda::_1));
    ui.m_stack_classes->insertWidget(j,v[j]->GetCreateDialogFunction()(this));
  }
  dialog->addWidget(ui.m_stack_classes);

  return dialog;
}

Wt::WWidget * ribi::RichelBilderbeek::WtMenuDialog::CreateNewCodeToHtmlDialog() const
{
  c2h::WtMenuDialog * const d = new c2h::WtMenuDialog;
  assert(d);
  return d;
}

Wt::WWidget * ribi::RichelBilderbeek::WtMenuDialog::CreateNewConnectThreeDialog() const
{
  con3::WtConnectThreeMenuDialog * const d = new con3::WtConnectThreeMenuDialog;
  assert(d);
  return d;
}

Wt::WWidget * ribi::RichelBilderbeek::WtMenuDialog::CreateNewGamesDialog()
{
  Wt::WContainerWidget * const dialog = new Wt::WContainerWidget;
  const int n_menu_items = boost::numeric_cast<int>(m_main_menu_items.size());
  const double gradient = 1.0 / boost::numeric_cast<double>(n_menu_items + 1);
  const int i = 2; // Index in the main menu
  const double main_color = (0.5 * gradient) + (boost::numeric_cast<double>(i) * gradient);
  const auto& v = m_games_menu_items;
  const int n_sub_menu_items = boost::numeric_cast<int>(v.size());
  const double sub_menu_gradient = gradient / boost::numeric_cast<double>(n_sub_menu_items);

  for (int j=0; j!=n_sub_menu_items; ++j)
  {
    const double sub_menu_color = main_color - (0.5 * gradient) + (boost::numeric_cast<double>(j) * sub_menu_gradient);
    WtShinyButtonWidget * const b = new WtShinyButtonWidget(sub_menu_color,sub_menu_gradient,v[j]->GetCaption());
    b->GetWidget()->SetGeometry(0,0,m_button_width,m_button_height);
    dialog->addWidget(b);
    b->GetWidget()->m_signal_clicked.connect(
      boost::bind(&ribi::RichelBilderbeek::WtMenuDialog::OnSubItemClicked,this,boost::lambda::_1));
    ui.m_stack_games->insertWidget(j,v[j]->GetCreateDialogFunction()(this));
  }
  dialog->addWidget(ui.m_stack_games);
  return dialog;
}

Wt::WWidget * ribi::RichelBilderbeek::WtMenuDialog::CreateNewGtstDialog() const
{
  boost::scoped_ptr<SafeIpAddress> ip_address(
    new SafeIpAddress(m_ip_address));
  gtst::MenuDialog * const d
    = new gtst::MenuDialog(ip_address.get());
  assert(d);
  return d;
}

Wt::WWidget * ribi::RichelBilderbeek::WtMenuDialog::CreateNewHometrainerDialog() const
{
  WtHometrainerMenuDialog * const d = new WtHometrainerMenuDialog;
  assert(d);
  return d;
}

Wt::WWidget * ribi::RichelBilderbeek::WtMenuDialog::CreateNewProjectsDialog()
{
  Wt::WContainerWidget * const dialog = new Wt::WContainerWidget;
  const int n_menu_items = boost::numeric_cast<int>(m_main_menu_items.size());
  const double gradient = 1.0 / boost::numeric_cast<double>(n_menu_items + 1);
  const int i = 3; // Index in the main menu
  const double main_color = (0.5 * gradient) + (boost::numeric_cast<double>(i) * gradient);
  const auto& v = m_projects_menu_items;
  const int n_sub_menu_items = boost::numeric_cast<int>(v.size());
  const double sub_menu_gradient = gradient / boost::numeric_cast<double>(n_sub_menu_items);
  for (int j=0; j!=n_sub_menu_items; ++j)
  {
    const double sub_menu_color = main_color - (0.5 * gradient) + (boost::numeric_cast<double>(j) * sub_menu_gradient);
    WtShinyButtonWidget * const b = new WtShinyButtonWidget(sub_menu_color,sub_menu_gradient,v[j]->GetCaption());
    b->GetWidget()->SetGeometry(0,0,m_button_width,m_button_height);
    dialog->addWidget(b);
    b->GetWidget()->m_signal_clicked.connect(
      boost::bind(&ribi::RichelBilderbeek::WtMenuDialog::OnSubItemClicked,this,boost::lambda::_1));
    ui.m_stack_projects->insertWidget(j,v[j]->GetCreateDialogFunction()(this));
  }
  dialog->addWidget(ui.m_stack_projects);
  return dialog;
}

Wt::WWidget * ribi::RichelBilderbeek::WtMenuDialog::CreateNewRandomCodeDialog() const
{
  WtRandomCodeMenuDialog * const d = new WtRandomCodeMenuDialog;
  assert(d);
  return d;
}

Wt::WWidget * ribi::RichelBilderbeek::WtMenuDialog::CreateNewRubiksClockDialog() const
{
  ruco::WtRubiksClockMenuDialog * const d = new ruco::WtRubiksClockMenuDialog;
  assert(d);
  return d;
}

Wt::WWidget * ribi::RichelBilderbeek::WtMenuDialog::CreateNewSimMysteryMachineDialog() const
{
  WtSimMysteryMachineMenuDialog * const d = new WtSimMysteryMachineMenuDialog;
  assert(d);
  return d;
}

Wt::WWidget * ribi::RichelBilderbeek::WtMenuDialog::CreateNewStatusesDialog() const
{
  Wt::WContainerWidget * dialog = new Wt::WContainerWidget;
  dialog->setContentAlignment(Wt::AlignCenter);
  dialog->addWidget(new RichelBilderbeek::WtGalleryDialog);
  return dialog;
}


Wt::WWidget * ribi::RichelBilderbeek::WtMenuDialog::CreateNewTestAsciiArterDialog() const
{
  WtAsciiArterMainDialog * const d = new WtAsciiArterMainDialog;
  assert(d);
  return d;
}

Wt::WWidget * ribi::RichelBilderbeek::WtMenuDialog::CreateNewTestDialDialog() const
{
  WtTestDialMenuDialog * const d = new WtTestDialMenuDialog;
  assert(d);
  return d;
}

Wt::WWidget * ribi::RichelBilderbeek::WtMenuDialog::CreateNewEncrangerDialog() const
{
  WtEncrangerMenuDialog * const d = new WtEncrangerMenuDialog;
  assert(d);
  return d;
}

Wt::WWidget * ribi::RichelBilderbeek::WtMenuDialog::CreateNewTestEntranceDialog() const
{
  boost::shared_ptr<IpAddress> ip_address(new IpAddress(m_ip_address));
  ToolTestEntrance::WtMenuDialog * const d
    = new ToolTestEntrance::WtMenuDialog(ip_address);
  assert(d);
  return d;
}

Wt::WWidget * ribi::RichelBilderbeek::WtMenuDialog::CreateNewTestExerciseDialog() const
{
  WtTestExerciseMenuDialog * const d = new WtTestExerciseMenuDialog;
  assert(d);
  return d;
}

Wt::WWidget * ribi::RichelBilderbeek::WtMenuDialog::CreateNewTestFunctionParserDialog() const
{
  WtTestFunctionParserMenuDialog * const d = new WtTestFunctionParserMenuDialog;
  assert(d);
  return d;
}

Wt::WWidget * ribi::RichelBilderbeek::WtMenuDialog::CreateNewTestGroupWidgetDialog() const
{
  WtTestGroupWidgetMenuDialog * const d = new WtTestGroupWidgetMenuDialog;
  assert(d);
  return d;
}

Wt::WWidget * ribi::RichelBilderbeek::WtMenuDialog::CreateNewTestLedDialog() const
{
  WtTestLedMenuDialog * const d = new WtTestLedMenuDialog;
  assert(d);
  return d;
}

Wt::WWidget * ribi::RichelBilderbeek::WtMenuDialog::CreateNewTestNewickVectorDialog() const
{
  WtTestNewickVectorDialog * const d = new WtTestNewickVectorDialog;
  assert(d);
  return d;
}

Wt::WWidget * ribi::RichelBilderbeek::WtMenuDialog::CreateNewTestQuestionDialog() const
{
  WtTestQuestionMenuDialog * const d = new WtTestQuestionMenuDialog;
  assert(d);
  return d;
}

Wt::WWidget * ribi::RichelBilderbeek::WtMenuDialog::CreateNewTestSelectFileDialogDialog() const
{
  WtTestSelectFileDialogMenuDialog * const d = new WtTestSelectFileDialogMenuDialog;
  assert(d);
  return d;
}

Wt::WWidget * ribi::RichelBilderbeek::WtMenuDialog::CreateNewTestServerPusherDialog() const
{
  ToolTestServerPusher::WtMenuDialog * const d = new ToolTestServerPusher::WtMenuDialog;
  assert(d);
  return d;
}

Wt::WWidget * ribi::RichelBilderbeek::WtMenuDialog::CreateNewTestShapeDialog() const
{
  WtTestShapeMenuDialog * const d = new WtTestShapeMenuDialog;
  assert(d);
  return d;
}

Wt::WWidget * ribi::RichelBilderbeek::WtMenuDialog::CreateNewTestShinyButtonDialog() const
{
  WtTestShinyButtonMenuDialog * const d = new WtTestShinyButtonMenuDialog;
  assert(d);
  return d;
}

Wt::WWidget * ribi::RichelBilderbeek::WtMenuDialog::CreateNewTestTimedServerPusherDialog() const
{
  ToolTestTimedServerPusher::WtMenuDialog * const d = new ToolTestTimedServerPusher::WtMenuDialog;
  assert(d);
  return d;
}

Wt::WWidget * ribi::RichelBilderbeek::WtMenuDialog::CreateNewTestToggleButtonDialog() const
{
  WtTestToggleButtonMenuDialog * const d = new WtTestToggleButtonMenuDialog;
  assert(d);
  return d;
}

Wt::WWidget * ribi::RichelBilderbeek::WtMenuDialog::CreateNewTestTwoDigitNewickDialog() const
{
  WtTestTwoDigitNewickDialog * const d = new WtTestTwoDigitNewickDialog;
  assert(d);
  return d;
}

Wt::WWidget * ribi::RichelBilderbeek::WtMenuDialog::CreateNewTicTacToeDialog() const
{
  tictactoe::WtTicTacToeMenuDialog * const d = new tictactoe::WtTicTacToeMenuDialog;
  assert(d);
  return d;
}

Wt::WWidget * ribi::RichelBilderbeek::WtMenuDialog::CreateNewTimePollDialog() const
{
  ToolTimePoll::WtTimePollMenuDialog * const d
    = new ToolTimePoll::WtTimePollMenuDialog;
  assert(d);
  return d;
}

Wt::WWidget * ribi::RichelBilderbeek::WtMenuDialog::CreateNewToolsDialog()
{
  Wt::WContainerWidget * const dialog = new Wt::WContainerWidget;
  const int n_menu_items = boost::numeric_cast<int>(m_main_menu_items.size());
  const double gradient = 1.0 / boost::numeric_cast<double>(n_menu_items + 1);
  const int i = 4; // Index in the main menu
  const double main_color = (0.5 * gradient) + (boost::numeric_cast<double>(i) * gradient);
  const auto& v = m_tools_menu_items;
  const int n_sub_menu_items = boost::numeric_cast<int>(v.size());
  const double sub_menu_gradient = gradient / boost::numeric_cast<double>(n_sub_menu_items);

  for (int j=0; j!=n_sub_menu_items; ++j)
  {
    const double sub_menu_color = main_color - (0.5 * gradient) + (boost::numeric_cast<double>(j) * sub_menu_gradient);
    WtShinyButtonWidget * const b = new WtShinyButtonWidget(sub_menu_color,sub_menu_gradient,v[j]->GetCaption());
    b->GetWidget()->SetGeometry(0,0,m_button_width,m_button_height);
    dialog->addWidget(b);
    b->GetWidget()->m_signal_clicked.connect(
      boost::bind(&ribi::RichelBilderbeek::WtMenuDialog::OnSubItemClicked,this,boost::lambda::_1));
    ui.m_stack_tools->insertWidget(j,v[j]->GetCreateDialogFunction()(this));
  }
  dialog->addWidget(ui.m_stack_tools);
  return dialog;
}

Wt::WWidget * ribi::RichelBilderbeek::WtMenuDialog::CreateNewWelcomeDialog() const
{
  Wt::WContainerWidget * dialog = new Wt::WContainerWidget;
  dialog->setContentAlignment(Wt::AlignCenter);
  {
    Wt::WLabel * const title = new Wt::WLabel("Welcome");
    title->setStyleClass("title");
    dialog->addWidget(title);
  }
  dialog->addWidget(new Wt::WBreak);
  new Wt::WLabel("Welcome to Project Richel Bilderbeek",dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  new Wt::WLabel("Project Richel Bilderbeek collects all my web applications as one single application.",dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  new Wt::WLabel("All code can be found at my static HTML website:",dialog);
  new Wt::WBreak(dialog);
  new Wt::WAnchor("http://www.richelbilderbeek.nl","www.richelbilderbeek.nl",dialog);
  return dialog;
}

void ribi::RichelBilderbeek::WtMenuDialog::OnMainItemClicked(const ShinyButtonWidget * const widget)
{
  assert(widget);
  const std::string text = widget->GetShinyButton()->GetText();
  const auto i = std::find_if(m_main_menu_items.begin(),m_main_menu_items.end(),
    [text](const Item_t& item)
    {
      return item->GetCaption() == text;
    }
  );

  assert(i != m_main_menu_items.end());

  (*i)->GetStack()->setCurrentIndex((*i)->GetIndex());
}

void ribi::RichelBilderbeek::WtMenuDialog::OnSubItemClicked(const ShinyButtonWidget * const widget)
{
  const std::vector<Item_t> sub_menu_items = CollectSubMenuItems();

  assert(widget);
  const std::string text = widget->GetShinyButton()->GetText();
  const auto i = std::find_if(sub_menu_items.begin(),sub_menu_items.end(),
    [text](const Item_t& item)
    {
      return item->GetCaption() == text;
    }
  );

  assert(i != sub_menu_items.end());

  (*i)->GetStack()->setCurrentIndex((*i)->GetIndex());
}
