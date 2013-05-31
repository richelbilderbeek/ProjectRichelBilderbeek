//---------------------------------------------------------------------------
/*
TestAsciiArter, tool to test the AsciiArter class
Copyright (C) 2006-2011 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestAsciiArter.htm
//---------------------------------------------------------------------------
#ifndef WTASCIIARTERMAINDIALOG_H
#define WTASCIIARTERMAINDIALOG_H
//---------------------------------------------------------------------------
#include <boost/scoped_ptr.hpp>
//---------------------------------------------------------------------------
#include <Wt/WContainerWidget>
//---------------------------------------------------------------------------
struct AsciiArterMainDialog;
namespace Wt
{
  struct WFileUpload;
  struct WLineEdit;
  struct WTextArea;
  struct WWidget;
}
//---------------------------------------------------------------------------
struct WtAsciiArterMainDialog : public Wt::WContainerWidget
{
  WtAsciiArterMainDialog();

  private:
  boost::scoped_ptr<AsciiArterMainDialog> m_dialog;

  struct Ui
  {
    Ui();
    Wt::WLineEdit * const m_edit_width;
    Wt::WFileUpload * const m_fileupload;
    Wt::WTextArea * const m_text;
  } ui;

  Wt::WWidget * CreateNewAboutDialog() const;
  Wt::WWidget * CreateNewMainDialog();
  Wt::WWidget * CreateNewWelcomeDialog() const;


  void OnAboutClick();
  void OnAnyChange();
  void OnConvertClick();
  void OnEditWidthChange();
  void OnUploadDone();

  void ShowAbout();
  void ShowMain();


  //Returns a Y-X-ordered std::vector of greynesses.
  static const std::vector<std::vector<double> >
    ConvertToGreyYx(const std::string& filename);

};
//---------------------------------------------------------------------------
#endif // WTASCIIARTERMAINDIALOG_H
