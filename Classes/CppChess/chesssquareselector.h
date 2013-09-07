#ifndef CHESSSQUARESELECTOR_H
#define CHESSSQUARESELECTOR_H

#include <boost/scoped_ptr.hpp>
#include <boost/signals2.hpp>

#include "chesscolor.h"
#include "chessfwd.h"
//#include "chesssquare.h"


namespace ribi {
namespace Chess {

///SquareSelector is the selector of a Chess::BoardWidget
///It consists of an ever-present cursor and a possibly selected square
struct SquareSelector
{
  SquareSelector();

  ///Respond to a click on a certain square
  void Click(
    const Chess::Square& square,
    const bool can_select_square);

  ///Select the square the cursor is on
  void DoSelect();

  ///The initially selected Square
  static boost::shared_ptr<Square> GetInitialSquare();

  ///Obtain the version of this class
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  ///Obtain the location of the cursor
  const boost::shared_ptr<const Square> GetCursor() const { return m_cursor; }

  ///Obtain the location of the cursor
  const boost::scoped_ptr<Square>& GetSelected() const { return m_selected; }

  ///Try to move the cursor down
  void MoveDown();

  ///Try to move the cursor to the left
  void MoveLeft();

  ///Try to move the cursor to the right
  void MoveRight();

  ///Try to move the cursor up
  void MoveUp();

  ///Convert the SquareSelector to a std::string
  const std::string ToStr() const;

  ///Respond to a change in size
  mutable boost::signals2::signal<void ()> m_signal_changed;

  static const Chess::Color m_cursor_color = Color::green;
  static const Chess::Color m_selected_color = Color::red;
  static const Chess::Color m_moves_color = Color::blue;

  private:
  ~SquareSelector() {}

  ///The Square the cursor is.
  ///There will always be a cursor somewhere
  const boost::shared_ptr<Square> m_cursor;

  ///The selected Square, if any
  boost::scoped_ptr<Square> m_selected;

  friend void boost::checked_delete<>(SquareSelector* x);
};

} //~namespace Chess
} //~namespace ribi

#endif // CHESSSQUARESELECTOR_H
