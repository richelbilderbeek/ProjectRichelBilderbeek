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
#ifndef QTCONNECTTHREEGAMEDIALOG_H
#define QTCONNECTTHREEGAMEDIALOG_H

#include <bitset>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/signals2.hpp>
#pragma GCC diagnostic pop

#include <QDialog>

namespace Ui {
  class QtConnectThreeGameDialog;
}
struct QtConnectThreeWidget;

class QtConnectThreeGameDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtConnectThreeGameDialog(
    QWidget *parent = 0,
    const std::bitset<3>& is_player_human = std::bitset<3>(true));
  boost::signals2::signal<void ()> m_signal_close;


  ~QtConnectThreeGameDialog();

protected:
  void changeEvent(QEvent *e);

public slots:
  void DoComputerTurn();

private:
  Ui::QtConnectThreeGameDialog *ui;
  boost::shared_ptr<QtConnectThreeWidget> m_board;
  const std::bitset<3>& m_is_player_human;
  void OnValidMove();
};

#endif // QTCONNECTTHREEGAMEDIALOG_H
