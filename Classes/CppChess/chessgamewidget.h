#ifndef CHESSGAMEWIDGET_H
#define CHESSGAMEWIDGET_H

#include <boost/shared_ptr.hpp>

//#include "chessboard.h"
#include "chessfwd.h"
#include "chesswidget.h"
//struct Rect;

namespace Chess {

///Chess::GameWidget is a Chess::Widget to interact with a Chess::Game
struct GameWidget : public Chess::ChessWidget
{
  GameWidget(boost::shared_ptr<Chess::Game> game, const Rect& geometry);

  ///Can do a move?
  bool CanDoMove(const Chess::Square& from, const Chess::Square& to) const;

  ///Respond to a click
  void Click(const Chess::Square& square);

  ///Do a move
  void DoMove(const Chess::Square& from, const Chess::Square& to);

  ///Get the Chess::Board this Chess::Widget works on
  const boost::shared_ptr<Chess::Game> GetGame() const { return m_game; }

  ///Test this class
  static void Test();

  private:
  ~GameWidget() {}

  ///The chessboard
  boost::shared_ptr<Chess::Game> m_game;

  friend void boost::checked_delete<>(GameWidget* x);
};

} //~ namespace Chess

#endif // CHESSGAMEWIDGET_H
