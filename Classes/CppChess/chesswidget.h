#ifndef CHESSWIDGET_H
#define CHESSWIDGET_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/checked_delete.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>

#include "chessfwd.h"
#include "widget.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace Chess {

///Chess::ChessWidget is a Widget to interact with a Chess class:
///Where the Chess::Board is very picky about valid moves,
///the Chess::ChessWidget enables simple interaction with it
///Note the name, which is to prevent conflict with the Widget class
struct ChessWidget : public ribi::Widget
{
  enum class Key { up, down, left, right, select };

  ///Emit this signal when the chessboard changes
  mutable boost::signals2::signal<void ()> m_signal_graphic_changed;

  ChessWidget(const Rect& geometry);

  virtual ~ChessWidget() noexcept;

  ///Can do a move?
  virtual bool CanDoMove(
    const boost::shared_ptr<const Square> from,
    const boost::shared_ptr<const Square> to) const noexcept = 0;

  ///Respond to a click
  ///Note: originally, this method was called Click, but it conflicted with Click(const Square&) :-(
  void ClickPixel(const int x, const int y);

  ///Do a move
  virtual void DoMove(
    const boost::shared_ptr<const Square> from,
    const boost::shared_ptr<const Square> to) = 0;

  ///Obtain the SquareSelector
  boost::scoped_ptr<Chess::SquareSelector>& GetSelector() { return m_selector; }

  ///Obtain the SquareSelector
  const boost::scoped_ptr<Chess::SquareSelector>& GetSelector() const { return m_selector; }

  ///Obtain the version of this class
  static std::string GetVersion();

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory();

  ///Respond to a key being pressed
  void PressKey(const Chess::ChessWidget::Key key);

  ///Test this class
  static void Test() noexcept;

  ///The Selector (a cursor and possibly a selected square)
  boost::scoped_ptr<Chess::SquareSelector> m_selector;

  ///Respond to a click, transformed click coordinats to a square
  virtual void Click(const boost::shared_ptr<const Chess::Square> square) = 0;

  ///OnChanged is called when the BoardWidget is changed and needs a repaint.
  ///BoardWidget requests for a repaint by emitting m_signal_board_changed
  void OnChanged() const;

  friend void boost::checked_delete<>(ChessWidget* x);
  friend class boost::detail::sp_ms_deleter<      ChessWidget>;
  friend class boost::detail::sp_ms_deleter<const ChessWidget>;

};

} //~namespace Chess
} //~namespace ribi

#endif // CHESSWIDGET_H
