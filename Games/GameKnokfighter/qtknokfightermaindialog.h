#ifndef QTKNOKFIGHTERMAINDIALOG_H
#define QTKNOKFIGHTERMAINDIALOG_H

#include <boost/shared_ptr.hpp>
#include <QGraphicsView>

struct QGraphicsScene;
struct QKeyEvent;

namespace ribi {

struct QtKnokfighterBackground;
struct QtKnokfighterPlayer;

class QtKnokfighterMainDialog : public QGraphicsView
{
  Q_OBJECT
  public:
    explicit QtKnokfighterMainDialog(QWidget *parent = 0);
    
  signals:
    
  public slots:

  private slots:
  void do_main_timer();

  void keyPressEvent(QKeyEvent *event);

  private:

  QtKnokfighterBackground * const m_background;
  std::vector<boost::shared_ptr<QtKnokfighterPlayer> > m_players;
  QGraphicsScene * const m_scene;
};

} //~namespace ribi

#endif // QTKNOKFIGHTERMAINDIALOG_H
