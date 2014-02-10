#ifndef TICTACTOEWIDGET_H
#define TICTACTOEWIDGET_H

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#pragma GCC diagnostic pop


namespace ribi {

struct TextCanvas;
struct TicTacToe;

struct TicTacToeWidget
{
  enum class Key { up, right, down, left, select };

  TicTacToeWidget();

  void PressKey(const Key key);

  const boost::shared_ptr<TextCanvas> ToTextCanvas() const noexcept;

  ///Signal emitted when the widget is changed
  boost::signals2::signal<void ()> m_signal_changed;

  private:

  const boost::shared_ptr<TicTacToe> m_tictactoe;

  int m_x;
  int m_y;

};

} //~namespace ribi


#endif // TICTACTOEWIDGET_H
