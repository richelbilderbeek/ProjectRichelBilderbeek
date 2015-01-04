//---------------------------------------------------------------------------
/*
RichelbilderbeekNlSitemapGenerator, generates the richelbilderbeek.nl sitemap
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
//From http://www.richelbilderbeek.nl/ToolRichelbilderbeekNlSitemapGenerator.htm
//---------------------------------------------------------------------------
#ifndef SITEMAPGENERATORMAINDIALOG_H
#define SITEMAPGENERATORMAINDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtSitemapGeneratorMainDialog;
}

namespace ribi {

class QtSitemapGeneratorMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtSitemapGeneratorMainDialog(QWidget *parent = 0);
  QtSitemapGeneratorMainDialog(const QtSitemapGeneratorMainDialog&);
  QtSitemapGeneratorMainDialog& operator=(const QtSitemapGeneratorMainDialog&);
  ~QtSitemapGeneratorMainDialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent * e);

private:
  Ui::QtSitemapGeneratorMainDialog *ui;

private slots:
  void on_button_start_clicked();

  //From http://www.richelbilderbeek.nl/CppGetCurrentFolder.htm
  static std::string GetCurrentFolder();

  //From http://www.richelbilderbeek.nl/CppGetCurrentFolder.htm
  static std::string GetCurrentFolder(const std::string& s);

  void OnLogMessage(const std::string& msg) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // SITEMAPGENERATORMAINDIALOG_H
