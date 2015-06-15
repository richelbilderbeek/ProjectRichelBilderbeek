//---------------------------------------------------------------------------
/*
WtTestTwoDigitNewickDialog, Wt dialog to test the TwoDigitNewick class
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
//From http://www.richelbilderbeek.nl/ToolTestTwoDigitNewick.htm
//---------------------------------------------------------------------------
#ifndef WTTESTTWODIGITNEWICKDIALOG_H
#define WTTESTTWODIGITNEWICKDIALOG_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <boost/signals2.hpp>

#include <Wt/WContainerWidget>
#include <Wt/WPushButton>
#include <Wt/WTextArea>

#include "about.h"
#pragma GCC diagnostic pop

namespace ribi {

struct WtTestTwoDigitNewickDialog : public Wt::WContainerWidget
{
  WtTestTwoDigitNewickDialog();
  WtTestTwoDigitNewickDialog(const WtTestTwoDigitNewickDialog&) = delete;
  WtTestTwoDigitNewickDialog& operator=(const WtTestTwoDigitNewickDialog&) = delete;

  boost::signals2::signal<void ()> m_signal_about;
  boost::signals2::signal<void ()> m_signal_any_change;
  static const About GetAbout();
  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();
  private:
  Wt::WLineEdit * const m_edit_newick;
  Wt::WLineEdit * const m_edit_password;
  Wt::WLineEdit * const m_edit_theta;
  Wt::WTextArea * const m_text;

  void OnAbout();
  void OnCalculate();
};

} //~namespace ribi

#endif // WTTESTTWODIGITNEWICKDIALOG_H
