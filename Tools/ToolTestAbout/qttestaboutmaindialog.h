//---------------------------------------------------------------------------
/*
TestAbout, tests the About classes
Copyright (C) 2012-2013 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestAbout.htm
//---------------------------------------------------------------------------
#ifndef QTTESTABOUTMAINDIALOG_H
#define QTTESTABOUTMAINDIALOG_H

#include <QDialog>

namespace Ui {
  class QtTestAboutMainDialog;
}

namespace ribi {

class QtTestAboutMainDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtTestAboutMainDialog(QWidget *parent = 0);
  ~QtTestAboutMainDialog();

private slots:
  void on_button_about_clicked();

  void on_button_quit_clicked();

private:
  Ui::QtTestAboutMainDialog *ui;

  ///Obtain this class its version
  static const std::string GetVersion();

  ///Obtain this class its version history
  static const std::vector<std::string> GetVersionHistory();
};

} //~namespace ribi

#endif // QTTESTABOUTMAINDIALOG_H
