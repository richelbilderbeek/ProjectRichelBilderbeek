//---------------------------------------------------------------------------
/*
WtChessBoardWidget, Wt widget for displaying the Chess::Board class
Copyright (C) 2011 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppWtChessBoardWidget.htm
//---------------------------------------------------------------------------
#ifndef WTCHESSBOARDWIDGET_H
#define WTCHESSBOARDWIDGET_H
//---------------------------------------------------------------------------
#include "chessboardwidget.h"
#include "chessfwd.h"
//---------------------------------------------------------------------------
#include <string>
#include <vector>
//---------------------------------------------------------------------------
#include <boost/signals2.hpp>
//---------------------------------------------------------------------------
#include <Wt/WPaintDevice>
#include <Wt/WPaintedWidget>
//---------------------------------------------------------------------------
namespace Chess { struct WtResources; }
namespace Wt { struct WMouseEventEvent; }
namespace Wt { struct WPainter; }
//---------------------------------------------------------------------------
///WtChessBoardWidget displays a Chess::Board (with a ChessBoardWidget in between)
struct WtChessBoardWidget : public Wt::WPaintedWidget
{
  ///A WtChessBoardWidget is created by its width and height
  WtChessBoardWidget(const int width, const int height);

  ///Draw a ChessBoard from a BoardWidget
  static void DrawChessBoard(
    Wt::WPainter& painter,
    const Chess::BoardWidget * const widget);

  ///Draw a ChessBoard
  static void DrawChessBoard(
    Wt::WPainter& painter,
    const int left, const int top,
    const int width, const int height,
    const Chess::Board * const board);


  ///Obtain a read-only pointer to the Chess::Board
  const Chess::BoardWidget * GetWidget() const { return m_widget.get(); }

  ///Obtain a read-and-write pointer to the Chess::Board
  Chess::BoardWidget * GetWidget() { return m_widget.get(); }

  ///Signal that is emitted when a WtChessBoardWidget is changed
  mutable boost::signals2::signal<void ()> m_signal_changed;

  ///Obtain the WtChessBoardWidget its version
  static const std::string GetVersion();

  ///Obtain the WtChessBoardWidget its version history
  static const std::vector<std::string> GetVersionHistory();

  protected:
  ///Paint the WtMysteryMachineWidget
  void paintEvent(Wt::WPaintDevice *paintDevice);

  private:

  ///The resources used
  const boost::scoped_ptr<const Chess::WtResources> m_resources;

  ///The Chess::Board
  boost::scoped_ptr<Chess::BoardWidget> m_widget;


  ///Repaint the WtChessBoardWidget
  void DoRepaint();

  ///Respond to mouse click
  void OnClicked(const Wt::WMouseEvent& e);

  ///OnResize is called when the geometry of the widget is changed
  void OnResize();

  ///Wt resize: hide it from sight
  void resize(const Wt::WLength& width, const Wt::WLength& height);

  ///Respond to mouse click
  //void OnClicked(const Wt::WMouseEvent& e);
};
//---------------------------------------------------------------------------
#endif // QTCHESSBOARDWIDGET_H
