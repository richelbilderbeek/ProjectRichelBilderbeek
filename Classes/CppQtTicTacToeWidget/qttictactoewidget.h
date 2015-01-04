//---------------------------------------------------------------------------
/*
QtTicTacToeWidget, widget for TicTacToe class
Copyright (C) 2010-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppQtTicTacToeWidget.htm
//---------------------------------------------------------------------------
#ifndef QTTICTACTOEWIDGET_H
#define QTTICTACTOEWIDGET_H

#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include <QWidget>

#include "tictactoefwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace tictactoe {

class QtTicTacToeWidget : public QWidget
{
  Q_OBJECT
public:
  explicit QtTicTacToeWidget(
    const boost::shared_ptr<Ai>& player1,
    const boost::shared_ptr<Ai>& player2,
    QWidget *parent = 0);
  boost::shared_ptr<const Widget> GetWidget() const { return m_widget; }

  ///Called every second, makes the AI do a move
  void OnTimer() noexcept;
  void Restart() noexcept;

  ///mousePressEvent must be public for TicTacToeTest's
  ///virtual mouse clicks
  void mousePressEvent(QMouseEvent *);

  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

  boost::signals2::signal<void(QtTicTacToeWidget*)> m_signal_changed;
  boost::signals2::signal<void(QtTicTacToeWidget*)> m_signal_has_winner;

protected:
  void paintEvent(QPaintEvent *) noexcept;
  void resizeEvent(QResizeEvent *) noexcept;

private:
  const boost::shared_ptr<Ai> m_player1;
  const boost::shared_ptr<Ai> m_player2;

  boost::shared_ptr<Widget> m_widget;

  void OnChanged();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace tictactoe
} //~namespace ribi

#endif // QTTICTACTOEWIDGET_H
