//---------------------------------------------------------------------------
/*
MusicTheory, tool for visualizing my music theory
Copyright (C) 2012-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolMusicTheory.htm
//---------------------------------------------------------------------------
#ifndef QTMUSICTHEORYMENUDIALOG_H
#define QTMUSICTHEORYMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtMusicTheoryMenuDialog;
}

namespace ribi {

class QtMusicTheoryMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtMusicTheoryMenuDialog(QWidget *parent = 0);
  QtMusicTheoryMenuDialog(const QtMusicTheoryMenuDialog&) = delete;
  QtMusicTheoryMenuDialog& operator=(const QtMusicTheoryMenuDialog&) = delete;
  ~QtMusicTheoryMenuDialog() noexcept;

private:
  Ui::QtMusicTheoryMenuDialog *ui;

private slots:
  void on_button_about_clicked();
  void on_button_quit_clicked();
  void on_button_start_singlescale_clicked();
  void on_button_start_multiscale_clicked();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTMUSICTHEORYMENUDIALOG_H
