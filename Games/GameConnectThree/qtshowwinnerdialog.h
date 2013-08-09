//---------------------------------------------------------------------------
/*
GameConnectThree, connect-three game
Copyright (C) 2010-2013 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/GameConnectThree.htm
//---------------------------------------------------------------------------
#ifndef QTSHOWWINNERDIALOG_H
#define QTSHOWWINNERDIALOG_H

#include <string>

#include <QDialog>

namespace Ui {
  class QtShowWinnerDialog;
}

class QtShowWinnerDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtShowWinnerDialog(
    const std::string& filename,
    const std::string& winner_text,
    QWidget *parent = 0);
  ~QtShowWinnerDialog();
  void SetPixmap();

private:
  Ui::QtShowWinnerDialog *ui;
};

#endif // QTSHOWWINNERDIALOG_H
