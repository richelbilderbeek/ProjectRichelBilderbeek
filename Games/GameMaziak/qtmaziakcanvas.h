#ifndef QTMAZIAKCANVAS_H
#define QTMAZIAKCANVAS_H

#ifdef USE_QTCANVAS

#include "qtcanvas.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

struct QTimer;

namespace ribi {

struct TextCanvas;

namespace maziak {

struct MainDialog;

struct QtMaziakCanvas : public QtCanvas
{
  Q_OBJECT

public:

  QtMaziakCanvas(const int size);
  QtMaziakCanvas(const QtMaziakCanvas&) = delete;
  QtMaziakCanvas& operator=(const QtMaziakCanvas&) = delete;
  ~QtMaziakCanvas() noexcept;

  void keyPressEvent(QKeyEvent *e);
  void keyReleaseEvent(QKeyEvent *e);

private:
  const boost::shared_ptr<MainDialog> m_dialog;
  const boost::shared_ptr<QTimer> m_timer_enemy;
  const boost::shared_ptr<QTimer> m_timer_press_key;
  const boost::shared_ptr<QTimer> m_timer_show_solution;
  const int m_view_height;
  const int m_view_width;

  static const boost::shared_ptr<Canvas> CreateCanvas(const int width, const int height) noexcept;
  static const boost::shared_ptr<MainDialog> CreateWidget(const int size) noexcept;

  void OnGameOver();
  void OnGameWon();
  void OnTimerStartShowingSolution();

private slots:
  void OnTimerPressKey();
  void OnTimerEnemy();
  void OnTimerStopShowingSolution();

};

} //~namespace maziak
} //~namespace ribi


#endif //~ USE_QTCANVAS

#endif // QTMAZIAKCANVAS_H
