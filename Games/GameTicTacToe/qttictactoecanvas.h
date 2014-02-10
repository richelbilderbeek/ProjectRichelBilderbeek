#ifndef QTTICTACTOECANVAS_H
#define QTTICTACTOECANVAS_H

#include "qtcanvas.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

namespace ribi {

struct TicTacToeWidget;

struct QtTicTacToeCanvas : public QtCanvas
{
  QtTicTacToeCanvas();

  void keyPressEvent(QKeyEvent *e);


  private:
  const boost::shared_ptr<TicTacToeWidget> m_widget;

  static const boost::shared_ptr<Canvas> CreateCanvas() noexcept;
  static const boost::shared_ptr<TicTacToeWidget> CreateWidget() noexcept;

  void OnChanged();
};

} //~namespace ribi


#endif // QTTICTACTOECANVAS_H
