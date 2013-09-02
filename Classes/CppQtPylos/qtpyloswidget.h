//---------------------------------------------------------------------------
/*
PylosWidget, widget to display Pylos class
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
//From http://www.richelbilderbeek.nl/ToolTestPylos.htm
//---------------------------------------------------------------------------
#ifndef QTPYLOSWIDGET_H
#define QTPYLOSWIDGET_H

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/tuple/tuple.hpp>
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

#include <QWidget>

#include "pyloscoordinat.h"
#include "pylosfwd.h"
#include "pylosmove.h"
#include "pyloswinner.h"
#include "qtpylossprites.h"

struct QPaintEvent;
//namespace Pylos { struct Game; }

///PylosWidget is the base class of QtPylosBoardWidget and QtPylosWidget
class QtPylosWidget : public QWidget
{
  Q_OBJECT
public:
  QtPylosWidget();
  virtual ~QtPylosWidget() {}
  ///mouseMoveEvent is public, because
  ///TestPylos must be able to make virtual mouse movements.
  void mouseMoveEvent(QMouseEvent * e);
  ///mousePressEvent is public, because
  ///TestPylos must be able to deliver virtual clicks.
  void mousePressEvent(QMouseEvent*);

  ///CanRemove specifies if current player can remove one or
  ///two marble(s) at the requested position(s).
  virtual bool CanRemove(const std::vector<Pylos::Coordinat>& v) const = 0;

  ///CanSet tests if the current player can be set at the Coordinat
  virtual bool CanSet(const Pylos::Coordinat& c) const = 0;

  ///CanTransfer specifies if current player can transfer
  ///the marble at the specified coordinat for movement
  virtual bool CanTransfer(const Pylos::Coordinat& c) const = 0;

  ///CanTransfer specifies if current player can transfer his marble
  ///to a new, higher position
  virtual bool CanTransfer(
    const Pylos::Coordinat& from,
    const Pylos::Coordinat& to) const = 0;

  ///GetCurrentTurn returns whose turn it is now
  virtual Pylos::Player GetCurrentTurn() const = 0;

  ///GetLayerSize returns how many marbles this is wide/height.
  ///For exaple; layer 0 has 4x4 marbles, so GetLayerSize
  ///will return 4.
  virtual int GetLayerSize(const int layer) const = 0;

  ///MustRemove returns whether the current player
  ///must remove one or two marbles
  virtual Pylos::MustRemoveState GetMustRemove() const = 0;

  ///GetOtherSelectors returns the other selectors' current coodinats
  const std::vector<Pylos::Coordinat>& GetOtherSelectors() const;

  ///GetSelector returns the selector's current coodinat
  const Pylos::Coordinat& GetSelector() const { return m_select; }

  ///Obtain this class its version
  static const std::string GetVersion();

  ///Obtain this class its version history
  static const std::vector<std::string> GetVersionHistory();

  ///Return the possible winner
  virtual Pylos::Winner GetWinner() const = 0;

  ///Remove lets the current player remove one or two marbles
  virtual void Remove(const std::vector<Pylos::Coordinat>& v) = 0;

  ///Set makes current player place his marble
  ///at the specified position. After Set,
  ///GetMustRemove must be called to determine if
  ///the current player must remove some marbles
  virtual void Set(const Pylos::Coordinat& c) = 0;

  ///SetColorSchemeBlackWhite sets the color scheme to black and white.
  void SetColorSchemeBlackWhite();

  ///SetColorSchemeRedBlue sets the color scheme to red and blue.
  void SetColorSchemeRedBlue();

  ///SetTilt sets the tilt of this widget
  void SetTilt(const double tilt);

  ///StartAdvanced cleans the board to start a game
  ///with advanced rules
  virtual void StartAdvanced() = 0;

  ///StartBasic cleans the board to start a game
  ///with basic rules
  virtual void StartBasic() = 0;

  ///Transfer lets current player tranfer his marble to a new, higher position
  virtual void Transfer(
    const Pylos::Coordinat& from,
    const Pylos::Coordinat& to) = 0;


signals:
  ///HasWinner is emitted when a winner is found
  void HasWinner();
  ///SelectorChanged is emitted when the selector is moved
  void SelectorChanged();
  ///DoneMove is emitted when a player has done a successfull move
  void DoneMove();
  ///Toggle is emitted when a marble is (de)selected for something
  void Toggle();

protected:
  ///Draw the Pylos widget
  void paintEvent(QPaintEvent *);

  ///Resize the Pylos widget
  void resizeEvent(QResizeEvent *);

  ///m_other_selectors embodies the coordinats for
  ///- selecting a marble to move to a higher layer
  ///- select one or two marbles for removal
  std::vector<Pylos::Coordinat> m_other_selectors;

  ///The current coordinat of the selector
  Pylos::Coordinat m_select;

  ///All Pylos sprites
  Pylos::QtSprites m_sprites;

  ///The angle which the board is tilted in radians.
  ///0.0*M_PI denotes looking at the board from the top
  ///0.5*M_PI denotes looking from directly above the bottom left position
  double m_tilt;

private:
  ///DeselectRemove remove coordinat c from m_other_selectors,
  ///because the player deselected the marble at
  ///that coordinat
  void DeselectRemove(const Pylos::Coordinat& c);

  ///DrawRemove draws a marble toggled for removal
  void DrawRemove(QPainter& painter, const Pylos::Coordinat& c);

  ///DrawSelect draws the selector
  void DrawSelect(QPainter& painter);

  ///Obtain the PositionState at a certain coordinat
  virtual Pylos::PositionState Get(const Pylos::Coordinat& c) const = 0;

  ///Obtain all Pylos::Coordinat instances at a certain mouse position
  const std::vector<Pylos::Coordinat> GetCoordinats(const int mouse_x, const int mouse_y);

  ///From www.richelbilderbeek.nl/CppGetDistance.htm
  static double GetDistance(const double dx, const double dy);

  ///IsOtherSelector returns if the specified coordinat
  ///is selected for removal
  bool IsOtherSelector(const Pylos::Coordinat& c) const;

  ///MouseLeftClick handles mouse left-clicking.
  void MouseLeftClick();

  ///MouseLeftClickRemove handles mouse left-clicking
  ///during removal state.
  void MouseLeftClickRemove();

  ///MouseLeftClickSelect handles mouse left-clicking
  ///during select state.
  void MouseLeftClickSelect();

  ///MouseRightClick handles mouse right-clicking.
  void MouseRightClick();

  ///MouseMove is the first method called after a
  ///mouse move
  void MouseMove(const int x, const int y);

  ///MouseMoveRemoval handles mouse movement
  ///when player must remove one or two marbles
  void MouseMoveRemoval(const int x, const int y);

  ///MouseMoveSelect handles mouse movement
  ///when player must select either a location to
  ///place a new marble or to select a marble to move
  void MouseMoveSelect(const int x, const int y);

  ///SaveAllSprites saves all sprites used in this game.
  void SaveAllSprites() const;

  ///SetSelector sets the selector coordinat to c
  void SetSelector(const Pylos::Coordinat& c);

  ///Transform a Pylos::Coordinat to a (x,y) position on the widget's canvas
  ///Note: the (x,y) position denotes the center of the marble
  const std::pair<int,int> Transform(const Pylos::Coordinat& c) const;
};

#endif // QTPYLOSWIDGET_H

