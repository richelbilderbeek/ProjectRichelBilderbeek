//---------------------------------------------------------------------------
/*
BeerWanter. A simple game.
Copyright (C) 2005-2012 Richel Bilderbeek

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
//From hhtp://www.richelbilderbeek.nl/GameBeerWanter.htm
//---------------------------------------------------------------------------
#ifndef QTBEERWANTERMENUDIALOG_H
#define QTBEERWANTERMENUDIALOG_H

#include <QDialog>

namespace Ui {
class QtBeerWanterMenuDialog;
}

class QtBeerWanterMenuDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtBeerWanterMenuDialog(QWidget *parent = 0);
  ~QtBeerWanterMenuDialog();

private slots:

  void on_button_start_clicked();

  void on_button_about_clicked();

  void on_button_quit_clicked();

private:
  Ui::QtBeerWanterMenuDialog *ui;
};

#endif // QTBEERWANTERMENUDIALOG_H
