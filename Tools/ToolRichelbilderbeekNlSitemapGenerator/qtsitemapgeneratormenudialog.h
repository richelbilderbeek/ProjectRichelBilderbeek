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
#ifndef QTSITEMAPGENERATORMENUDIALOG_H
#define QTSITEMAPGENERATORMENUDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
class QtSitemapGeneratorMenuDialog;
}

namespace ribi {

class QtSitemapGeneratorMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT
    
public:
  explicit QtSitemapGeneratorMenuDialog(QWidget *parent = 0);
  QtSitemapGeneratorMenuDialog(const QtSitemapGeneratorMenuDialog&) = delete;
  QtSitemapGeneratorMenuDialog& operator=(const QtSitemapGeneratorMenuDialog&) = delete;
  ~QtSitemapGeneratorMenuDialog() noexcept;
    
protected:
  void keyPressEvent(QKeyEvent * event);

private slots:
  void on_button_start_clicked();

  void on_button_about_clicked();

  void on_button_quit_clicked();

private:
  Ui::QtSitemapGeneratorMenuDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTSITEMAPGENERATORMENUDIALOG_H
