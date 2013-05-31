#ifndef CHESSBOARDWIDGET_H
#define CHESSBOARDWIDGET_H

#include <boost/shared_ptr.hpp>

#include "chessfwd.h"
#include "chesswidget.h"

namespace Chess {

///Chess::BoardWidget is a Chess::Widget to interact with a Chess::Board
struct BoardWidget : public Chess::ChessWidget
{
  BoardWidget(boost::shared_ptr<Chess::Board> board, const Rect& geometry);

  ///Can do a move?
  bool CanDoMove(const Chess::Square& from, const Chess::Square& to) const;
  //bool CanDoMove(const Chess::Move& move) const;

  ///Can the square be selected?
  bool CanSelect(const Chess::Square& square) const;

  ///Respond to a click
  void Click(const Chess::Square& square);


  ///Do a move
  void DoMove(const Chess::Square& from, const Chess::Square& to);

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

  ///The active Player
  Player m_player;

  ///The chessboard
  boost::shared_ptr<Chess::Board> m_board;

  friend void boost::checked_delete<>(BoardWidget* x);
};

} //~ namespace Chess

#endif // CHESSBOARDWIDGET_H
