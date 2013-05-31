//---------------------------------------------------------------------------
/*
Loose, reduce an emailaddress to an unknown limited set
Copyright (C) 2010-2013 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolLoose.htm
//---------------------------------------------------------------------------
#ifndef WTLOOSEMAINDIALOG_H
#define WTLOOSEMAINDIALOG_H

#include <string>
#include <vector>

#include <Wt/WContainerWidget>

namespace Wt
{
  struct WImage;
};

struct WtLooseMaindialog : public Wt::WContainerWidget
{
  static const std::vector<std::string> GetAbout();
  static const std::vector<std::string> GetLicence();
  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();
  static const std::vector<std::string> GetWhatsNew();
  WtLooseMaindialog();
  private:
  Wt::WPushButton * const m_button_about;
  Wt::WPushButton * const m_button_check;
  Wt::WPushButton * const m_button_licence;
  Wt::WPushButton * const m_button_whatsnew;
  Wt::WContainerWidget * const m_container;
  Wt::WLineEdit * const m_edit;
  Wt::WImage * const m_image;
  Wt::WText * const m_result;
  Wt::WScrollArea * const m_scroll_area;
  Wt::WTextArea * const m_text_area;
  void onAboutClick();
  void onCheckClick();
  void onLicenceClick();
  void onWhatsNewClick();
};

int StringToMagicInt(const std::string& s);

#endif // WTLOOSEMAINDIALOG_H
