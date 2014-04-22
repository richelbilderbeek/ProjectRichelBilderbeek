#ifndef QTXENONZEROCANVAS_H
#define QTXENONZEROCANVAS_H

#include <bitset>

#include "qtcanvas.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

namespace ribi {

struct TextCanvas;

namespace xnz {

struct Dialog;

struct QtXeNonZeroCanvas : public QtCanvas
{
  Q_OBJECT

public:

  QtXeNonZeroCanvas(const int width, const int height
  );
  QtXeNonZeroCanvas(const QtXeNonZeroCanvas&) = delete;
  QtXeNonZeroCanvas& operator=(const QtXeNonZeroCanvas&) = delete;
  ~QtXeNonZeroCanvas() noexcept;

  void keyPressEvent(QKeyEvent *e);

private:
  const boost::shared_ptr<Dialog> m_dialog;

  static const boost::shared_ptr<Canvas> CreateCanvas(const int width, const int height) noexcept;
  static const boost::shared_ptr<Dialog> CreateWidget(
  ) noexcept;

  void OnGameOver();
  void OnGameWon();
};

} //~namespace xnz
} //~namespace ribi

#endif // QTXENONZEROCANVAS_H
