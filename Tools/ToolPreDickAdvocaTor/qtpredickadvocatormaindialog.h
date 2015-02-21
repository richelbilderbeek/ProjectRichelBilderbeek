//---------------------------------------------------------------------------
/*
PreDickAdvocaTor, tool to predict WC scores
Copyright (C) 2010-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolPreDickAdvocaTor.htm
//---------------------------------------------------------------------------
#ifndef QTPREDICKADVOCATORMAINDIALOG_H
#define QTPREDICKADVOCATORMAINDIALOG_H

#include <string>
#include <vector>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "predickadvocatormaindialog.h"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtPreDickAdvocaTorMainDialog;
}

namespace ribi {

class QtPreDickAdvocaTorMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT
public:
  QtPreDickAdvocaTorMainDialog(const int seed, QWidget *parent = 0);
  QtPreDickAdvocaTorMainDialog(const QtPreDickAdvocaTorMainDialog&) = delete;
  QtPreDickAdvocaTorMainDialog& operator=(const QtPreDickAdvocaTorMainDialog&) = delete;
  ~QtPreDickAdvocaTorMainDialog() noexcept;

private:
  Ui::QtPreDickAdvocaTorMainDialog *ui;
  const PreDickAdvocaTorMainDialog m_dialog;
private slots:
  void on_box_left_currentIndexChanged(int index);
  void on_box_right_currentIndexChanged(int index);
  void OnAnyChange();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};


} //~namespace ribi

#endif // QTPREDICKADVOCATORMAINDIALOG_H
