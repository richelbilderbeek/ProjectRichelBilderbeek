//---------------------------------------------------------------------------
/*
Maziak, a simple maze game
Copyright (C) 2007-2015 Richel Bilderbeek

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
#ifndef QTMAZIAKMENUDIALOG2_H
#define QTMAZIAKMENUDIALOG2_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qthideandshowdialog.h"
#include "maziakdifficulty.h"
#pragma GCC diagnostic pop

struct QKeyPressEvent;
struct QMouseEvent;
struct QPaintEvent;

namespace Ui {
  class QtMaziakMenuDialog2;
}

namespace ribi {
namespace maziak {

class QtMaziakMenuDialog2 : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtMaziakMenuDialog2(QWidget *parent = 0);
  QtMaziakMenuDialog2(const QtMaziakMenuDialog2&) = delete;
  QtMaziakMenuDialog2& operator=(const QtMaziakMenuDialog2&) = delete;
  ~QtMaziakMenuDialog2() noexcept;

private:
  Ui::QtMaziakMenuDialog2 *ui;
  int GetMazeSize() const;
  Difficulty m_difficulty;
  void keyPressEvent(QKeyEvent * event);
  void mousePressEvent(QMouseEvent * event);
  void paintEvent(QPaintEvent*);
  void OnStart();
  void OnInstructions();
  void OnAbout();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace maziak
} //~namespace ribi

#endif // QTMAZIAKMENUDIALOG2_H
