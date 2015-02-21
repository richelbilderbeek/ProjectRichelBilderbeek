//---------------------------------------------------------------------------
/*
GameConnectThree, connect-three game
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
//From http://www.richelbilderbeek.nl/GameConnectThree.htm
//---------------------------------------------------------------------------
#ifndef QTSHOWWINNERDIALOG_H
#define QTSHOWWINNERDIALOG_H

#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtShowWinnerDialog;
}

namespace ribi {
namespace con3 {

class QtShowWinnerDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtShowWinnerDialog(
    const std::string& filename,
    const std::string& winner_text,
    QWidget *parent = 0) noexcept;
  QtShowWinnerDialog(const QtShowWinnerDialog&) = delete;
  QtShowWinnerDialog& operator=(const QtShowWinnerDialog&) = delete;
  ~QtShowWinnerDialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent *) noexcept;

private:
  Ui::QtShowWinnerDialog *ui;
};

} //~namespace con3
} //~namespace ribi

#endif // QTSHOWWINNERDIALOG_H
