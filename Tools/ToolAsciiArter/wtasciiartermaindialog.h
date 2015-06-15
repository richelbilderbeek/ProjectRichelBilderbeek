//---------------------------------------------------------------------------
/*
AsciiArter, tool to create ASCII art
Copyright (C) 2006-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolAsciiArter.htm
//---------------------------------------------------------------------------
#ifndef WTASCIIARTERMAINDIALOG_H
#define WTASCIIARTERMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <boost/scoped_ptr.hpp>

#include <Wt/WContainerWidget>
#pragma GCC diagnostic pop

namespace Wt
{
  struct WFileUpload;
  struct WLineEdit;
  struct WTextArea;
  struct WWidget;
}

namespace ribi {

struct AsciiArterMainDialog;

///WtAsciiArterMainDialog displays a AsciiArterMainDialog
struct WtAsciiArterMainDialog : public Wt::WContainerWidget
{
  WtAsciiArterMainDialog();


  private:
  ///The dialog
  ///This dialog may be nullptr, if the user has not supplied
  ///all the arguments needed for its creation
  boost::scoped_ptr<AsciiArterMainDialog> m_dialog;

  //The image its filename
  std::string m_filename;

  ///The ASCII art number of characters per line
  int m_n_cols;

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

} //~namespace ribi

#endif // WTASCIIARTERMAINDIALOG_H
