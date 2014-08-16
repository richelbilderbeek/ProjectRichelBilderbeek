#ifndef QTCONNECTTHREECANVAS_H
#define QTCONNECTTHREECANVAS_H

#include <bitset>

#include "qtcanvas.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

namespace ribi {

struct TextCanvas;

namespace con3 {

struct ConnectThreeWidget;

struct QtConnectThreeCanvas : public QtCanvas
{
  Q_OBJECT

public:

  QtConnectThreeCanvas(
    const std::bitset<3>& is_player_human,
    const int width, const int height
  );
  QtConnectThreeCanvas(const QtConnectThreeCanvas&) = delete;
  QtConnectThreeCanvas& operator=(const QtConnectThreeCanvas&) = delete;
  ~QtConnectThreeCanvas() noexcept;

  void keyPressEvent(QKeyEvent *e) override;

private:
  const boost::shared_ptr<ConnectThreeWidget> m_dialog;

  static const boost::shared_ptr<Canvas> CreateCanvas(const int width, const int height) noexcept;
  static const boost::shared_ptr<ConnectThreeWidget> CreateWidget(
    const std::bitset<3>& is_player_human,
    const int width,
    const int height
  ) noexcept;

  void OnGameOver();
  void OnGameWon();
};

} //~namespace con3
} //~namespace ribi

#endif // QTCONNECTTHREECANVAS_H
