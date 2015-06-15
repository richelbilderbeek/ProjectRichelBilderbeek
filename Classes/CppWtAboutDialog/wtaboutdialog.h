//---------------------------------------------------------------------------
/*
WtAboutDialog, Wt dialog for displaying the About class
Copyright (C) 2010-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppWtAboutDialog.htm
//---------------------------------------------------------------------------
#ifndef WTABOUTDIALOG_H
#define WTABOUTDIALOG_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/signals2.hpp>

#include <Wt/WContainerWidget>
#include <Wt/WPushButton>

#include "about.h"
#pragma GCC diagnostic pop

namespace ribi {

struct WtAboutDialog : public Wt::WContainerWidget
{
  explicit WtAboutDialog(const About& about, const bool display_close_button = true);
  WtAboutDialog(const WtAboutDialog&) = delete;
  WtAboutDialog& operator=(const WtAboutDialog&) = delete;

  boost::signals2::signal<void ()> m_signal_close;

  ///Get the version of this class
  static std::string GetVersion();

  ///Get the version history of this class
  static std::vector<std::string> GetVersionHistory();

  ///GetWtVersion returns the version of the currently installed Wt library
  ///From http://www.richelbilderbeek.nl/CppGetWtVersion.htm
  static std::string GetWtVersion();
  private:
  Wt::WPushButton * const m_button_close;
  void OnClose();
};

} //~namespace ribi

#endif // WTABOUTDIALOG_H
