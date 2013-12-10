//---------------------------------------------------------------------------
/*
Maziak, a simple maze game
Copyright (C) 2007-2012 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/GameMaziak.htm
//---------------------------------------------------------------------------
#ifndef QTMAZIAKMENUDIALOG_H
#define QTMAZIAKMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

struct QKeyPressEvent;
struct QMouseEvent;
struct QPaintEvent;

namespace Ui {
  class QtMaziakMenuDialog;
}

namespace ribi {

class QtMaziakMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtMaziakMenuDialog(QWidget *parent = 0);
  QtMaziakMenuDialog(const QtMaziakMenuDialog&) = delete;
  QtMaziakMenuDialog& operator=(const QtMaziakMenuDialog&) = delete;
  ~QtMaziakMenuDialog() noexcept;

private:
  Ui::QtMaziakMenuDialog *ui;
  enum Difficulty { easy, medium, hard } m_difficulty;
  int getMazeSize() const;

  void keyPressEvent(QKeyEvent * event);
  void mousePressEvent(QMouseEvent * event);
  void paintEvent(QPaintEvent*);
  void onStart();
  void onInstructions();
  void onAbout();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTMAZIAKMENUDIALOG_H
