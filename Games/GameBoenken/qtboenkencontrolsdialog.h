//---------------------------------------------------------------------------
/*
Boenken. A multiplayer soccer/billiards game.
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
//From http://www.richelbilderbeek.nl/GameBoenken.htm
//---------------------------------------------------------------------------
#ifndef QTBOENKENCONTROLSDIALOG_H
#define QTBOENKENCONTROLSDIALOG_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"

#include "boenkencontrols.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtBoenkenControlsDialog;
}

namespace ribi {

///QtBoenkenControlsDialog
///
///This dialog connects player names to their controls
///(but it does not connect sprites to their controllers,
///this is what DialogPlayers is for)
class QtBoenkenControlsDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtBoenkenControlsDialog(QWidget *parent = 0);
  QtBoenkenControlsDialog(const QtBoenkenControlsDialog&) = delete;
  QtBoenkenControlsDialog& operator=(const QtBoenkenControlsDialog&) = delete;
  ~QtBoenkenControlsDialog() noexcept;

  Boenken::Controls GetControls() const noexcept;

private:
  Ui::QtBoenkenControlsDialog *ui;
  std::vector<int> m_keys_accel;
  std::vector<int> m_keys_turn;

private slots:
  void onAccelerate1() noexcept;
  void onAccelerate2() noexcept;
  void onTurn1() noexcept;
  void onTurn2() noexcept;
  void showKeys() noexcept;

  std::vector<int> getKeysAccel() const noexcept;
  std::vector<int> getKeysTurn() const noexcept;
  std::vector<std::string> getNames() const noexcept;
};

} //~namespace ribi

#endif // QTBOENKENCONTROLSDIALOG_H
