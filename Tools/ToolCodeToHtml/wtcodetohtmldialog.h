//---------------------------------------------------------------------------
/*
CodeToHtml, converts C++ code to HTML
Copyright (C) 2010-2015  Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolCodeToHtml.htm
//---------------------------------------------------------------------------
#ifndef WTCODETOHTMLDIALOG_H
#define WTCODETOHTMLDIALOG_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <Wt/WContainerWidget>
#pragma GCC diagnostic pop

struct WtDialWidget;
struct WtCodeToHtmlWidget;

namespace ribi {
namespace c2h {

struct WtDialog : public Wt::WContainerWidget
{
  WtDialog();

  private:
  struct Ui
  {
    Ui();
    Wt::WAnchor * const m_anchor;
    Wt::WTextArea * const m_area_result;
    Wt::WTextArea * const m_area_snippet;
    Wt::WComboBox * const m_box_page_type;
    Wt::WComboBox * const m_box_tech_info;
    Wt::WComboBox * const m_box_content_type;
    Wt::WPushButton * const m_button_convert;
    Wt::WLineEdit * const m_edit_source;
    Wt::WMenu * m_menu; //Needs to be initialized with m_stack
    Wt::WStackedWidget * const m_stack;
  } ui;


  ///Read the text from a Wt::WTextArea and convert it to std::vector<std::string>
  static std::vector<std::string> AreaToVector(const Wt::WTextArea * const area);

  ///Display the HTML code as web page and plain text
  void Display(const std::vector<std::string>& v);

  ///Obtain the selected header type
  //c2h::PageType GetPageType() const;

  ///Obtain the selected technical info type
  //c2h::TechInfoType GetTechInfo() const;

  ///Obtain the selected source type
  //c2h::ContentType GetContentType() const;

  ///Respond to click on Convert button
  void on_button_convert_clicked();

  ///Respond to a change in the source location
  void on_tab_source_currentChanged();

  ///Respond to a change in the edit containing the source file or source folder
  void on_edit_source_textChanged();

};

} //~namespace c2h
} //~namespace ribi

#endif // WTCODETOHTMLDIALOG_H
