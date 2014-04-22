//---------------------------------------------------------------------------
/*
QtChessBoardWidget, Qt widget for displaying the Chess::Board class
Copyright (C) 2011-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppQtChessBoardWidget.htm
//---------------------------------------------------------------------------
#ifndef QTCHESSBOARDWIDGET_H
#define QTCHESSBOARDWIDGET_H

//#include "chessfwd.h"

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/signals2.hpp>

#include <QWidget>

#include "chessboardwidget.h"    //For MOC
#include "chesssquare.h"         //For MOC
#include "chesssquareselector.h" //For MOC
#include "qtchessresources.h"    //For MOC
#pragma GCC diagnostic pop

namespace ribi {
namespace Chess {

///QtChessBoardWidget displays a Chess::Board (with a ChessBoardWidget in between)
struct QtChessBoardWidget : public QWidget
{
  Q_OBJECT

  public:

  explicit QtChessBoardWidget(QWidget *parent = 0);

  ///A QtChessBoardWidget is created by its width and height
  QtChessBoardWidget(const int width, const int height,
    QWidget *parent = 0);

  ///Draw a ChessBoard from a BoardWidget
  static void DrawChessBoard(
    QPainter& painter,
    const Chess::BoardWidget * const widget);

  ///Draw a ChessBoard
  static void DrawChessBoard(
    QPainter& painter,
    const int left, const int top,
    const int width, const int height,
    const Chess::Board * const board);


  ///Obtain a read-only pointer to the Chess::Board
  const Chess::BoardWidget * GetWidget() const { return m_widget.get(); }

  ///Obtain a read-and-write pointer to the Chess::Board
  Chess::BoardWidget * GetWidget() { return m_widget.get(); }

  ///Signal that is emitted when a QtChessBoardWidget is changed
  mutable boost::signals2::signal<void ()> m_signal_changed;

  ///Obtain the QtChessBoardWidget its version
  static std::string GetVersion();

  ///Obtain the QtChessBoardWidget its version history
  static std::vector<std::string> GetVersionHistory();

  protected:

  ///Respond to a key press
  void keyPressEvent(QKeyEvent *);

  ///Respond to mouse clicks
  void mousePressEvent(QMouseEvent *);

  ///Paint the QtChessBoardWidget
  void paintEvent(QPaintEvent *);

  ///Resize the QtChessBoardWidget
  void resizeEvent(QResizeEvent *);

  private:

  ///The resources used
  const boost::scoped_ptr<const Chess::QtResources> m_resources;

  ///The Chess::Board
  boost::scoped_ptr<Chess::BoardWidget> m_widget;


  ///Repaint the QtChessBoardWidget
  void DoRepaint();

  static void Test() noexcept;
  ///Respond to mouse click
  //void OnClicked(const Wt::WMouseEvent& e);
};

} //~namespace Chess
} //~namespace ribi

#endif // QTCHESSBOARDWIDGET_H
