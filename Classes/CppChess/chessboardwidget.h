#ifndef CHESSBOARDWIDGET_H
#define CHESSBOARDWIDGET_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>

#include "chessfwd.h"
#include "chesswidget.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace Chess {

///Chess::BoardWidget is a Chess::Widget to interact with a Chess::Board
struct BoardWidget : public Chess::ChessWidget
{
  BoardWidget(boost::shared_ptr<Chess::Board> board, const Rect& geometry);

  ///Can do a move?
  bool CanDoMove(
    const boost::shared_ptr<const Chess::Square> from,
    const boost::shared_ptr<const Chess::Square> to) const noexcept;
  //bool CanDoMove(const Chess::Move& move) const;

  ///Can the square be selected?
  bool CanSelect(const boost::shared_ptr<const Chess::Square> square) const noexcept;

  ///Respond to a click
  void Click(const boost::shared_ptr<const Chess::Square> square) noexcept;

  ///Do a move
  void DoMove(const boost::shared_ptr<const Chess::Square> from, const boost::shared_ptr<const Chess::Square> to);

  ///Get which Player is active
  Player GetActivePlayer() const { return m_player; }

  ///Get the Chess::Board this Chess::Widget works on
  const boost::shared_ptr<Chess::Board> GetBoard() const { return m_board; }

  ///Set which Player is active
  void SetActivePlayer(const Player player);

  ///Test this class
  static void Test();

  private:

  ~BoardWidget() {}

  ///The chessboard
  boost::shared_ptr<Chess::Board> m_board;

  ///The active Player
  Player m_player;

  friend void boost::checked_delete<>(BoardWidget* x);
};

} //~namespace Chess
} //~namespace ribi

#endif // CHESSBOARDWIDGET_H
