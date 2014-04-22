#ifndef CHESSSQUARESELECTOR_H
#define CHESSSQUARESELECTOR_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/scoped_ptr.hpp>
#include <boost/signals2.hpp>

#include "chesscolor.h"
#include "chessfwd.h"
//#include "chesssquare.h"

#pragma GCC diagnostic pop

namespace ribi {
namespace Chess {

///SquareSelector is the selector of a Chess::BoardWidget
///It consists of an ever-present cursor and a possibly selected square
struct SquareSelector
{
  SquareSelector();

  ///Respond to a click on a certain square
  void Click(
    const boost::shared_ptr<const Square> square,
    const bool can_select_square);

  ///Select the square the cursor is on
  void DoSelect();

  ///The initially selected Square
  static boost::shared_ptr<Square> GetInitialSquare() noexcept;

  ///Obtain the version of this class
  static std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Obtain the location of the cursor
  const boost::shared_ptr<const Square> GetCursor() const noexcept { return m_cursor; }

  ///Obtain the location of the cursor
  const boost::shared_ptr<const Square> GetSelected() const noexcept;

  ///Try to move the cursor down
  void MoveDown() noexcept;

  ///Try to move the cursor to the left
  void MoveLeft() noexcept;

  ///Try to move the cursor to the right
  void MoveRight() noexcept;

  ///Try to move the cursor up
  void MoveUp() noexcept;

  ///Convert the SquareSelector to a std::string
  std::string ToStr() const noexcept;

  ///Respond to a change in size
  mutable boost::signals2::signal<void ()> m_signal_changed;

  static const Chess::Color m_cursor_color = Color::green;
  static const Chess::Color m_selected_color = Color::red;
  static const Chess::Color m_moves_color = Color::blue;

  private:
  ~SquareSelector() {}

  ///The Square the cursor is.
  ///There will always be a cursor somewhere
  boost::shared_ptr<const Square> m_cursor;

  ///The selected Square, if any
  boost::shared_ptr<const Square> m_selected;

  friend void boost::checked_delete<>(SquareSelector* x);
};

} //~namespace Chess
} //~namespace ribi

#endif // CHESSSQUARESELECTOR_H
