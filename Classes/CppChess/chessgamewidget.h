#ifndef CHESSGAMEWIDGET_H
#define CHESSGAMEWIDGET_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>

//#include "chessboard.h"
#include "chessfwd.h"
#include "chesswidget.h"
//struct Rect;
#pragma GCC diagnostic pop

namespace ribi {

namespace Chess {

///Chess::GameWidget is a Chess::Widget to interact with a Chess::Game
struct GameWidget : public Chess::ChessWidget
{
  GameWidget(boost::shared_ptr<Chess::Game> game, const Rect& geometry);

  ///Can do a move?
  bool CanDoMove(
    const boost::shared_ptr<const Square> from,
    const boost::shared_ptr<const Square> to
  ) const noexcept;

  ///Respond to a click
  void Click(const boost::shared_ptr<const Square> square);

  ///Do a move
  void DoMove(
    const boost::shared_ptr<const Square> from,
    const boost::shared_ptr<const Square> to
  );

  ///Get the Chess::Board this Chess::Widget works on
  const boost::shared_ptr<Chess::Game> GetGame() const { return m_game; }

  ///Test this class
  static void Test() noexcept;

  private:
  ~GameWidget() {}

  ///The chessboard
  boost::shared_ptr<Chess::Game> m_game;

  friend void boost::checked_delete<>(GameWidget* x);
};

} //~ namespace Chess
} //~ namespace ribi

#endif // CHESSGAMEWIDGET_H
