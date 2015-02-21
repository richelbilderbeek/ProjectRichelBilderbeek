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
#ifndef QTMAZIAKGAMEWONDIALOG_H
#define QTMAZIAKGAMEWONDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

struct QTimer;

namespace Ui {
  class QtMaziakGameWonDialog;
}

namespace ribi {

class QtMaziakGameWonDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtMaziakGameWonDialog(QWidget *parent = 0);
  QtMaziakGameWonDialog(const QtMaziakGameWonDialog&) = delete;
  QtMaziakGameWonDialog& operator=(const QtMaziakGameWonDialog&) = delete;
  ~QtMaziakGameWonDialog() noexcept;

protected:
  void paintEvent(QPaintEvent*);
  void mousePressEvent(QMouseEvent*);
  void keyPressEvent(QKeyEvent*);

private:
  Ui::QtMaziakGameWonDialog *ui;
  boost::shared_ptr<QTimer> m_timer;
  bool m_allow_close;

  private slots:
  void onTimer();
};

} //~namespace ribi

#endif // QTMAZIAKGAMEWONDIALOG_H
