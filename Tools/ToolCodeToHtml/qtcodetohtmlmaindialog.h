//---------------------------------------------------------------------------
/*
CodeToHtml, converts C++ code to HTML
Copyright (C) 2010-2013  Richel Bilderbeek

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
#ifndef QTCODETOHTMLMAINDIALOG_H
#define QTCODETOHTMLMAINDIALOG_H

//#include <string>
//#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
//#include "about.h"
//#include "codetohtml.h"
#include "codetohtmlcontenttype.h"
#include "codetohtmlpagetype.h"
#include "codetohtmltechinfotype.h"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

struct QPlainTextEdit;

namespace Ui {
  class QtCodeToHtmlMainDialog;
}

namespace ribi {

class QtCodeToHtmlMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtCodeToHtmlMainDialog(QWidget *parent = 0);
  QtCodeToHtmlMainDialog(const QtCodeToHtmlMainDialog&) = delete;
  QtCodeToHtmlMainDialog& operator=(const QtCodeToHtmlMainDialog&) = delete;
  ~QtCodeToHtmlMainDialog();

protected:
  void keyPressEvent(QKeyEvent *);

private:
  Ui::QtCodeToHtmlMainDialog *ui;

  ///Display the HTML code as web page and plain text
  void Display(const std::vector<std::string>& v);

  ///Convert a QPlainTextEdit to std::vector<std::string>
  static const std::vector<std::string> EditToVector(const QPlainTextEdit * const edit);

private slots:

  ///Obtain the selected header type
  c2h::PageType GetPageType() const;

  ///Obtain the selected technical info type
  c2h::TechInfoType GetTechInfo() const;

  ///Obtain the selected source type
  c2h::ContentType GetContentType() const;

  ///Respond to click on Convert button
  void on_button_convert_clicked();

  void on_tab_source_currentChanged(int index);

  ///Respond to a change in the edit containing the source file or source folder
  void on_edit_source_textChanged(QString );

  #ifndef NDEBUG
  static void Test();
  #endif

};

} //~namespace ribi

#endif // QTCODETOHTMLMAINDIALOG_H
