//---------------------------------------------------------------------------
/*
GTST, Game Theory Server
Copyright (C) 2011-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ProjectGtst.htm
//---------------------------------------------------------------------------
#ifndef PROJECTGTSTMENUDIALOG_H
#define PROJECTGTSTMENUDIALOG_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/checked_delete.hpp>

//#include <boost/shared_ptr.hpp>
//#include <boost/signals2.hpp>

#include <Wt/WContainerWidget>
#include <Wt/WPushButton>

#include "about.h"

#include "gtstforward_declarations.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace gtst {

///\brief
///The main menu dialog
struct MenuDialog : public Wt::WContainerWidget
{
  ///Create a MenuDialog using one IP address per Participant
  MenuDialog(const SafeIpAddress * const ip_address);
  MenuDialog(const MenuDialog&) = delete;
  MenuDialog& operator=(const MenuDialog&) = delete;

  private:
  ~MenuDialog() {}
  friend void boost::checked_delete<>(MenuDialog*);

  ///Create the WtAboutDialog
  WtAboutDialog * CreateNewAboutDialog() const;

  ///Create a new welcome dialog
  Wt::WContainerWidget * CreateNewWelcomeDialog(
    const SafeIpAddress * const ip_address) const;

  ///Create a new 'About the experiment' dialog
  Wt::WContainerWidget * CreateNewAboutTheExperimentDialog() const;

  ///Create a new 'About the experiment | Experiment flow' dialog
  Wt::WContainerWidget * CreateNewAboutTheExperimentFlowDialog() const;

  ///Create a new 'About the experiment | General' dialog
  Wt::WContainerWidget * CreateNewAboutTheExperimentGeneralDialog() const;

  ///Create a new 'About the experiment | Parameters' dialog
  Wt::WContainerWidget * CreateNewAboutTheExperimentParametersDialog() const;

  Server * const m_server;

  public:
  ///Get the About
  static const About GetAbout();

  ///Get the current version
  static std::string GetVersion();

  ///Get the program's version history
  static std::vector<std::string> GetVersionHistory();

};

} //~namespace gtst
} //~namespace ribi

#endif // MENUDIALOG_H
