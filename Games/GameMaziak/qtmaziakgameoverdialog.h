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
#ifndef QTMAZIAKGAMEOVERDIALOG_H
#define QTMAZIAKGAMEOVERDIALOG_H

#include <boost/shared_ptr.hpp>
#include <QDialog>

struct QTimer;

namespace Ui {
  class QtMaziakGameOverDialog;
}

namespace ribi {

class QtMaziakGameOverDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtMaziakGameOverDialog(QWidget *parent = 0);
  ~QtMaziakGameOverDialog();

protected:
  void changeEvent(QEvent *e);
  void paintEvent(QPaintEvent*);
  void mousePressEvent(QMouseEvent*);
  void keyPressEvent(QKeyEvent*);

private:
  Ui::QtMaziakGameOverDialog *ui;
  boost::shared_ptr<QTimer> m_timer;
  bool m_allow_close;

  private slots:
  void onTimer();

};

} //~namespace ribi

#endif // QTMAZIAKGAMEOVERDIALOG_H
