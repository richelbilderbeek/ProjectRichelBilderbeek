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
//From http://www.richelbilderbeek.nl/ProjectWtRichelBilderbeek.htm
//---------------------------------------------------------------------------
#ifndef WTRICHELBILDERBEEKMENUDIALOG_H
#define WTRICHELBILDERBEEKMENUDIALOG_H


#include <string>
#include <tuple>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <Wt/WContainerWidget>
#include <Wt/WPushButton>

#include "wtrichelbilderbeekmenuitem.h"
#pragma GCC diagnostic pop

namespace Wt
{
  enum Orientation;
  struct WMenu;
  struct WStackedWidget;
  struct WWidget;
}

namespace ribi {

struct ShinyButtonWidget;

namespace RichelBilderbeek {

///WtMenuDialog is the menu of WtRichelBilderbeek
struct WtMenuDialog : public Wt::WContainerWidget
{
  typedef boost::shared_ptr<WtMenuItem> Item_t;

  explicit WtMenuDialog(const std::string& ip_address);

  private:
  struct Ui
  {
    Ui();
    Wt::WStackedWidget * const m_stack_about;
    Wt::WStackedWidget * const m_stack_classes;
    Wt::WStackedWidget * const m_stack_games;
    Wt::WStackedWidget * const m_stack_main;
    Wt::WStackedWidget * const m_stack_projects;
    Wt::WStackedWidget * const m_stack_tools;
  } ui;


  const std::vector<Item_t> m_about_menu_items;

  const int m_button_height;
  const int m_button_width;

  const std::vector<Item_t> m_classes_menu_items;
  const std::vector<Item_t> m_games_menu_items;

  ///The client his/her IP address
  const std::string m_ip_address;

  const std::vector<Item_t> m_main_menu_items;
  const std::vector<Item_t> m_projects_menu_items;
  const std::vector<Item_t> m_tools_menu_items;


  ///Collect all the submenu items
  std::vector<Item_t> CollectSubMenuItems() const;

  ///Create the 'About' submenu dialog
  Wt::WWidget * CreateNewAboutDialog();

  ///Create the 'About | About Bep' dialog
  Wt::WWidget * CreateNewAboutBepDialog() const;

  ///Create the 'About | About the program' dialog
  Wt::WWidget * CreateNewAboutProgramDialog() const;

  ///Create the 'Classes' submenu dialog
  Wt::WWidget * CreateNewClassesDialog();

  ///Create the 'Tools | CodeToHtml' subsubmenu dialog
  Wt::WWidget * CreateNewCodeToHtmlDialog() const;

  ///Create the 'Games | ConnectThree' subsubmenu dialog
  Wt::WWidget * CreateNewConnectThreeDialog() const;

  ///Create the 'Games' submenu dialog
  Wt::WWidget * CreateNewGamesDialog();

  ///Create the 'project | GTST' subsubmenu dialog
  Wt::WWidget * CreateNewGtstDialog() const;

  ///Create the 'Tools | Hometrainer' subsubmenu dialog
  Wt::WWidget * CreateNewHometrainerDialog() const;

  ///Create the 'Projects' submenu dialog
  Wt::WWidget * CreateNewProjectsDialog();

  Wt::WWidget * CreateNewRandomCodeDialog() const;
  Wt::WWidget * CreateNewRubiksClockDialog() const;
  Wt::WWidget * CreateNewSimMysteryMachineDialog() const;
  Wt::WWidget * CreateNewStatusesDialog() const;
  Wt::WWidget * CreateNewTestAsciiArterDialog() const;
  Wt::WWidget * CreateNewTestDialDialog() const;
  Wt::WWidget * CreateNewEncrangerDialog() const;
  Wt::WWidget * CreateNewTestEntranceDialog() const;
  Wt::WWidget * CreateNewTestExerciseDialog() const;
  Wt::WWidget * CreateNewTestFunctionParserDialog() const;
  Wt::WWidget * CreateNewTestGroupWidgetDialog() const;
  Wt::WWidget * CreateNewTestLedDialog() const;
  Wt::WWidget * CreateNewTestNewickVectorDialog() const;
  Wt::WWidget * CreateNewTestQuestionDialog() const;
  Wt::WWidget * CreateNewTestSelectFileDialogDialog() const;
  Wt::WWidget * CreateNewTestServerPusherDialog() const;
  Wt::WWidget * CreateNewTestShapeDialog() const;
  Wt::WWidget * CreateNewTestShinyButtonDialog() const;
  Wt::WWidget * CreateNewTestTimedServerPusherDialog() const;
  Wt::WWidget * CreateNewTestToggleButtonDialog() const;
  Wt::WWidget * CreateNewTestTwoDigitNewickDialog() const;
  Wt::WWidget * CreateNewTicTacToeDialog() const;
  Wt::WWidget * CreateNewTimePollDialog() const;

  ///Create the 'Tools' submenu dialog
  Wt::WWidget * CreateNewToolsDialog();
  Wt::WWidget * CreateNewWelcomeDialog() const;

  void OnMainItemClicked(const ShinyButtonWidget * const widget);
  void OnSubItemClicked(const ShinyButtonWidget * const widget);

  std::vector<Item_t> CreateAboutMenuItems() const;
  std::vector<Item_t> CreateClassesMenuItems() const;
  std::vector<Item_t> CreateGamesMenuItems() const;
  std::vector<Item_t> CreateMainMenuItems() const;
  std::vector<Item_t> CreateProjectsMenuItems() const;
  std::vector<Item_t> CreateToolsMenuItems() const;
};

} //~namespace RichelBilderbeek
} //~namespace ribi

#endif // WTRICHELBILDERBEEKMENUDIALOG_H
