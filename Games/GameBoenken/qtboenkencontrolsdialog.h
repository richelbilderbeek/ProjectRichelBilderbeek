//---------------------------------------------------------------------------
/*
Boenken. A multiplayer soccer/billiards game.
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
//From http://www.richelbilderbeek.nl/GameBoenken.htm
//---------------------------------------------------------------------------
#ifndef QTBOENKENCONTROLSDIALOG_H
#define QTBOENKENCONTROLSDIALOG_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QDialog>

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
class QtBoenkenControlsDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtBoenkenControlsDialog(QWidget *parent = 0);
  QtBoenkenControlsDialog(const QtBoenkenControlsDialog&) = delete;
  QtBoenkenControlsDialog& operator=(const QtBoenkenControlsDialog&) = delete;
  ~QtBoenkenControlsDialog() noexcept;

  Boenken::Controls GetControls() const;

private:
  Ui::QtBoenkenControlsDialog *ui;
  std::vector<int> m_keys_accel;
  std::vector<int> m_keys_turn;

private slots:
  void onAccelerate1();
  void onAccelerate2();
  void onTurn1();
  void onTurn2();
  void showKeys();

  std::vector<int> getKeysAccel() const;
  std::vector<int> getKeysTurn() const;
  std::vector<std::string> getNames() const;
};

} //~namespace ribi

#endif // QTBOENKENCONTROLSDIALOG_H
