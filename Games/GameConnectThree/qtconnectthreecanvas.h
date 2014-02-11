#ifndef QTCONNECTTHREECANVAS_H
#define QTCONNECTTHREECANVAS_H

#include "qtcanvas.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

namespace ribi {

struct TextCanvas;
struct ConnectThreeWidget;

struct QtConnectThreeCanvas : public QtCanvas
{
  Q_OBJECT

public:

  QtConnectThreeCanvas(const int size);
  QtConnectThreeCanvas(const QtConnectThreeCanvas&) = delete;
  QtConnectThreeCanvas& operator=(const QtConnectThreeCanvas&) = delete;
  ~QtConnectThreeCanvas() noexcept;

  void keyPressEvent(QKeyEvent *e);

private:
  const boost::shared_ptr<ConnectThreeWidget> m_dialog;

  static const boost::shared_ptr<Canvas> CreateCanvas(const int width, const int height) noexcept;
  static const boost::shared_ptr<ConnectThreeWidget> CreateWidget(const int size) noexcept;

  void OnGameOver();
  void OnGameWon();
};

} //~namespace ribi

#endif // QTCONNECTTHREECANVAS_H
