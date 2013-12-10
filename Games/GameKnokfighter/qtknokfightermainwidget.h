#ifndef QTKNOKFIGHTERMAINDIALOG_H
#define QTKNOKFIGHTERMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include <QGraphicsView>
#pragma GCC diagnostic pop

struct QGraphicsScene;
struct QKeyEvent;

namespace ribi {

struct QtKnokfighterBackground;
struct QtKnokfighterPlayer;

class QtKnokfighterMainWidget : public QGraphicsView
{
  Q_OBJECT
  public:
  explicit QtKnokfighterMainWidget(QWidget *parent = 0);
  QtKnokfighterMainWidget(const QtKnokfighterMainWidget&) = delete;
  QtKnokfighterMainWidget& operator=(const QtKnokfighterMainWidget&) = delete;

  signals:
    
  public slots:

  private slots:
  void do_main_timer();

  void keyPressEvent(QKeyEvent *event);

  private:

  QtKnokfighterBackground * const m_background;
  std::vector<boost::shared_ptr<QtKnokfighterPlayer> > m_players;
  QGraphicsScene * const m_scene;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTKNOKFIGHTERMAINDIALOG_H
