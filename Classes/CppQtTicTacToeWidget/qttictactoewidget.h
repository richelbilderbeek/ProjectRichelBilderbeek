//---------------------------------------------------------------------------
/*
QtTicTacToeWidget, widget for TicTacToe class
Copyright (C) 2010 Richel Bilderbeek

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
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <string>
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
//---------------------------------------------------------------------------
#include <QWidget>
//---------------------------------------------------------------------------
struct TicTacToe;
//---------------------------------------------------------------------------
class QtTicTacToeWidget : public QWidget
{
  Q_OBJECT
public:
  explicit QtTicTacToeWidget(QWidget *parent = 0);
  const TicTacToe * GetTicTacToe() const { return m_tictactoe.get(); }
  void Restart();

  ///mousePressEvent must be public for TicTacToeTest's
  ///virtual mouse clicks
  void mousePressEvent(QMouseEvent *);

  static const std::string GetVersion() { return "1.0"; }

protected:
  void paintEvent(QPaintEvent *);
  void resizeEvent(QResizeEvent *);

private:
  boost::shared_ptr<TicTacToe> m_tictactoe;

signals:
  void hasWinner();
  void stateChanged();
public slots:

};
//---------------------------------------------------------------------------
#endif // QTTICTACTOEWIDGET_H
