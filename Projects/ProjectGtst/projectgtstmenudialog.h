//---------------------------------------------------------------------------
/*
GTST, Game Theory Server
Copyright (C) 2011 Richel Bilderbeek

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
//---------------------------------------------------------------------------
#include <string>
#include <vector>
//---------------------------------------------------------------------------
#include <boost/checked_delete.hpp>
#include <boost/noncopyable.hpp>
//#include <boost/shared_ptr.hpp>
//#include <boost/signals2.hpp>
//---------------------------------------------------------------------------
#include <Wt/WContainerWidget>
#include <Wt/WPushButton>
//---------------------------------------------------------------------------
#include "about.h"
//---------------------------------------------------------------------------
#include "forward_declarations.h"
//---------------------------------------------------------------------------
namespace ProjectGtst {
//---------------------------------------------------------------------------
///\brief
///The main menu dialog
struct MenuDialog : public Wt::WContainerWidget
{
  ///Create a MenuDialog using one IP address per Participant
  MenuDialog(const SafeIpAddress * const ip_address);

  private:
  ///\brief Only allow a Boost smart pointer to delete WtMenuDialog
  ///
  ///This prevents the following trouble,
  ///cited from http://www.boost.org/libs/utility/checked_delete.html:
  ///The C++ Standard allows, in 5.3.5/5, pointers to incomplete
  ///class types to be deleted with a delete-expression.
  ///When the class has a non-trivial destructor, or a class-specific operator
  ///delete, the behavior is undefined. Some compilers issue a warning when an
  ///incomplete type is deleted, but unfortunately, not all do, and programmers
  ///sometimes ignore or disable warnings.
  ~MenuDialog() {}
  ///Only allow a Boost smart pointer to delete WtMenuDialog
  //Template syntax from Herb Sutter. Exceptional C++ style. 2005. ISBN: 0-201-76042-8. Item 8: 'Befriending templates'.
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
  static const std::string GetVersion();

  ///Get the program's version history
  static const std::vector<std::string> GetVersionHistory();

};
//---------------------------------------------------------------------------
}; //~namespace ProjectGtst
//---------------------------------------------------------------------------
#endif // MENUDIALOG_H
