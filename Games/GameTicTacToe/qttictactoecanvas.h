#ifndef QTTICTACTOECANVAS_H
#define QTTICTACTOECANVAS_H

#ifdef SUPPORT_RETRO_VERSION_OF_TICTACTOE_AGAIN_20150918
//#include "qtcanvas.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>

#include "tictactoefwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace tictactoe {

struct QtTicTacToeCanvas : public QtCanvas
{
  QtTicTacToeCanvas();

  void keyPressEvent(QKeyEvent *e);


  private:
  const boost::shared_ptr<Widget> m_widget;

  static const boost::shared_ptr<Canvas> CreateCanvas() noexcept;
  static const boost::shared_ptr<Widget> CreateWidget() noexcept;

  void OnChanged();
};

} //~namespace tictactoe
} //~namespace ribi

#endif // SUPPORT_RETRO_VERSION_OF_TICTACTOE_AGAIN_20150918

#endif // QTTICTACTOECANVAS_H
